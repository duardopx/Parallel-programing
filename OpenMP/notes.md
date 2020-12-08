#Variables scope

## shared

Share the especifyed variable with other threads.

## private

Dont share the variables and dont initialize them on the threads.

## first_private

the variables are initialized with the values before the parallel region be declared

## last_private

Return the values of the last iteraction in an for

## defualt

if the varibles are not declared with some scope, it's shared

# Reduce

It's apply some operation in an especific target

# For

Dived the number of interactions with some threads
openmp dont check de dependencies
