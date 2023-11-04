# Castlevania Decompilation

## Getting started

### Requirements

- Your own (legally obtained) copy of Castlevania for the Nintendo 64 (USA v1.0) (`sha1: 989A28782ED6B0BC489A1BBBD7BEC355D8F2707E`)
- CMake (3.22 or higher)
- Git

#### Docker

There is a Dockerfile for convenience. If you want to have your
development environment on your system, continue to [Linux](#linux-debianubuntu-offshoots)
or [Windows](#windows).

> **Note**
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

Run, the following... It's that simple (supposed to be, anyway).

```sh
make
```

See available rules:

```sh
make help
```

[rtx]: https://github.com/jdx/rtx
