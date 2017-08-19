#!/bin/bash

# ipcrm -a; #in case of a previous CTRL C
# make re;

for ((i=1;i<105;i++)); do
    for ((j=1;j<7;j++)); do
	     ./lemipc `pwd` $j&
    done
done
