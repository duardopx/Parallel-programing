#!/bin/bash

# rm output.csv
# rm parallel_trapezoidal_rule

# mpicc -g -Wall parallel_trapezoidal_rule.c -o parallel_trapezoidal_rule

#rounds=5
#
#for cores in 2 4 8; do
#    for input in 100 500 900; do 
#        echo -e "\n$cores\t$input\t\t\c" >> "tempo_de_mm.txt"
#        for round in $(seq $rounds); do
#            mpirun -np $cores --oversubscribe ./parallel_trapezoidal_rule $input
#
#        done
#    done
#done
#
#exit
if [ "$1" ==  "p" ]; then
	mpicc parallel_trapezoidal_rule.c -o parallel_trapezoidal_rule -pedantic -ansi -Wall
	mpirun -np 4 --oversubscribe ./parallel_trapezoidal_rule 800000000
fi

gcc serial_trapezoidal_rule.c -o serial_trapezoidal_rule -Wall -pedantic 
time ./serial_trapezoidal_rule 30000000
rm -rf serial_trapezoidal_rule
