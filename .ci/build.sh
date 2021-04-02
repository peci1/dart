#!/usr/bin/env bash
set -e

if [ -f /etc/os-release ]; then
  # freedesktop.org and systemd
  . /etc/os-release
  OS=$NAME
  VER=$VERSION_ID
elif type lsb_release >/dev/null 2>&1; then
  # linuxbase.org
  OS=$(lsb_release -si)
  VER=$(lsb_release -sr)
elif [ -f /etc/lsb-release ]; then
  # For some versions of Debian/Ubuntu without lsb_release command
  . /etc/lsb-release
  OS=$DISTRIB_ID
  VER=$DISTRIB_RELEASE
elif [ -f /etc/debian_version ]; then
  # Older Debian/Ubuntu/etc.
  OS=Debian
  VER=$(cat /etc/debian_version)
elif [ -f /etc/SuSe-release ]; then
  # Older SuSE/etc.
  echo "Not supported"
  exit 1
elif [ -f /etc/redhat-release ]; then
  # Older Red Hat, CentOS, etc.
  echo "Not supported"
  exit 1
else
  # Fall back to uname, e.g. "Linux <version>", also works for BSD, etc.
  OS=$(uname -s)
  VER=$(uname -r)
fi

echo "Detected OS name    = $OS"
echo "Detected OS version = $VER"

# Sanity checks for required environment variables.
if [ -z "$BUILD_TYPE" ]; then
  echo "Error: Environment variable BUILD_TYPE is unset."
  exit 1
fi

if [ -z "$BUILD_TESTS" ]; then
  echo "Info: Environment variable BUILD_TESTS is unset. Using ON by default"
  BUILD_TESTS=ON
fi

if [ -z "$BUILD_BENCHMARKS" ]; then
  echo "Info: Environment variable BUILD_BENCHMARKS is unset. Using ON by default"
  BUILD_BENCHMARKS=ON
fi

if [ -z "$RUN_MEMCHECK" ]; then
  echo "Info: Environment variable RUN_MEMCHECK is unset. Using OFF by default"
  RUN_MEMCHECK=OFF
fi

if [ -z "$BUILD_PYTHON_BINDING" ]; then
  echo "Info: Environment variable BUILD_PYTHON_BINDING is unset. Using OFF by default."
  BUILD_PYTHON_BINDING=OFF
fi

if [ -z "$COMPILER" ]; then
  echo "Info: Environment variable COMPILER is unset. Using gcc by default."
  COMPILER=gcc
fi

if [ -z "$BUILD_DIR" ]; then
  echo "Info: Environment variable BUILD_DIR is unset. Using $PWD by default."
  BUILD_DIR=$PWD
fi

if [ -z "$CMAKE_BUILD_DIR" ]; then
  echo "Info: Environment variable CMAKE_BUILD_DIR is unset. Using .build by default."
  CMAKE_BUILD_DIR=.build
fi

if [ -z "$CHECK_FORMAT" ]; then
  echo "Info: Environment variable CHECK_FORMAT is unset. Using OFF by default."
  CHECK_FORMAT=OFF
fi

# Set number of threads for parallel build
# Ref: https://unix.stackexchange.com/a/129401
if [ "$OSTYPE" = "linux-gnu" ]; then
  num_threads=$(nproc)
elif [ "$OSTYPE" = "darwin" ]; then
  num_threads=$(sysctl -n hw.logicalcpu)
else
  num_threads=1
  echo "$OSTYPE is not supported to detect the number of logical CPU cores."
fi
while getopts ":j:" opt; do
  case $opt in
  j)
    num_threads="$OPTARG"
    ;;
  \?)
    echo "Invalid option -$OPTARG" >&2
    ;;
  esac
done

# Set compilers
if [ "$COMPILER" = "gcc" ]; then
  export CC=gcc
  export CXX=g++
elif [ "$COMPILER" = "clang" ]; then
  export CC=clang
  export CXX=clang++
else
  echo "Info: Compiler isn't specified. Using the system default."
fi

# Run CMake
mkdir -p $CMAKE_BUILD_DIR && cd $CMAKE_BUILD_DIR
if [ "$OSTYPE" = "linux-gnu" ]; then
  install_prefix_option="-DCMAKE_INSTALL_PREFIX=/usr/"
fi
cmake $BUILD_DIR \
  -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
  -DDART_BUILD_TESTS=$BUILD_TESTS \
  -DDART_BUILD_BENCHMARKS=$BUILD_BENCHMARKS \
  -DDART_BUILD_PYTHON_BINDING=$BUILD_PYTHON_BINDING \
  ${install_prefix_option}

if [ "$CHECK_FORMAT" = "ON" ]; then
  make clang-format-check
fi

# C++: build, test, and install
make -s -j$num_threads all
if [ "$BUILD_TESTS" = "ON" ]; then
  ctest --output-on-failure -j$num_threads
  if [ "$RUN_MEMCHECK" = "ON" ]; then
    ctest --output-on-failure -j$num_threads -T memcheck
  fi
fi

# Install dartpy8
if [ "$BUILD_PYTHON_BINDING" = "ON" ]; then
  make install-dartpy8
fi
