FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    cmake \
    gcc \
    build-essential \
    vim \
    openssh-server \
    && apt-get clean

WORKDIR /workspace
