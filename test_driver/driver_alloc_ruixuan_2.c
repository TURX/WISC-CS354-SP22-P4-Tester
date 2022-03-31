// CS354 SP22 Project 4 Sample Tester
// Authored by Ruixuan Tu

#include "mem.h"
#include <stdio.h>

int main() {
    Initialize_Memory_Allocator(1600);
    Mem_Dump();

    char *p[1024];
    for (int i = 1; i < 1024; i++) {
        if ((p[i] = Mem_Alloc(i)) == NULL) {
            printf("Allocation failed\n");
            exit(0);
        }
        Mem_Dump();
    }
    Mem_Dump();


    for (int i = 1023; i >= 1; i--) {
        if (Mem_Free(p[i]) == -1) {
            printf("Free failed\n");
            exit(0);
        }
        Mem_Dump();
    }
    Mem_Dump();

    Free_Memory_Allocator();
    return 0;
}
