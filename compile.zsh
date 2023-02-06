#!/bin/zsh

cwd=$(pwd)
build_dir="$(pwd)/build/"

cmake -GNinja\
      -DCMAKE_CXX_COMPILER=$CXX\
      -DCMAKE_BUILD_TYPE=Debug\
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON\
      -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake\
      -S $cwd\
      -B $build_dir

cmake --build

# cd $build_dir
# ninja
# cd $cwd