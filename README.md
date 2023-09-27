# Castlevania Decompilation

## Getting started

### Requirements

- Your own (legally obtained) copy of Castlevania for the Nintendo 64
- CMake (3.22 or higher)
- Make (Unix or MinGW)
- Git

#### Linux (Debian/Ubuntu offshoots)

- build-essential
- binutils-mips-linux-gnu
- python3/pip3 (I recommend managing this through [rtx][rtx])

#### Windows

- MinGW

### Bootstrapping

Once you have the requirements, you can run the
following command to bootstrap your environment-
specific build system of choice.

```sh
chmod +x ./scripts/bootstrap
./scripts/bootstrap
```

### Building

CMake can run your build system for you.

```sh
cmake --build ./build
```

Or if you need to rebuild the tools.

```sh
cmake --build ./build/tools
```

[rtx]: https://github.com/jdx/rtx
