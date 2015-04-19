#!/bin/sh

BUILD_ROOT=`cd "$(dirname "$0")/build" && pwd`  

CPU_TYPE=`uname -p`

case "$CPU_TYPE" in
    x86_64|amd64)
        echo Detected 64-bit operating system
        "$BUILD_ROOT/unix/build.sh" address-model=64 $*
        ;;
    i*86)
        echo Detected 32-bit operating system
        "$BUILD_ROOT/unix/build.sh" address-model=32 $*
        ;;
    *)
        echo Current operating system is not supported
        exit 1
        ;;
esac
