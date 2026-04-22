# Menu-Driven-Quick-Sort-MPI

This repository contains a menu-driven implementation of the Quick Sort algorithm using MPI (Message Passing Interface) for parallel computing. The program allows users to interactively select sorting options and demonstrates parallel sorting on distributed systems.

## Features

- Interactive menu for user input and sorting options.
- Parallel Quick Sort implementation using MPI.
- Support for sorting arrays of integers.
- Displays sorted results and execution time.

## Prerequisites

- Ubuntu 24.04.4 LTS (or compatible Linux distribution).
- MPI library installed (e.g., OpenMPI).
- C compiler (e.g., GCC).

## Installation

1. Ensure MPI is installed:
    ```
    sudo apt update
    sudo apt install openmpi-bin openmpi-doc libopenmpi-dev
    ```

2. Clone the repository:
    ```
    git clone https://github.com/saipy10/Menu-Driven-Quick-Sort-MPI.git
    cd Menu-Driven-Quick-Sort-MPI
    ```

## Usage

1. Compile the code:
    ```
    mpicc quick_sort_mpi.c -o quick_sort_mpi
    ```
    (Replace `quick_sort_mpi.c` with the actual source file name if different.)

2. Run the program with a specified number of processes (e.g., 4):
    ```
    mpirun -np 4 ./quick_sort_mpi
    ```

3. Follow the on-screen menu to input array elements and select sorting options.

## Example

- Launch the program as above.
- Choose option to enter array size and elements.
- Select Quick Sort to perform parallel sorting.
- View the sorted array and timing results.

## Contributing

Feel free to submit issues or pull requests for improvements.

## License

This project is licensed under the MIT License.