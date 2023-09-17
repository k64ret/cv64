# Castlevania Decompilation

## Getting started

### Requirements

- Your own (legally obtained) copy of Castlevania for the Nintendo 64
- CMake
- Make (Unix or MinGW)
- Git

#### Linux (Debian/Ubuntu offshoots)

- build-essential
- binutils-mips-linux-gnu
- python3/pip3 (I recommend managing this through [rtx][rtx])

#### Windows

- MinGW

Once you have CMake installed, you can run the
following command to bootstrap your environment-
specific build system of choice.

```sh
chmod +x ./scripts/bootstrap
./scripts/bootstrap
```

Or on Windows...

```dosbatch
.\scripts\bootstrap
```

On UNIX-like systems, the default generator creates
Makefiles, so you should be able to build simply.

```sh
cd build/
make all
cd tools/
make all
```

[rtx]: https://github.com/jdx/rtx
