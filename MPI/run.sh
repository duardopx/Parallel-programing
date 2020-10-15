#!/bin/bash

# File paths
generate_pi="./generate-pi"
trapezoidal_rule="./trapezoidal-rule"

compiling_all_sources()
{
    mpicc $generate_pi/parallel_generate_pi.c -o $generate_pi/parallel_pi -Wall -pedantic

    cc $generate_pi/serial_generate_pi.c -o $generate_pi/serial_pi -Wall -pedantic 

    mpicc $trapezoidal_rule/parallel_trapezoidal_rule.c -o $trapezoidal_rule/parallel_trapezoidal_rule -Wall -pedantic
    
    cc $trapezoidal_rule/serial_trapezoidal_rule.c -o $trapezoidal_rule/serial_trapezoidal_rule -Wall -pedantic 

    echo "All souces are compiled correctly. "$'\n'
}

run_parallel_algorithms()
{
    echo 
    echo "----------------------------------"

    rounds=5

    for cores in 2 4 8; do
        for input in $2 $3 $4 $5; do 
            for round in $(seq $rounds); do

                [[ "$1" == "pi" ]] && mpirun -np $cores --oversubscribe $generate_pi/serial_pi $input

                [[ "$1" == "trapezoid" ]] && mpirun -np $cores --oversubscribe $trapezoidal_rule/parallel_trapezoidal_rule $input

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
        done
    done
}


remove_executables()
{
    rm -f $generate_pi/serial_pi
    rm -f $generate_pi/parallel_pi
    rm -f $trapezoidal_rule/serial_trapezoidal_rule
    rm -f $trapezoidal_rule/parallel_trapezoidal_rule
}

echo "[>] Compiling program"
echo "---------------------------------"
compiling_all_sources


echo "[>] Run serial codes"
echo "---------------------------------"
time run_serial_algorithms pi 100000 2000000 3000000 40000000
echo "---------------------------------"
time run_serial_algorithms trapezoid 100000 2000000 3000000 40000000

echo "[>] Run parallel codes"
echo "---------------------------------"
time run_serial_algorithms pi 100000 2000000 3000000 40000000
echo "---------------------------------"
time run_serial_algorithms trapezoid 100000 2000000 3000000 40000000


echo "[>] Removing executables"
echo "----------------------------------"
remove_executables


exit 0
