# Lab Activity 3 (5%) - Bonus (2.5%)
## Due Date - Friday June 19, 2026 (Late Policy: 10% per day)

## Learning Outcomes

- use OpenMP to parallize an algorithm
- identify false sharing in a parallelized program
- compare approaches to parallelizing a region of code 


## Environment Setup

Review the following:

- Course Text: Section 8.12.2 (False Sharing)
- [Introduction of OpenMP YouTube Series - Tim Mattson - Modules 1-8](https://www.youtube.com/playlist?list=PLLX-Q6B8xqZ8n8bwjGdzBJ25X2utwnoEG)
- [Enabling OpenMP support in Visual Studio](https://learn.microsoft.com/en-us/cpp/build/reference/openmp-enable-openmp-2-0-support?view=msvc-170) 


## Question 1: OpenMP Development

The [given program](pi_serial.cpp) implements the differentiation of the function below by approximating the area under its curve. 

$$ \int \frac{4}{1+x^2}~dx \approx \pi $$

1. Compile the [given code](pi_serial.cpp) using both "no-optimization" and "max optimization for speed" options to generate two different binaries.
2. Gather timing data when executing both versions on either *the lab machine or own* (set the number of steps to 1000000000). 
3. Identify the region of the code which can be parallelized. Justify your choice in the summary report.
4. Create 3 different parallel versions of this code using OpenMP.
  - *naive*, accumulate partial sums in each thread within a one dimensional array
  - *padded*, convert the array into a two dimensional array
  - *synchronized*, use a single accumulutor variable as is done in the serial verison
5. Again, create 2 binaries ("no-opt" and "max-opt") for each version    
6. OpenMP allows you to control the max number of threads spawned using an *environment variable*. Execute all 6 files to collect timing data by executing tests on your *assigned virtual machine*. The tests should include max thread settings of 1,2,4,8,16,32 and 64. Summarize your results using an appropriate visualization(s) to compare the settings.  Provide a brief analysis based on your findings.

### Optional Bonus - 2.5%

Implement the above using Thrust. Compile and execute for CUDA and OpenMP backends. In order to receive bonus credit, you must present your work to the instructor.  Details about how to do so will be annouced later. 

### Deliverables

-  summary report

The report is to be submitted in a single file on **Blackboard**.  Code, files containing the raw data collected and files used to generate visualizations should be uploaded to **your assigned GitHub repository**.



