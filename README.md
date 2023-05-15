C generics
==========

Generic implementations of some data structures and algorithms in C.

## Usage

This repository contains only generic implementations. If you want to use one of them, you have to
create a concrete implementation. This can be done by including the `*.c` file in one of the
subdirectories of the `src/` directory. Before the `#include`, you will have to configure all the
parameters using `#define`s. To see what parameters you can change look at the `default.h` file. To
create a header file with the definition of the methods, you can use the `*.h` file. Here you will
also have to configure the parameters before the include statement. After the `#include`, you should
also include the `defualt-end.h` file to clear all the parameters. This is required, because
otherwise including multiple concrete implementations will result in errors.

If you use any of the data structures using hashes (e.g., hash-table or hash-set) you can also use
the default hash functions in `src/hash.c`. In general however these are designed mainly just for
use in the test cases.

## Development

There are two directories in this repository:
* `src/` This directory is for all the code of the generic implementations. 
* `tests/` This directory contains all the tests for all implementations.

For every subdirectory in `src/` there are four files:
* `default.h` This file includes all the configurable parameters for each implementation containing
default values. This file is included from the `*.h` file.
* `default-end.h` This file is not included by default, but can be used to `#undef` all the
parameters in the `default.h` file.
* `*.h` This file includes the declarations of all methods and data types implemented in the `*.c`
file. When creating a concrete implementation, this file can be included in the header `.h` file.
* `*.c` This file contains the generic implementation. This file should be included in the source
`.c` of the concrete implementation.

Every subdirectory in `src/` should also have a corresponding directory in `tests/`. These can
contain other subdirectories for different parameters which then contain a number of c source files.
Every one of these c files should be a complete program (i.e., containing a main function). The
tests can then use asserts, exit with non-zero error code or write to `stderr` to indicate an error.
For tests to be considered correct, they must not include undefined behavior or memory leaks.

