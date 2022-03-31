// CS354 SP22 Project 4 Sample Tester
// by UW-Madison CS354

#include "mem.h"
#include <stdio.h>

int main() {
    Initialize_Memory_Allocator(1600);
    Mem_Dump();
   
    int *p1 = Mem_Alloc(8);
    int *p2 = Mem_Alloc(8);
    int *p3 = Mem_Alloc(8);
    int *p4 = Mem_Alloc(8);
    int *p5 = Mem_Alloc(8);
    int *p6 = Mem_Alloc(8);
    int *p7 = Mem_Alloc(8);
    int *p8 = Mem_Alloc(8);
    int *p9 = Mem_Alloc(8);
    Mem_Dump();

    printf("Free P7\n");
    Mem_Free(p7);
    Mem_Dump();

    printf("Free P6\n");
    Mem_Free(p6);
    Mem_Dump();

    printf("Free P8\n");
    Mem_Free(p8);
    Mem_Dump();

    printf("Free P4\n");
    Mem_Free(p4);
    Mem_Dump();
   
    printf("Free P5\n");
    Mem_Free(p5);
    Mem_Dump();
    Free_Memory_Allocator();
    return 0;
}
