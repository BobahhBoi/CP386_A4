# CP386 Assignment 4
## Features
This repository demonstrates the use of 3 algorithms; First Fit Algorithm, Best Fit Algorith, and Worst Fit Algorithm.
## Makefile
Below is the code in the makefile"
```
CC = gcc
CFLAGS = -std=gnu99
TARGET = allocation  
OBJFILES = allocation.o
all: $(TARGET)

allocation: allocation.c
	$(CC) $(CFLAGS) -o allocation allocation.c
	
run: allocation
	./allocation 1048576
clean:
	rm -f $(OBJFILES) $(TARGET) *~
```
The makefile is used to help students test their code.
When using the makefile, it will run the allocation.c file with the test case of ```1048576```

## Screenshots of output
## Contributions
## About Developers
- [Alex Lau](https://github.com/BobahhBoi)
- [Tatiana Olenciuc](https://github.com/tygragamand)
## License
This repository is licensed under the MIT License, explained further in the license file.
