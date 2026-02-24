#! /usr/bin/env bash

set -e

BUILD_DIR="build"

if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
fi

cmake -B "$BUILD_DIR" -S .
cd "$BUILD_DIR"
make -j
