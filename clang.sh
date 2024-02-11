#!/bin/bash

ROOT_SRC='./src'
ROOT_TESTS='tests'
FILE_NAME=.clang-format
MODEL_SRCDIRS_H=("array" "iterator" "list" "queue" "stack" "vector")
MODEL_SRCDIRS_TCC=("map" "multiset" "set" "tree" )


function clangfile() {
  cp ./materials/linters/.clang-format $1/${FILE_NAME}
  if [ $2 = 'cch' ]; then
    clang-format -n $1/*.cc $1/*.h
  elif [ $2 = 'tcch' ]; then
    clang-format -n $1/*.tcc $1/*.h
  else
    clang-format -n $1/*.h
  fi

  rm -rf $1/${FILE_NAME}
}

for dir in ${MODEL_SRCDIRS_H[@]}; do
  DIRECTORY=${ROOT_SRC}/${dir}
  clangfile ${DIRECTORY} 'h'
done

for dir in ${MODEL_SRCDIRS_TCC[@]}; do
  DIRECTORY=${ROOT_SRC}/${dir}
  clangfile ${DIRECTORY} 'tcch'
done

clangfile ${ROOT_TESTS} 'cch'
