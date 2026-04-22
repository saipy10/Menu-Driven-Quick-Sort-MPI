#!/bin/bash

make clean
make

echo ""
echo "========= MENU ========="
echo "1. Sort by Product Name (A-Z)"
echo "2. Sort by Price Low to High"
echo "3. Sort by Price High to Low"
echo "4. Sort by Rating High to Low"
echo "5. Sort by Rating Low to High"
echo ""
read -p "Enter Choice : " choice

export SORT_CHOICE=$choice

# Try with --oversubscribe to fix WSL OpenMPI process spawning issue
mpirun --allow-run-as-root --oversubscribe -np 4 ./quicksort_mpi
