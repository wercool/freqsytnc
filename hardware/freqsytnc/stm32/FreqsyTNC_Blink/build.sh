#!/usr/bin/env bash
set -e

BUILD_DIR="build"

# Если передать флаг --clean или -c, скрипт очистит сборку
if [ "$1" == "--clean" ] || [ "$1" == "-c" ]; then
    echo "==> Cleaning build directory..."
    rm -rf "$BUILD_DIR"
    shift
fi

if [ ! -d "$BUILD_DIR" ]; then
    echo "==> Configuring CMake..."
    cmake -B "$BUILD_DIR" -DCMAKE_C_COMPILER=arm-none-eabi-gcc
fi

echo "==> Building project..."
cmake --build "$BUILD_DIR"

if [ "$1" == "--flash" ] || [ "$1" == "-f" ]; then
    echo "==> Flashing via DFU..."
    dfu-util -a 0 -s 0x08000000:leave -D "$BUILD_DIR/FreqsyTNC_Blink.bin"
fi

echo "==> Done!"