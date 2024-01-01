# Castlevania Decompilation

<div align="center">

[![Discord](https://img.shields.io/discord/106120859520905216?logo=discord&logoColor=white&label=CV64%26CVLoDSpeedruns)](https://discord.gg/eKht382)
[![Castlevania 64 - Research Spreadsheets](https://img.shields.io/badge/Castlevania%2064%20-%20Research%20Spreadsheets-blue?logo=googlesheets)][research-spreadsheets]
[![TCRF - Castlevania (Nintendo 64)](https://img.shields.io/badge/TCRF-Castlevania%20%28Nintendo%2064%29-blue)](https://tcrf.net/Notes:Castlevania_(Nintendo_64))

</div>

## Acknowledgements

### Tools

These tools are instrumental in the decompilation process of Castlevania 64.

- [Splat](https://github.com/ethteck/splat)
- [LZKN64][lzkn64]
- [asm-processor](https://github.com/simonlindholm/asm-processor)

### People

These people make this project possible and successful.

- [@moisesPC](https://github.com/moisesPC) for his research efforts and the creation/upkeep of the [Castlevania 64 - Research Spreadsheets][research-spreadsheets]
- [@LiquidCat64](https://github.com/LiquidCat64) and [@Fluvian](https://github.com/Fluvian) for reversing the [LZKN64][lzkn64] compression algorithm used by Konami

## Getting started

### Requirements

- Your own (legally obtained) copy of Castlevania for the Nintendo 64 (USA v1.0) (`sha1: 989A28782ED6B0BC489A1BBBD7BEC355D8F2707E`)
- CMake
- Git
- Make/Ninja

#### Docker

There is a Dockerfile for convenience. If you want to have your
development environment on your system, continue to [Linux](#linux-debianubuntu-offshoots)
or [Windows](#windows).

> [!NOTE]
> You may need to prefix `docker` commands with `sudo`
> if your user is not part of the docker user group.

You can build the Docker image as follows.

```sh
docker build . -t c64
```

And then, you can interactively spin up a docker container.

```sh
docker run --rm -ti -v $(pwd):/c64 c64
```

#### Linux (Debian/Ubuntu offshoots)

- build-essential
- binutils-mips-linux-gnu
- python3/pip3 (I recommend managing this through [rtx][rtx])

#### Windows

- MinGW

### Building

Place a Castlevania 64 (USA v1.0) ROM in the root of the project, and rename it to `baserom.z64`.

Now, you must configure the CMake project by running the following...

```sh
cmake -S . -B build -G "Ninja"
```

> [!TIP]
> Or run `rtx run c` if you are already using [rtx][rtx]

The above snippet produces a Ninja-based build system under the hood. This seems to be faster than Make,
but if you still prefer Make over Ninja, you can run the following...

```sh
cmake -S . -B build -G "Unix Makefiles"
```

Afterwards, to build the project, run the following...

```sh
cmake --build build
```

> [!TIP]
> Or run `rtx run b` if you are already using [rtx][rtx]

### Cleaning

Run the following to clean up the build artifacts.

```sh
./scripts/clean
```

> [!TIP]
> Or run `rtx run clean` if you are already using [rtx][rtx]

[rtx]: https://github.com/jdx/rtx
[research-spreadsheets]: https://docs.google.com/spreadsheets/d/1nzh_nFf26oVZy6uWeNYiYGXAto6Yz3xypZwWqwJBBJQ/edit#gid=74717405
[lzkn64]: https://github.com/fluvian/lzkn64
