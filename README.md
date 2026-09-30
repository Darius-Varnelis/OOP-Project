# OOP-Project
## Introduction
This program was written as a project for an Object Oriented Programming Course. The purpose of the program in this branch is to take generate files with a large amount of random student grade data, which must then be separated into two groups based on the students' final grade. Additionally, both the generation and sorting step are timed to aid in improving performance.
## Usage
This program does all steps automatically upon running main.cpp. Student data is generated and put into 5 separate files with 1k, 10k, 100k, 1 million and 10 million entries. For each of these data tables, two new files are generated, where the students are sorted into two groups based on their final grade:
```math
Final grade = 0.4 \cdot average  + 0.6 \cdot exam
```
Students are put in a failing group if their grade is lower than 5.
## Structure
### Studentas.cpp and Studentas.h
These files contain features directly related to the student entity in the program, such as name and last name, grade average and final grade functions.
### Utils.cpp and Utils.h
These files contain helper functions that aid in better aligning tables that use Lithuanian characters.
### Failai.cpp and Failai.H
These files contain functions related to reading and inputing data into files.
### main.cpp
This file includes calls the above mentioned features to achieve the desired result of the program.
## Disclaimer
The generation of the text files is likely to take a long amount of time (about 5 minutes) as well as a large amount of storage (about 1gb).
