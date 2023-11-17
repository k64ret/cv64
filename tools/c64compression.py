#!/usr/bin/env python3

import sys
import argparse
import lzkn64
from typing import BinaryIO, Literal


def compress(
    file_type: Literal["rom", "lzkn64"], input_file: BinaryIO, output_file: BinaryIO
):
    # TODO: not worried about compression yet...
    pass


def decompress(
    file_type: Literal["rom", "lzkn64"], input_file: BinaryIO, output_file: BinaryIO
):
    input_file_buffer = input_file.read()
    match file_type:
        case "rom":
            decompress_rom(input_file, output_file)
        case "lzkn64":
            output_file.write(lzkn64.decompress_buffer(input_file_buffer))


def decompress_rom(input_file: BinaryIO, output_file: BinaryIO):
    """
    Decompress all LZKN64-compressed files in-place within an existing Castlevania ROM file
    :param input_file:
    :param output_file:
    :return:
    """
    print(f"Decompressing {input_file.name} and storing results in {output_file.name}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Compression/Decompression tool-suite for Castlevania on the Nintendo 64"
    )
    parser.add_argument(
        "-t", "--type", choices=["rom", "lzkn64"], default="rom", help="File type"
    )
    subparsers = parser.add_subparsers()

    parser_compress = subparsers.add_parser("compress", help="Compress an object")
    parser_compress.add_argument(
        "input_file",
        nargs="?",
        type=argparse.FileType("rb"),
        default=sys.stdin,
        help="File to compress",
    )
    parser_compress.add_argument(
        "output_file",
        nargs="?",
        type=argparse.FileType("wb"),
        default=sys.stdout,
        help="Resulting compressed file",
    )
    parser_compress.set_defaults(func=compress)

    parser_decompress = subparsers.add_parser("decompress", help="Decompress an object")
    parser_decompress.add_argument(
        "input_file",
        nargs="?",
        type=argparse.FileType("rb"),
        default=sys.stdin,
        help="File to decompress",
    )
    parser_decompress.add_argument(
        "output_file",
        nargs="?",
        type=argparse.FileType("wb"),
        default=sys.stdout,
        help="Resulting decompressed file",
    )
    parser_decompress.set_defaults(func=decompress)

    args = parser.parse_args()

    args.func(args.type, args.input_file, args.output_file)
