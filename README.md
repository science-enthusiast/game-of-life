# Conway's game of life

`Makefile` is used for building the project. Executables for both Linux (Ubuntu) and Windows will be produced.

Note 1: To compile for Windows in Linux, MinGW needs to be installed. Refer to `.github/workflows/golAction.yml` for installing MinGW.\
Note 2: C++17 or later is needed.

Once MinGW is installed, just running `make` from root folder should produce the executables for Linux and Windows. You will find them in the `bin` folder. 
 
## CLI usage

The following parameters are mandatory:\
--input: input file path as string. Data must be in the format described below.\
--iterations: A positive integer.

The following parameter is optional:\
--all: It will print all the iterations.

Example:

```shell
./game_of_life_exe --input gol_init.txt --iterations 1000 --all
```

## Input file

Input should be a text file.\
One empty (dead) cell is encoded as '_', one living cell is encoded as '*'.\
Lines terminated by newline character '\n'.\
No other characters should be present.\
In a valid input, all lines must have same length.

## Testing

Testing is based on CppUnit. Refer to `.github/workflows/golAction.yml` for installing CppUnit. 
Refer `test` folder for the test case. 
