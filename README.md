# OOP-Project
## Introduction
This program was written as a project for an Object Oriented Programming Course. The purpose of the program in this branch is to take generate files with a large amount of random student grade data, which must then be separated into two groups based on the students' final grade. Additionally, both the generation and sorting step are timed to aid in improving performance.
## Usage
Upon running main.cpp the user will be prompted to decide by which student value they wish the output data to be sorted by. If previously generated student data doesn't exist, it will be automatically generated using the "random" library and put into 5 separate files with 1k, 10k, 100k, 1 million and 10 million entries. If data already exists, the user is prompted whether they want to generate new files or keep the old ones. For each of these data tables, two new files are generated, where the students are sorted into two groups based on their final grade:
```math
Final grade = 0.4 \cdot average  + 0.6 \cdot exam
```
Students are put in a failing group *(nuskriaustukai)* if their grade is lower than 5 and a passing group *(kietukai)* if their grade is 5 or greater. 
All steps are timed and repeated 5 times, the average time for each step is calculated and outputted to the console.
## Structure
### Studentas.cpp and Studentas.h
These files contain features directly related to the student entity in the program, such as name and last name, grade average and final grade functions.
### Utils.cpp and Utils.h
These files contain helper functions used in aligning Lithuanian text, inputting yes or no answers and counting averages.
### Failai.cpp and Failai.H
These files contain functions related to reading and inputing data into files.
### Timer.h
This file contains the timer function used for benchmarking.
### Rezultatai.cpp and Rezultatai.h
These files contain the functions for outputting benchmark results in a Markdown table.
### main.cpp
This file includes calls the above mentioned features to achieve the desired result of the program.

## Benchmark Results

### Release
|Student count|File generation time|Average file read time|Average final grade calculation time|Average sorting time|Average grouping time|Average failed student output time|Average passing student output time|Average processing time|
|---|---|---|---|---|---|---|---|---|
|1000|0.008s|0.003s|0.000s|0.000s|0.000s|0.003s|0.002s|0.016s|
|10000|0.013s|0.032s|0.000s|0.007s|0.003s|0.014s|0.012s|0.078s|
|100000|0.303s|0.307s|0.003s|0.051s|0.010s|0.079s|0.079s|0.537s|
|1000000|2.215s|3.430s|0.026s|0.842s|0.083s|0.973s|0.995s|6.359s|
|10000000|22.274s|29.573s|0.296s|12.912s|1.232s|9.895s|9.851s|63.767s|




### Debug
|Student count|File generation time|Average file read time|Average final grade calculation time|Average sorting time|Average grouping time|Average failed student output time|Average passing student output time|Average processing time|
|---|---|---|---|---|---|---|---|---|
|1000|0.009s|0.005s|0.000s|0.005s|0.001s|0.003s|0.003s|0.027s|
|10000|0.027s|0.048s|0.001s|0.071s|0.011s|0.019s|0.015s|0.179s|
|100000|0.326s|0.399s|0.010s|0.554s|0.065s|0.093s|0.100s|1.231s|
|1000000|5.960s|4.970s|0.112s|8.028s|0.661s|1.262s|1.167s|16.210s|
|10000000|20.690s|39.650s|1.008s|93.535s|8.547s|13.156s|12.385s|168.291s|

### Testing Conditions
Test system:
- CPU: AMD Ryzen AI 9 HX 370 (12 cores / 24 threads)
- RAM: 32 GB LPDDR5X
- Storage: NVMe SSD
- OS: Windows 11
- Compiler: GCC 15.2.0 (MinGW, bundled with CLion 2026.2.2)
- Power: Batter power, Silent profile
- Results: average of 5 runs on pre-generated files, files were generated once
- Optimizations used: Debug:   -g (no optimization, -O0); Release: -O3 -DNDEBUG
  



## Disclaimer
The generation of the text files is likely to take a long amount of time (about 5 minutes) as well as a large amount of storage (about 1gb). 



