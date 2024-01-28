# MPI-Sorting-Algorithms
## Overview
This project focuses on implementing serial and parallel versions of QuickSort and MergeSort algorithms to efficiently sort arrays. The assignment is part of the Parallel and Distributed Computing course, and it involves analyzing the performance of these algorithms in terms of GFlops.

### Serial Implementation
### Task 1
* Serial Sorting:

Serial versions of QuickSort and MergeSort are implemented for arrays of sizes 211, 213, 215, and 217.
Arrays are generated and saved to files.
Command line parameters identify the input, and sorted results are saved to corresponding output files.
Performance Analysis:

The performance of both algorithms is evaluated in terms of GFlops for each array size.
Plots illustrating the performance are generated.
### Parallel Implementation
### Task 2
* Parallel Sorting:

Parallel versions of QuickSort and MergeSort are implemented using MPI basic and collective communication functions.
Input arrays are divided into smaller parts, and each processor handles sorting operations on its assigned portion.
Leaf processes are allocated arrays based on specific sizes calculated from the last digits of the roll number.
Cluster Setup:

The parallel implementation uses a cluster setup of 2 machines for distributing tasks among parallel machines.
Performance Analysis:

The performance of both parallel algorithms is analyzed in terms of GFlops for each array size.
Plots are generated to visualize the parallel performance considering different scenarios:
Using 2 machines in the cluster.
Using 1 machine in the cluster.
### Getting Started
* Clone the Repository:

git clone https://github.com/your-username/mpi-sorting-algorithms.git
* Build and Run:

Navigate to the project directory and compile the code.
mpicc -o main main.c -lm
Execute the compiled program.
php
Copy code
mpirun -np <num_processes> ./main <array_size>
* Review Results:

Examine the output files to see the sorted arrays and performance analysis results.
Check the generated plots for insights into the algorithms' efficiency.
### Dependencies
MPI library for parallel implementation
Math library for mathematical operations
### Contributing
Feel free to contribute by opening issues or submitting pull requests. Your feedback and improvements are highly appreciated.
