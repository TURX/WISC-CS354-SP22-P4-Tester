// CS354 SP22 Project 4 Sample Tester
// Originally by UW-Madison CS354
// Modified by Ruixuan Tu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem.h"

// pointer to the first block of the heap
BLOCK_HEADER *first_header;  // use this variable for your heap

// **********************************************
// *****   INITIALIZE MEMORY FOR OUR HEAP   *****
// **********************************************
void *__start_of_heap; // don't change this, we need it to free our heap when finished

// this function calls malloc to reserve space for us to manage with our memory allocator
// this will be the only call to malloc in the entire project
void Initialize_Memory_Allocator(int size) {
    // round up the requested size to meet alignment requirements
    while (size%16) size++; // round up to a size divisible by 16

    // malloc space for our heap and first and last headers
    // plus a little extra for alignment
    __start_of_heap = malloc(size + 48); // don't change this we need this variable to free

    // generate the first header
    unsigned long start = (unsigned long)__start_of_heap; // cast so we can do arithmetic
    while (start%16) start++; // first payload must be an address divisible by 16
    start += 8; // header aligned 8 bytes before payload
    first_header = (BLOCK_HEADER *)start; // cast to block header pointer
    first_header->size_alloc = size; // set the block size and free
    first_header->payload = size-8; // set the payload size (available free size)

    // locate last header
    BLOCK_HEADER *last_header = (BLOCK_HEADER *)((unsigned long)first_header + size);
    last_header->size_alloc = 1;  // block size 0, allocated
    last_header->payload = 0;    
}

void Free_Memory_Allocator() {
    free(__start_of_heap);
}


void Mem_Dump() {
    // global stats   
    int total_free_size = 0;
    int total_allocated_size = 0;
    int total_metadata_size = 0;
    int total_padding_size = 0;

    // per block data
    int id = 0;
    int alloc;
    char status[6];
    BLOCK_HEADER *header;
    void *user_pointer;
    int block_size;
    int payload;
    int padding;

    printf("************************************** Block List *****************************************\n");
    printf("  %5s %6s %15s %15s %10s %10s %7s %7s %6s\n",
            "Id", "Status", "Header", "Pointer", "Size_Alloc", "Block Size", "Payload", "Padding", "Header");
    // process the blocks
    BLOCK_HEADER *current = first_header;
    while (1) {    
        // per block data
        id++;
        alloc = current->size_alloc & 1;
        if (alloc) strcpy(status, "alloc"); else strcpy(status," free");
        header = current;
        user_pointer = (void *)((unsigned long)current+8);
        block_size = current->size_alloc & 0xFFFFFFFE;
        payload = current->payload;
        padding = block_size - 8 - payload;
       
        // last block
        if (current->size_alloc == 1) strcpy(status, " last");
        if (current->size_alloc == 1) padding = 0;
        if (current->size_alloc == 1) block_size = 8;

        // total stats
        if (alloc == 0) total_free_size += payload;
        if (alloc == 1) total_allocated_size += payload;
        total_metadata_size += 8;
        if (alloc == 1) total_padding_size += padding;

        printf("> %5d %6s %15p %15p %10d %10d %7d %7d %6d\n",
                id, status, header, user_pointer, current->size_alloc, block_size, payload, padding, 8);
        if (current->size_alloc == 1) break;
        current = (BLOCK_HEADER *)((unsigned long)current + block_size);
    }
    printf("*******************************************************************************************\n");
    int total_size = total_free_size + total_allocated_size + total_metadata_size + total_padding_size;
    printf("    Total Free Size %d\n",total_free_size);
    printf("    Total Allocated Size %d\n",total_allocated_size);
    printf("    Total Header Size %d\n",total_metadata_size);
    printf("    Total Padding Size %d\n",total_padding_size);
    printf("    Total_Size %d\n\n\n",total_size);
            
}
