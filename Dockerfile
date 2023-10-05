FROM ubuntu:22.04 AS base

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
  binutils-mips-linux-gnu \
  build-essential \
  ca-certificates \
  gpg \
  python3 \
  python3-pip \
  wget \
  && rm -rf /var/lib/apt/lists/*

# Obtain Kitware signing key
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null \
  | gpg --dearmor - \
  | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null

# Add Kitware repository to sources list and update
RUN echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main' \
  | tee /etc/apt/sources.list.d/kitware.list >/dev/null \
  && apt update

# Ensure keyring stays up to date as Kitware rotates keys
RUN rm /usr/share/keyrings/kitware-archive-keyring.gpg
RUN apt install -y kitware-archive-keyring

# Install CMake (finally)
RUN apt install -y cmake

COPY requirements.txt tools/splat/requirements.txt /tmp/
RUN pip install --no-cache-dir --requirement /tmp/requirements.txt

FROM base AS workspace

RUN mkdir /c64

# RUN chmod 700 /c64/scripts/bootstrap
# RUN /c64/scripts/bootstrap

WORKDIR /c64

ENTRYPOINT ["/bin/bash"]
