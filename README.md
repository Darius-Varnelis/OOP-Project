# OOP-Project
## Introduction
This program was written as a project for an Object Oriented Programming course. The purpose of the program is to read or generate student data which will then be used to calculate their final grades.

## Build
The project uses CMake (3.16 or newer) and requires a C++17 compiler.
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
When using a multi-config generator (e.g. Visual Studio), build with:
```bash
cmake --build build --config Release
```
The program reads and writes data files in its working directory, so run it from the folder where you want the generated files to be stored.

## Usage
Upon running the compiled program, the user will be prompted with several options to decide the behavior of the program. 
```math
Final grade = 0.4 \cdot average\space or\space median + 0.6 \cdot exam
```

## Structure
### main.cpp
This file houses all the logic for the program, including the options that the user must select.
### manual.cpp and manual.h
These files contain the logic required for user interaction through the console, as well as the logic for executing program functions not related to benchmarking.
### nustatymai.h
This file stores all the enum classes that are used to store program settings.
### results.cpp and results.h
These files contain the functions for outputting benchmark results in a Markdown table.
### studentas.cpp and studentas.h
These files contain features directly related to the student entity in the program, such as name and last name, grade average and final grade functions.
### testai.cpp and testai.h
These files contain the logic for the benchmarking mode of the program.
### failai.cpp and failai.h
These files contain functions related to reading data from and writing data to files.
### timer.h
This file contains the timer class used for benchmarking.
### utils.cpp and utils.h
These files contain helper functions used in aligning Lithuanian text, inputting yes or no answers and counting averages or medians.


## Benchmarking
Upon running the app, users have the option to select a benchmarking mode. During the benchmarking mode the program randomly generates 5 files with varying amounts of students which will then be used to test the program's performance on analyzing them. Students are put in a failing group *(nuskriaustukai)* if their grade is lower than 5 and a passing group *(kietukai)* if their grade is 5 or greater.
All steps are timed and repeated 5 times, the average time for each step is calculated and output to the console.

The goal of the benchmark is to compare performance between the Vector and List containers in this app and to decide which one fits the program better.

## Benchmark Results

### Vector
|Student count|Average file read time|Average final grade calculation time|Average sorting time|Average grouping time|Average failed student output time|Average passing student output time|Average processing time|
|---|---|---|---|---|---|---|---|
|1000|0.005s|0.000s|0.000s|0.000s|0.002s|0.001s|0.011s|
|10000|0.041s|0.000s|0.002s|0.001s|0.008s|0.008s|0.064s|
|100000|0.415s|0.003s|0.021s|0.012s|0.070s|0.072s|0.598s|
|1000000|4.268s|0.029s|0.229s|0.068s|0.767s|0.769s|6.136s|
|10000000|44.835s|0.290s|2.741s|0.835s|8.490s|8.063s|65.260s|


### List
|Student count|Average file read time|Average final grade calculation time|Average sorting time|Average grouping time|Average failed student output time|Average passing student output time|Average processing time|
|---|---|---|---|---|---|---|---|
|1000|0.005s|0.000s|0.000s|0.000s|0.002s|0.001s|0.012s|
|10000|0.046s|0.001s|0.002s|0.001s|0.009s|0.009s|0.071s|
|100000|0.501s|0.007s|0.039s|0.031s|0.093s|0.087s|0.763s|
|1000000|4.385s|0.056s|0.818s|0.413s|0.834s|0.841s|7.352s|
|10000000|45.701s|0.608s|15.013s|5.730s|8.855s|8.476s|84.389s|


### Testing Conditions
Test system:
- CPU: AMD Ryzen AI 9 HX 370 (12 cores / 24 threads)
- RAM: 32 GB LPDDR5X
- Storage: NVMe SSD
- OS: Windows 11
- Compiler: GCC 15.2.0 (MinGW, bundled with CLion 2026.2.2)
- Power: AC (plugged in), Balanced profile
- Results: Average of 5 runs on pre-generated files
- Files were generated once per build
- Optimizations used: -O3 -DNDEBUG
- Sorted by final grade descending

### Benchmark Conclusion
The results show that Vector is the better fit for this program. At 10,000,000 students the total processing time was 65.3s with Vector versus 84.4s with List, about 29% slower. The gap starts to show at 100,000 students and widens as the data grows.

Reading the file and writing the results take almost the same time with both containers, because these steps are dominated by text parsing and disk I/O rather than by the container. The difference comes from three steps:

- **Sorting** showed the largest gap: at 10,000,000 students it took 2.7s with Vector and 15.0s with List, roughly 5.5x slower. Vector uses `std::sort` (introsort), which needs random-access iterators and works on elements stored next to each other in memory. List cannot use `std::sort` and relies on its own `list::sort` (merge sort) which is significantly slower.
- **Grouping** was about 7x slower with List (0.8s vs 5.7s). Each `push_back` into a List allocates a new node on the heap and copies the student into it. Vector only reallocates occasionally, since its capacity grows geometrically. The List version could be improved by moving nodes between lists with `splice`, which needs no allocation or copying.
- **Final grade calculation** was about 2x slower with List. The difference comes from memory layout: Vector stores its elements next to each other, while List elements are scattered all across memory, which makes it more difficult for the CPU to access.

In short, List's strengths (easy insertion and removal in the middle) are not used by this program, while its weaknesses affect every step that touches the container. Vector is therefore the better choice.

## Disclaimer
The generation of the text files is likely to take a large amount of time (about 30 seconds) as well as a large amount of storage (about 1GB). Further processing of the files (5 runs for every file) takes about 6 minutes on the release build and about 15 minutes on the debug build.
