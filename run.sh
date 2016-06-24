#!/bin/bash
clear
echo "Good morning, world."
export OMP_PROC_BIND=true
time ./solver sample-puzzle-2-hard 
