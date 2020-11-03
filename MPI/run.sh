#!/bin/bash

# File paths
generate_pi="./generate-pi"
trapezoidal_rule="./trapezoidal-rule"
_sort="./odd-even-transposition-sort"  

compiling_all_sources()
{
    mpicc $generate_pi/parallel_generate_pi.c -o $generate_pi/parallel_pi -Wall -pedantic

    cc $generate_pi/serial_generate_pi.c -o $generate_pi/serial_pi -Wall -pedantic

    mpicc $trapezoidal_rule/parallel_trapezoidal_rule.c -o $trapezoidal_rule/parallel_trapezoidal_rule -Wall -pedantic

    cc $trapezoidal_rule/serial_trapezoidal_rule.c -o $trapezoidal_rule/serial_trapezoidal_rule -Wall -pedantic

    mpicc $_sort/test2.c -o $_sort/parallel_sort -Wall -pedantic

    cc $_sort/serial_sort.c -o $_sort/serial_sort -Wall -pedantic -ansi
}

run_parallel_algorithms()
{
    echo "----------------------------------"

    rounds=5

    for cores in 2 4 8; do
    for cores in 2; do
        for input in $2 $3 $4 $5; do
            for round in $(seq $rounds); do

                [[ "$1" == "pi" ]] && mpirun -np $cores --oversubscribe $generate_pi/serial_pi $input [[ "$1" == "trapezoid" ]] && mpirun -np $cores --oversubscribe $trapezoidal_rule/parallel_trapezoidal_rule $input

                [[ "$1" == "_sort" ]] && mpirun -np $cores --oversubscribe $_sort/parallel_odd_even_transposition_sort $input

            done
        done
    done

}


run_serial_algorithms()
{
    rounds=5

    for input in $2 $3 $4 $5; do
        for round in $(seq $rounds); do
            [[ "$1" == "pi" ]] && $generate_pi/serial_pi $input

            [[ "$1" == "trapezoid" ]] && $trapezoidal_rule/serial_trapezoidal_rule $input

            [[ "$1" == "_sort" ]] && $_sort/serial_sort $1 $input
        done
    done
    
    use it to the sum o 5 values time
    cat serial_sort.csv | paste -s -d+ | bc --
}


remove_executables()
{
    rm -f $generate_pi/serial_pi
    rm -f $generate_pi/parallel_pi

    rm -f $trapezoidal_rule/serial_trapezoidal_rule
    rm -f $trapezoidal_rule/parallel_trapezoidal_rule

    rm -f $_sort/serial_sort
    rm -f $_sort/parallel_sort
}

# echo "[>] Compiling program"
# echo "---------------------------------"
compiling_all_sources


echo "[>] Run serial codes"
echo "---------------------------------"
run_serial_algorithms _sort

echo "[>] Run parallel codes"
run_parallel_algorithms

echo "[>] Removing executables"
echo "----------------------------------"
remove_executables

exit 0
