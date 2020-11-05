#!/bin/bash

_sort="./odd_even_sort"
matrix="./square-matrix"

# set -x

compiling()
{

  cc $matrix/serial_square_matrix.c -o $matrix/serial_square_matrix -Wall -pedantic -std=c99

  cc $matrix/parallel_square_matrix.c -o $matrix/parallel_square_matrix -Wall -pedantic -ansi -lpthread

  # cc $matrix/serial_sort.c -o $_sort/serial_sort -Wall -pedantic -ansi

  # cc $matrix/parallel_sort.c -o $_sort/parallel_sort -Wall -pedantic -ansi -lthread
}

remove_garbage()
{
  find square-matrix -type f -perm /001 -delete
  find odd-even-sort -type f -perm /001 -delete
}


run_single_serial_code()
{
  [[ "$1" == "sort" ]] && $_sort/"serial_sort" $2
  [[ "$1" == "matrix" ]] && $matrix/"serial_square_matrix" $2 $3 $4
}


run_single_parallel_code()
{
  # Directory     file    core quantity   input
  [[ "$1" == "sort" ]] && $_sort/"parallel_sort" $2 
  [[ "$1" == "matrix" ]] && $matrix/"parallel_square_matrix" $2 $3 
}

echo "[>] Compiling all scripts "
echo ------------------------------
compiling


echo "[>] Run serial"
echo ------------------------------
run_single_serial_code matrix 3 3 3 
# run_single_parallel_code matrix  10

remove_garbage
