#!/bin/zsh

FOUNDATION_HOME="${HOME}/projects/libfoundation"
BUILD_DIR="${FOUNDATION_HOME}/build/release"

if [ ! -d $BUILD_DIR ]; then
      mkdir $BUILD_DIR      
fi

cmake -GNinja\
      -DCMAKE_CXX_COMPILER=$CXX\
      -DCMAKE_BUILD_TYPE=Release\
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON\
      -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake\
      -S $FOUNDATION_HOME\
      -B $BUILD_DIR

cmake --build $BUILD_DIR

