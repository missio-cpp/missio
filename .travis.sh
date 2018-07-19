#!/bin/sh


if [ -z "${TRAVIS}" ]
then
  echo "This script is designed to run in Travis CI environment"
  exit 1
fi


if [ -z "${BOOST_VERSION}" ]
then
  BOOST_VERSION=1.63.0
fi


DEPS_DIR="${TRAVIS_BUILD_DIR}/deps"


install_boost()
{
  BOOST_NAME="boost_$(echo ${BOOST_VERSION} | sed "s/\./_/g")"

  BOOST_DIR="${DEPS_DIR}/${BOOST_NAME}"

  mkdir -p "${BOOST_DIR}"

  if [ -z "$(ls -A "${BOOST_DIR}")" ]
  then
    echo "Downloading and preparing Boost ${BOOST_VERSION}"

    BOOST_URL="http://sourceforge.net/projects/boost/files/boost/${BOOST_VERSION}/${BOOST_NAME}.tar.gz"

    wget --no-check-certificate -O - $BOOST_URL | tar --strip-components=1 -xz -C $BOOST_DIR
  fi

  echo "${BOOST_DIR}" > "${DEPS_DIR}/BOOST_ROOT"
}


install()
{
  if [ "${VARIANT}" = "coverage" ]
  then
    pip install --user --upgrade cpp-coveralls
  fi

  mkdir -p "${DEPS_DIR}" && cd "${DEPS_DIR}"

  install_boost
}


build()
{
  export CC=$TRAVIS_CC
  export CXX=$TRAVIS_CXX

  case "${CC}" in
    clang*) TOOLSET="clang";;
    gcc*) TOOLSET="gcc";;
  esac

  export BOOST_ROOT="$(cat "${DEPS_DIR}/BOOST_ROOT")"

  ./build/unix/build.sh --user-config="${TRAVIS_BUILD_DIR}/user-config.jam" toolset=$TOOLSET variant=$VARIANT link=$LINK boost-link=$LINK boost=source

  if [ $? -ne 0 ]
  then
    return $?
  fi

  if [ "${VARIANT}" = "coverage" ]
  then
    coveralls --gcov gcov-5 --gcov-options '\-lp' --exclude deps --exclude test --exclude perf
  fi
}


case "$1" in
  install) install;;
  build) build;;
esac


cd "${TRAVIS_BUILD_DIR}"
