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

![](images/Screenshot_Options.png)

The following formula is used for final grade calculation:
```math
Final grade = 0.4 \cdot average\space or\space median + 0.6 \cdot exam
```

## Structure
Most of the logic is written as function templates over a generic `Konteineris` type, so the same code works with both `std::vector<Studentas>` and `std::list<Studentas>`. The container is chosen once, at runtime, in `main.cpp`. Where the two containers need different code (sorting), `if constexpr` picks the right version at compile time.

### main.cpp
The program's entry point. It asks the user to choose a mode (manual entry, random generation, reading from a file, or benchmark), a sort field and order, a container, an output target and which statistic to show. It then calls the matching template function with either `std::vector<Studentas>` or `std::list<Studentas>`.

### studentas.h / studentas.cpp
- `struct Studentas`: first name, last name, homework grades, exam grade and final grade.
- `skaiciuotiGalutini()`: calculates the final grade (0.4 × homework average + 0.6 × exam).
- `rusiuotiStudentus()`: sorts by first name, last name or final grade, in ascending or descending order. Uses `std::sort` for `vector` and the member `list::sort()` for `list`.
- `skirstytiStudentus()`: splits students into failing (*nuskriaustukai*, final grade < 5) and passing (*kietukai*, final grade ≥ 5) groups.

### manual.h / manual.cpp
Console interaction and the non-benchmark modes:
- `nustatymai()`, `ivestiSk()`, `taipArNe()`: menu prompts and validated number and yes/no input.
- `ivestiRanka()`: manual entry, with an option to generate grades randomly. After each student is added, it prints the student's address in memory.
- `nuskaitytiIsFailo()`: reads, processes and outputs students from an existing file.
- `rasytiAntraste()`, `rasytiStudenta()`, `rasytiGrupe()`: write the formatted results table to the console or a file.

### failai.h / failai.cpp
File I/O:
- `generuotiFaila()`: generates a test file with *n* random students. The whole file is built in a `stringstream` first and written to disk in one go.
- `nuskaitytiStudentus()`: reads a student file into any container.
- `isvestiStudentus()`: writes a group of students to a file.
- `arFailaiEgzistuoja()`: checks whether the benchmark files already exist, so they don't have to be regenerated.

### testai.h / testai.cpp
The benchmark. `testas()` times each step (read, final grade calculation, sort, grouping, writing both groups) on one file. `testuPaleistuvas()` repeats the test 5 times per file for the chosen container and averages the results.

### results.h / results.cpp
`struct Rezultatai` stores the average time for each step. `spausdintiLentele()` exports all results as a Markdown table, which is where the tables in this README come from.

### nustatymai.h
The `enum class` types that hold the program's settings: `Rezimas`, `Struktura`, `Rusiuoti`, `Tvarka`, `Statistika` and `Isvedimas`.

### timer.h
A small `Timer` class built on `std::chrono::high_resolution_clock`, with `reset()` and `elapsed()`.

### utils.h / utils.cpp
Helpers: `vidurkis()` (average), `mediana()` (median) and `utf8Plotis()`, which corrects `setw` column width for Lithuanian UTF-8 characters.

### kursiokai.txt
A small sample student file for testing the read-from-file mode.


## Benchmarking
Upon running the app, users have the option to select a benchmarking mode. During the benchmarking mode the program randomly generates 5 files with varying amounts of students which will then be used to test the program's performance on analyzing them. Students are put in a failing group *(nuskriaustukai)* if their grade is lower than 5 and a passing group *(kietukai)* if their grade is 5 or greater.
All steps are timed and repeated 5 times, the average time for each step is calculated and output to the console.

The goal of the benchmark is to compare performance between the Vector and List containers in this app and to decide which one fits the program better.

![](images/Screenshot_Benchmark.png)

## Benchmark Results

### Vector
|Student count|Average file read time|Average final grade calculation time|Average sorting time|Average grouping time (Original Method)|Average grouping time (Method 1)|Average grouping time (Method 2)|Average grouping time (Original Method with Partition)|Average grouping time (Method 2 with copy_if and remove_if)|Average failed student output time|Average passing student output time|Average processing time|
|---|---|---|---|---|---|---|---|---|---|---|---|
|1000|0.005s|0.000s|0.000s|0.000s|0.000s|0.001s|0.000s|0.001s|0.002s|0.002s|0.017s|
|10000|0.051s|0.001s|0.002s|0.001s|0.002s|0.005s|0.001s|0.003s|0.010s|0.009s|0.095s|
|100000|0.462s|0.003s|0.023s|0.008s|0.024s|0.052s|0.023s|0.040s|0.081s|0.077s|0.834s|
|1000000|4.611s|0.029s|0.280s|0.066s|0.278s|0.588s|0.281s|0.449s|0.784s|0.752s|8.718s|
|10000000|48.629s|0.301s|2.840s|0.969s|3.768s|7.902s|3.496s|5.195s|7.744s|7.928s|98.032s|



### List
|Student count|Average file read time|Average final grade calculation time|Average sorting time|Average grouping time (Original Method)|Average grouping time (Method 1)|Average grouping time (Method 2)|Average grouping time (Original Method with Partition)|Average grouping time (Method 2 with copy_if and remove_if)|Average failed student output time|Average passing student output time|Average processing time|
|---|---|---|---|---|---|---|---|---|---|---|---|
|1000|0.007s|0.000s|0.000s|0.000s|0.002s|0.004s|0.002s|0.004s|0.002s|0.002s|0.032s|
|10000|0.060s|0.002s|0.003s|0.002s|0.022s|0.036s|0.023s|0.039s|0.009s|0.010s|0.246s|
|100000|0.576s|0.019s|0.035s|0.035s|0.226s|0.361s|0.220s|0.356s|0.081s|0.081s|2.451s|
|1000000|5.916s|0.203s|0.912s|0.498s|2.827s|4.208s|3.051s|4.450s|0.854s|0.823s|28.461s|
|10000000|65.188s|2.059s|16.488s|10.842s|27.195s|49.420s|26.148s|41.602s|9.061s|9.110s|340.677s|

### Memory usage when grouping 10,000,000 students
|Method|Peak memory used (MiB)|
|---|---|
|Original|1665 MiB|
|Method 1|2688 MiB|
|Method 2|1665 MiB|
|Method 1 with Partition|991 MiB|
|Method 2 with copy_if and remove_if|1665 MiB| 



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

![](images/Screenshot_Sizes.png)
