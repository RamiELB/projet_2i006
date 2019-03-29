#! /bin/bash

i=1

for fic in $(ls ./Instance_Netlist/ibm*)
do
    ./benchmarking $fic
    
done > "perf.tmp"

for nb in $(cat "perf.tmp")
do
    if [ $i -eq 1 ] 
    then 
        echo "$nb" >> "naif.txt"
        i=2
        continue
    fi
    
    if [ $i -eq 2 ] 
    then 
        echo "$nb" >> "balayage.txt"
        i=3
        continue
    fi
    
    if [ $i -eq 3 ] 
    then 
        echo "$nb" >> "avl.txt"
        i=1
        continue
    fi
done
