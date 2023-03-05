#!/usr/bin/env zsh

FOUNDATION_HOME=$HOME/projects/libfoundation
build_dir="${FOUNDATION_HOME}/build/debug"

if [ -d $build_dir ]
then
  rm -rf $build_dir
fi

mkdir $build_dir