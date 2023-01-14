#!/bin/zsh

# setup modules for the zshell
source $HOME/apps/modules/5.0.1/init/zsh
module load llvm

cwd=$(pwd)
build_dir="$(pwd)/build/"

cmake -GNinja\
      -DCMAKE_CXX_COMPILER=$CXX\
      -DCMAKE_BUILD_TYPE=Release\
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON\
      -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake\
      -S $cwd\
      -B $build_dir

cd $build_dir
ninja
cd $cwd