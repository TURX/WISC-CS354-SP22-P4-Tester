// CS354 SP22 Project 4 Sample Tester
// by UW-Madison CS354

#include "mem.h"
#include <stdio.h>

int main() {
    Initialize_Memory_Allocator(1600);
    Mem_Dump();
   
    char *p = Mem_Alloc(1);
    if (p == NULL) {
        printf("Allocation failed\n");
        exit(0);
    }
    p[0] = 'c';
    Mem_Dump();
    
    Free_Memory_Allocator();
    return 0;
}
