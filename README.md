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

## Screenshots of outputs/test cases
### Output of best fit:  
![](https://cdn.discordapp.com/attachments/675206324086374400/1000238182794805248/allocator.png)  
### Output of worst fit: (NOTE: Worst fit performed better than best fit by allocating memory to process P5)  
![](https://cdn.discordapp.com/attachments/971437891622404218/1000241197085896774/unknown.png)  
## Contributions
- main() - Alex
- firstFit() - Tatiana
- bestFit() - Tatiana
- worstFit() - Tatiana
- requestMemory() - Tatiana
- releaseMemory() - Alex
- compactMemory() - Alex
- status() - Tatiana
- error fixing - Alex
## About Developers
- [Alex Lau](https://github.com/BobahhBoi)
- [Tatiana Olenciuc](https://github.com/tygragamand)
## License
This repository is licensed under the MIT License, explained further in the license file.
