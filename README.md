# Castlevania Decompilation

## Getting started

### Requirements

- Your own (legally obtained) copy of Castlevania for the Nintendo 64
- CMake `^v3.22`

Once you have CMake installed, you can run the
following command to bootstrap your environment-
specific build system of choice.

```sh
cmake -S . -B ./build
```

On UNIX-like systems, the default generator creates
Makefiles, so you should be able to build simply.

```sh
cd build/
make all
```
