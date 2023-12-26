# LZK64 compression

> [!WARN]
> **This specification is a WIP**

> [!NOTE]
> Files compressed in this format are also known as Nagano files.

Various files in Castlevania for the Nintendo 64 are compressed using a
custom form of LZ compression specific to Konami. It is commonly referred
to as LZK64.

## Nisitenma-Ichigo table

The ROM contains a _magic_ 16-byte ASCII string indicating the start of a data table
with the addresses of all the compressed files.

This string is `4E69736974656E6D612D49636869676F` in hexadecimal or `Nisitenma-Ichigo`
if interpreted as ASCII characters.
