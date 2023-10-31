FROM ubuntu:22.04 AS base

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
  binutils-mips-linux-gnu \
  build-essential \
  make \
  python3 \
  python3-pip \
  wget \
  && rm -rf /var/lib/apt/lists/*

COPY requirements.txt tools/splat/requirements.txt /tmp/
RUN pip install --no-cache-dir --requirement /tmp/requirements.txt

FROM base AS workspace

RUN mkdir /c64

WORKDIR /c64

ENTRYPOINT ["/bin/bash"]
