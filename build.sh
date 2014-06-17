#!/bin/sh

BUILD_ROOT=`cd "$(dirname "$0")/build" && pwd`  

OS_NAME=`uname -s`
CPU_TYPE=`uname -p`

case "$OS_NAME:$CPU_TYPE" in
    Linux:x86_64)
        echo Detected 64-bit Linux operating system
        "$BUILD_ROOT/linux/build64.sh" $*
        ;;
    Linux:i*86)
        echo Detected 32-bit Linux operating system
        "$BUILD_ROOT/linux/build32.sh" $*
        ;;
    FreeBSD:amd64)
        echo Detected 64-bit FreeBSD operating system
        "$BUILD_ROOT/freebsd/build64.sh" $*
        ;;
    FreeBSD:i*86)
        echo Detected 32-bit FreeBSD operating system
        "$BUILD_ROOT/freebsd/build32.sh" $*
        ;;
    *:*)
        echo Current operating system is not supported
        exit 1
        ;;
esac
