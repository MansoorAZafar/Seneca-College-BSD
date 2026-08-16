# Lab Activity 2 (5%)
## Due Date - Friday May 29, 2026 (Late Policy: 10% per day)

## Learning Outcomes

- use the MPI's collective functions to distribute work across processes
- design a program that uses a computer's GPU capability
- make implementation decisions using emphrical data


## Environment Setup

Review the following.  (Both environments are available on the lab machine):

- [MS-MPI v10.1.3](https://learn.microsoft.com/en-us/archive/blogs/windowshpc/how-to-compile-and-run-a-simple-ms-mpi-program) 
- [NVIDIA's CUDA Programming Guide (Part 1 and 2)](https://docs.nvidia.com/cuda/cuda-programming-guide/part2.html)


## Question 1: MPI Development (40%)

The given program populates an array with random data, discretize the data in that array into zero and unit values, and report the number of elements containing zero values and the number of elements containing unit values.  

1. Execute on your *assigned virtual machine* with different array sizes and collect timing data.
2. Complete the partial MPI implementation provided.
3. Here we assume that processes will all be run on the same machine.  Again execute with different array sizes. Experiment by spawning off your tests with 4,8, 16 and 32 processes. Provide a brief summary of your results using visualizations of the data for support.



## Question 2: GPU programming (60%)

In this exercise, you will implement a CUDA based program which performs matrix multiplication. As a review, given matrix $A$ and $B$, the elements of $A \dot B$ can be computed by multiplying elements from the $i^{th}$ row and $j^{th}$ column and summing them. If $C = AB$, where $A$ and $B$ are square matrices, then the elements of C can be computed as defined below. 

$$ c_{ij} = a_{i1} b_{1j} + a_{i2} b_{2j}  \dots + a_{in} b_{nj} $$


```math
\begin{bmatrix}
a_{11} & a_{12} & ... & a_{1n} \\
a_{21} & ... & ... & a_{2n} \\
...    & ... & ... & ...   \\
a_{n1} & ... & ... & a_{nn} \\
\end{bmatrix}
\begin{bmatrix}
b_{11} & b_{12} & ... & b_{1n} \\
b_{21} & ... & ... & b_{2n} \\
...    & ... & ... & ...   \\
b_{n1} & ... & ... & b_{nn} \\
\end{bmatrix}
=
\begin{bmatrix}
c_{11} & c_{12} & ... & c_{1n} \\
c_{21} & ... & ... & c_{2n} \\
...    & ... & ... & ...   \\
c_{n1} & ... & ... & c_{nn} \\
\end{bmatrix}
```


1. Use the "correctness test" code snippet in the given file to create a separate sequential version of the solution. Ensure that the size of the matrix can be passed in using the command line.  Use the code from the given file to initialize the matrices.

2. Modify the given file to create a solution which exploits a machine's GPU computing power.
   
3. Use both files to collect timing data by executing tests on your *assigned virtual machine*. Summarize your results using visualizations to compare the solutions.  Provide a brief analysis based on your findings.

### Deliverables

-  question 1 - MPI modified code, summary report
-  question 2 - sequential solution, GPU modified code, summary report


The reports are to be submitted in a **single pdf file** (Section 1 - Question 1, Section 2 - Question 2) on **Blackboard**.  Code, files containing the raw data collected and files used to generate visualizations should be uploaded to **your assigned GitHub repository**.


### NOTE:
- To run the `make.bat` file, the terminal needs to be MVSC, it will build the `q1parallel.c` file with microsofts MPI