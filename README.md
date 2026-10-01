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
## Disclaimer
The generation of the text files is likely to take a long amount of time (about 5 minutes) as well as a large amount of storage (about 1gb). 



