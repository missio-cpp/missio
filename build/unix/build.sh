#!/bin/sh

MISSIO_ROOT="$(cd "$(dirname "$0")/../.." && pwd)"

echo "MISSIO_ROOT = ${MISSIO_ROOT}"
echo "BOOST_ROOT  = ${BOOST_ROOT}"

if [ ! -e "${MISSIO_ROOT}/Jamroot" ]
then
    echo "Could not find file \"Jamroot\" required to build missio"
    exit 1
fi

if [ -n "${BOOST_ROOT}" ]
then
    # Remove trailing slash
    BOOST_ROOT="${BOOST_ROOT%/}"

    if [ ! -e "${BOOST_ROOT}/boost-build.jam" ]
    then
        echo "Environment variable BOOST_ROOT does not point to a BOOST distribution"
        exit 1
    fi

    BOOST_JAM="${BOOST_ROOT}/bjam"
    BOOST_JAM_LOG="${BOOST_ROOT}/bjam.log"
    BOOST_BUILD_PATH="${BOOST_ROOT}/tools/build/v2"

    if [ ! -x "${BOOST_JAM}" ]
    then
        if [ ! -x "${BOOST_ROOT}/bootstrap.sh" ]
        then
            echo "Could not find file \"bootstrap.bat\" required to build Boost.Jam build engine"
            exit 1
        fi

        OLD_PATH="$(pwd)"
        cd "${BOOST_ROOT}"

        echo "Building Boost.Jam build engine"
        ./bootstrap.sh 1>/dev/null 2>/dev/null

        if [ $? -ne 0 ]
        then
            echo "Error building Boost.Jam build engine"
            echo "See ${BOOST_JAM_LOG} for details"
            exit $?
        fi

        cd "${OLD_PATH}"
    fi

    export BOOST_ROOT="\"${BOOST_ROOT}\""
    export BOOST_BUILD_PATH="\"${BOOST_BUILD_PATH}\""
else
    BOOST_JAM="bjam"
fi

if [ ! -x "$(command -v "${BOOST_JAM}")" ]
then
    echo "Could not find file \"${BOOST_JAM}\" required to build missio"
    exit 1
fi

OLD_PATH="$(pwd)"
cd "${MISSIO_ROOT}"

echo "Starting build of missio"
"${BOOST_JAM}" -q $*

if [ $? -ne 0 ]
then
    echo "Error building missio"
    exit $?
fi

cd "${OLD_PATH}"
