# Yoinked from:
# https://github.com/Fluvian/mnsg/blob/main/tools/decompress.py

# Python script for decompressing the baserom file.
import sys

# Address of the first file in the overlay table.
firstFileAddr = None

# Sizes of all the decompressed files combined.
rawSize = None

# List of files to skip.
skipFiles = []

# List of all addresses for the files.
fileAddrs = []

# List of all file sizes for the files.
fileSizes = []

# List of the new addresses for the files.
newFileAddrs = []

# List of all the decompressed file sizes.
newFileSizes = []

##### Search #####


def preprocess_find_match(signature):
    prefixPosition = 0
    suffixPosition = 1
    partial_match_array = [0] * len(signature)

    while suffixPosition < len(signature):
        if signature[prefixPosition] == signature[suffixPosition]:
            partial_match_array[suffixPosition] = prefixPosition + 1
            prefixPosition = prefixPosition + 1
            suffixPosition = suffixPosition + 1

        elif prefixPosition == 0:
            partial_match_array[suffixPosition] = 0
            suffixPosition = suffixPosition + 1

        else:
            prefixPosition = partial_match_array[prefixPosition - 1]

    return partial_match_array


def find_match(input, signature):
    filePosition = 0
    signaturePosition = 0
    partial_match_array = preprocess_find_match(signature)

    while filePosition < len(input):
        if signature[signaturePosition] == input[filePosition]:
            filePosition = filePosition + 1
            signaturePosition = signaturePosition + 1

            if signaturePosition == len(signature):
                # Return position at end of signature.
                return filePosition

        elif signaturePosition > 0:
            signaturePosition = partial_match_array[signaturePosition - 1]

        else:
            signaturePosition = 0
            filePosition = filePosition + 1

    return -1

##### Decompression #####


def decompress_files(input, sizeCompressed):
    buffer = bytearray(0xFFFFFF)  # Max file size for a compressed LZKN64 file.

    inPos = 4  # Offset in input file.
    bufPos = 0  # Offset in output file.

    while inPos < sizeCompressed:
        curCmd = input[inPos]
        inPos += 1

        if curCmd < 0x80:  # Sliding window lookback and copy with length.
            lookBackLength = input[inPos] + (curCmd << 8) & 0x3FF
            for _ in range(2 + (curCmd >> 2)):
                buffer[bufPos] = buffer[bufPos - lookBackLength]
                bufPos += 1
            inPos += 1

        elif curCmd < 0xA0:  # Raw data copy with length.
            for _ in range(curCmd & 0x1F):
                buffer[bufPos] = input[inPos]
                bufPos += 1
                inPos += 1

        elif curCmd <= 0xFF:  # Write specific byte for length.
            value = 0
            length = 2 + (curCmd & 0x1F)

            if curCmd == 0xFF:
                length = 2 + input[inPos]
                inPos += 1
            elif curCmd < 0xE0:
                value = input[inPos]
                inPos += 1

            for _ in range(length):
                buffer[bufPos] = value
                bufPos += 1

        else:
            inPos += 1

    return buffer[:bufPos]

# Decompression code modified to just increment the position counters.


def decompress_get_len(input, sizeCompressed):
    inPos = 4  # Offset in input file.
    bufPos = 0  # Offset in output file.

    while inPos < sizeCompressed:
        curCmd = input[inPos]
        inPos += 1

        if curCmd < 0x80:  # Sliding window lookback and copy with length.
            for _ in range(2 + (curCmd >> 2)):
                bufPos += 1
            inPos += 1

        elif curCmd < 0xA0:  # Raw data copy with length.
            for _ in range(curCmd & 0x1F):
                bufPos += 1
                inPos += 1

        elif curCmd <= 0xFF:  # Write specific byte for length.
            length = 2 + (curCmd & 0x1F)

            if curCmd == 0xFF:
                length = 2 + input[inPos]
                inPos += 1
            elif curCmd < 0xE0:
                inPos += 1

            for _ in range(length):
                bufPos += 1

        else:
            inPos += 1

    return bufPos

##### Modify Overlay Table #####


def copy_buffer(input, output):
    output[0:len(input)] = input

    return output


def copy_buffer_from_pos_with_len(input, output, pos, len):
    output[0:len] = input[pos:pos + len]

    return output


def copy_buffer_to_pos_with_len(input, output, pos, len):
    output[pos:pos + len] = input[0:len]

    return output


def zero_out_buffer_from_pos_with_len(output, pos, len):
    for i in range(len):
        output[i + pos] = 0

    return output


