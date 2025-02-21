<!-- markdownlint-disable-next-line MD043 -->

# Castlevania Decompilation

<!-- markdownlint-disable-next-line MD033 -->
<div align="center">

[![Discord](https://img.shields.io/discord/106120859520905216?logo=discord&logoColor=white&label=CV64%26CVLoDSpeedruns)](https://discord.gg/eKht382)
[![Castlevania 64 - Research Spreadsheets](https://img.shields.io/badge/Castlevania%2064%20-%20Research%20Spreadsheets-blue?logo=googlesheets)][research-spreadsheets]
[![TCRF - Castlevania (Nintendo 64)](https://img.shields.io/badge/TCRF-Castlevania%20%28Nintendo%2064%29-blue)](<https://tcrf.net/Notes:Castlevania_(Nintendo_64)>)

</div>

## About

This repository contains a work-in-progress decompilation project
for Castlevania (Nintendo 64).

> [!IMPORTANT]
> This repository **DOES NOT** contain any of the assets required to build the ROM.
> All data, including the original assembly code and assets, requires a legally
> obtained copy of the original game to extract all of this data from.

The main objective of this project is to rewrite C code that, when compiled,
results in matching assembly code found in the game's ROM.
Besides this, the project also aims to extract and convert all assets
from binary data to a higher-level format understood by the console.

At the moment, this project cannot be used to create mods on a large scale
due to issues with shiftability (i.e. hardcoded addresses),
therefore it's only useful for documentation of the game's code for now.

## Acknowledgements

### Tools

These tools are instrumental in the decompilation process of Castlevania 64.

- [Splat](https://github.com/ethteck/splat)
- [LZKN64][lzkn64]
- [asm-processor](https://github.com/simonlindholm/asm-processor)

### People

These people make this project possible and successful.

- [@moisesPC](https://github.com/moisesPC) for his research efforts and the
  creation/upkeep of the [Castlevania 64 - Research Spreadsheets][research-spreadsheets]
- [@LiquidCat64](https://github.com/LiquidCat64) and [@Fluvian](https://github.com/Fluvian)
  for reversing the [LZKN64][lzkn64] compression algorithm used by Konami
- [@decompals](https://github.com/decompals) for the
  [ultralib](https://github.com/decompals/ultralib) repository,
  which we took the Ultra64 headers from.

## Getting started

### Requirements

- Your own (legally obtained) copy of Castlevania for the Nintendo 64 (USA v1.0)
  (`sha1: 989A28782ED6B0BC489A1BBBD7BEC355D8F2707E`)
- CMake
- Git
- Make/Ninja

#### Docker

There is a Dockerfile for convenience. If you want to have your development
environment on your system, continue to [Linux](#linux-debianubuntu-offshoots)
or [Windows](#windows).

> [!NOTE]
> You may need to prefix `docker` commands with `sudo` if your user is not part
> of the docker user group.

You can build the Docker image as follows.

```sh
docker build . -t cv64
```

And then, you can interactively spin up a docker container.

```sh
docker run --rm -ti -v $(pwd):/cv64 cv64
```

#### Linux (Debian/Ubuntu offshoots)

- cmake
- build-essential
- binutils-mips-linux-gnu
- python3/pip3 (We recommend managing this through [mise][mise])
- ninja-build
- libbz2-dev

#### Windows

- MinGW

### Building

> [!WARNING]
> If the compilation process fails, go to the `castlevania.yaml` file
> and set the option `dissasemble_all` to `True`, then clean and build again.
> It should then end up with an error.
> At this point, change said option back to `False`,
> clean and build again and the project should build successfully.

Place a Castlevania 64 (USA v1.0) ROM in the root of the project, and rename it
to `baserom.z64`.

Now, you must configure the CMake project by running the following...

```sh
cmake -S . -B build -G "Ninja"
```

> [!TIP]
> Or run `mise run build:configure` if you are already using [mise][mise]

The above snippet produces a Ninja-based build system under the hood. This seems
to be faster than Make, but if you still prefer Make over Ninja, you can run the
following...

```sh
cmake -S . -B build -G "Unix Makefiles"
```

If you need to debug non-matching compressed files by skipping the compression
step and not checking the ROM's checksum, you can use the following...

```sh
cmake -S . -B build -G "Ninja" -Dcompress=FALSE
```

> [!TIP]
> Or run `mise run build:configure --no-compress` if you are already using [mise][mise]

Afterwards, to build the project, run the following...

```sh
cmake --build build
```

> [!TIP]
> Or run `mise run build` if you are already using [mise][mise]

### Cleaning

Run the following to clean up the build artifacts.

```sh
./scripts/build/clean
```

> [!TIP]
> Or run `mise run build:clean` if you are already using [mise][mise]

### Context generation

You can generate a `ctx.c` context file for use with [mips2c](https://github.com/matt-kempster/m2c)
or [decomp.me](https://decomp.me/).
This will contain all headers within a given source file

```sh
python tools/m2ctx.py <c_file>
```

> [!TIP]
> Or run `mise run m2ctx <c_file>` if you are already using [mise][mise].

### Using permuter

You can use permuter to assist on matching functions that are close to completion,
but are problematic to work with, such as when there registers are allocated differently
or when instructions are placed in a different order than the target assembly.

1. Go to a scratch from [decomp.me](decomp.me) and copy the URL slug of the function
   you are working with. This looks like `https://decomp.me/scratch/<scratch_slug>`.

2. From the root of the repo, run:

   ```sh
   ./scripts/permuter/prepare <scratch_slug>
   ```

   This will create a scratch directory called `scratch/<scratch_slug>` from the
   root of the project.

> [!TIP]
> Or run `mise run permuter:prepare <scratch_slug>` if you are already using [mise][mise].

3. From the root of the repo, run:

   ```sh
   python tools/decomp-permuter/permuter.py scratch/<scratch_slug>
   ```

   Add the `-j` option to utilize multiple cores, followed by the number of cores.

> [!TIP]
> Or run `mise run permuter <scratch_slug>` if you are already using [mise][mise].

[mise]: https://github.com/jdx/mise
[research-spreadsheets]: https://docs.google.com/spreadsheets/d/1nzh_nFf26oVZy6uWeNYiYGXAto6Yz3xypZwWqwJBBJQ/edit#gid=74717405
[lzkn64]: https://github.com/fluvian/lzkn64
