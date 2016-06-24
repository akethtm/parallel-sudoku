#!/bin/bash
clear
g++ solver.cpp checks.cpp -o solver -fopenmp
echo "Good morning, world."
export OMP_PROC_BIND=true
time ./solver sample-puzzle-2-hard 