def get_compressed_file_addresses_and_sizes(input, tableAddr):
    pos = 0
    fileAddr = int.from_bytes(
        input[tableAddr + pos + 1:tableAddr + pos + 4], byteorder='big')
    nextFileAddr = int.from_bytes(
        input[tableAddr + pos + 5:tableAddr + pos + 8], byteorder='big')

    global firstFileAddr
    firstFileAddr = fileAddr

    while fileAddr != 0:
        # Highest bit of address is not set, file is already decompressed.
        if input[tableAddr + pos] == 0:
            skipFiles.append(1)

            fileAddrs.append(fileAddr)

            if (nextFileAddr - fileAddr) > 0:
                fileSizes.append(nextFileAddr - fileAddr)
            else:
                fileSizes.append(0)
        else:
            skipFiles.append(0)

            fileAddrs.append(fileAddr)

            # Headers of compressed files have their compressed sizes within them.
            fileSizes.append(int.from_bytes(
                input[fileAddr + 1:fileAddr + 4], byteorder='big'))

        pos += 4

        fileAddr = int.from_bytes(
            input[tableAddr + pos + 1:tableAddr + pos + 4], byteorder='big')
        nextFileAddr = int.from_bytes(
            input[tableAddr + pos + 5:tableAddr + pos + 8], byteorder='big')


def get_raw_file_sizes(input):
    # Max file size for a compressed LZKN64 file.
    compressedBuf = bytearray(0xFFFFFF)

    for i in range(len(fileSizes)):
        copy_buffer_from_pos_with_len(
            input, compressedBuf, fileAddrs[i], fileSizes[i])

        if skipFiles[i] != 1:
            # "Fake decompress" to get the length of the raw data.
            newFileSizes.append(decompress_get_len(
                compressedBuf, fileSizes[i]))
        else:
            newFileSizes.append(fileSizes[i])


def get_raw_file_addresses():
    pos = firstFileAddr

    for i in range(len(fileAddrs)):
        newFileAddrs.append(pos)
        pos += newFileSizes[i]

    global rawSize
    rawSize = pos - firstFileAddr


def write_raw_files(input, buffer, tableAddr):
    # Max file size for a compressed LZKN64 file.
    fileBuf = bytearray(0xFFFFFF)

    for i in range(len(fileAddrs)):
        copy_buffer_from_pos_with_len(
            input, fileBuf, fileAddrs[i], fileSizes[i])

        if skipFiles[i] != 1:
            fileBuf = decompress_files(fileBuf, fileSizes[i])

        copy_buffer_to_pos_with_len(
            fileBuf, buffer, newFileAddrs[i], newFileSizes[i])

        # Write the new locations to the overlay table.
        buffer[tableAddr + (i * 4):tableAddr + (i * 4) +
               4] = newFileAddrs[i].to_bytes(4, 'big')

# Find the nearest power of two for the final ROM size. (https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2)


def get_new_file_size(size):
    size -= 1
    size |= size >> 1
    size |= size >> 2
    size |= size >> 4
    size |= size >> 8
    size |= size >> 16
    size += 1

    return size


def decompress(input, tableAddr):
    buffer = bytearray(0x4000000)  # 512Mbit (64Mbyte) is the maximum ROM size.
    buffer = copy_buffer(input, buffer)

    # List all of the file addresses and sizes in a table.
    get_compressed_file_addresses_and_sizes(input, tableAddr)

    # Get the decompressed file sizes.
    get_raw_file_sizes(input)

    # Get the decompressed file addresses.
    get_raw_file_addresses()

    buffer = zero_out_buffer_from_pos_with_len(buffer, firstFileAddr, rawSize)

    write_raw_files(input, buffer, tableAddr)

    return buffer[:get_new_file_size(rawSize + firstFileAddr)]


def main():
    input = open(sys.argv[1], "rb")
    output = open(sys.argv[2], "wb")
    inputBuf = input.read()

    tableAddr = find_match(
        inputBuf, b'\x4E\x69\x73\x69\x74\x65\x6E\x6D\x61\x2D\x49\x63\x68\x69\x67\x6F')

    output.write(decompress(inputBuf, tableAddr))

    input.close()
    output.close()


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("LZKN64 decompression Script")
        print("")
        print("decompress.py input_file output_file")
        print("    input_file: Path to the ROM file for an LZKN64 compressed game.")
        print("    output_file: Path to the resulting decompressed ROM file.")
    else:
        main()
