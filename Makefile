# CS354 SP22 Project 4 Sample Tester
# Authored by Ruixuan Tu

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MY_CC := gcc
endif
ifeq ($(UNAME_S), Darwin)
	MY_CC := clang
endif

all: a.out
run: a.out
	./a.out <in.txt
test: a.out
	./a.out <in.txt >out.txt
	diff -w out.txt ans.txt
a.out: mem.h mem_init.c mem_functions.c driver_alloc_custom.c
	$(MY_CC) -g mem_init.c mem_functions.c driver_alloc_custom.c -Wall
clean: test_clean
	rm -rf *.out *.out.dSYM *.exe *.exe.dSYM test_output
test_compile: driver_test.exe
driver_test.exe: mem.h mem_init.c mem_functions.c driver_test.c
	$(MY_CC) -g mem_init.c mem_functions.c driver_test.c -o driver_test.exe -Wall
test_clean:
	rm -rf driver_test.c driver_test.exe driver_test.exe.dSYM
