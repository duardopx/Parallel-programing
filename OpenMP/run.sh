#!/bin/bash


cc serial_bst.c -o serial_bst -Wall -pedantic -ansi -g
./serial_bst 100000000

rm -rf serial_bst
