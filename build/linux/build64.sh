#!/bin/sh

BUILD_ROOT=`cd "$(dirname "$0")" && pwd`

"$BUILD_ROOT/build.sh" address-model=64 $*
