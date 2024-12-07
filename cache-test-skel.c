/*
Frank Xiao
ECE 154A - Fall 2012
Lab 2 - Mystery Caches
Due: 12/3/12, 11:00 pm

Mystery Cache Geometries:
mystery0:
    block size = 64 bytes
    cache size = 256 bytes
    associativity = 4
mystery1:
    block size = 4 bytes
    cache size = 16 bytes
    associativity = 2
mystery2:
    block size = 32
    cache size = 128 bytes
    associativity = 4
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

int get_cache_size(int block_size);
int get_cache_assoc(int size);
int get_block_size();

/* 
   Returns the size (in B) of the cache
*/
int get_cache_size(int block_size) {
  addr_t addr = 0;
  int num_blocks = 0;

  while (TRUE) {
    if (access_cache(addr)) {
      num_blocks+=2;
      addr += block_size;
    } else {
      break;
    }
  }

  return num_blocks * block_size;  // Cache size = number of blocks * block size
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
    addr_t addr = 0;
    int block_size = get_block_size(); // Get the block size
    int num_blocks = size / block_size; // Total number of blocks in the cache
    int assoc = 1; // Start with 1-way associativity (direct-mapped)
    int num_sets;

    flush_cache(); // Flush the cache before testing

    // Test associativity from 1-way upwards
    while (assoc <= num_blocks) {
        num_sets = num_blocks / assoc;  // Calculate number of sets for this associativity level

        // Test by accessing multiple addresses that map to the same set
        int hit_count = 0;
        for (int i = 0; i < num_sets; i++) {
            for (int j = 0; j < assoc; j++) {
                addr_t probe_addr = addr + (i * assoc + j) * block_size;  // Access different addresses in the same set
                if (access_cache(probe_addr)) {
                    hit_count++;
                } else {
                    break;
                }
            }

            if (hit_count != (i + 1) * assoc) {
                break;
            }
        }

        // Double the associativity for the next test
        assoc *= 2;
    }
    return assoc;
}

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size() {
  addr_t addr = 0;
  int block_size = 0;
  flush_cache();
  access_cache(addr);

  while (access_cache(addr + block_size)) {
    block_size++;
  }
  return block_size;
}

int main(void) {
  int size;
  int assoc;
  int block_size;
  
  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.
     You can test your geometry paramter discovery routines by 
     calling cache_init() w/ your own size and block size values. */
  cache_init(0,0);
  
  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);


  printf("Cache size: %d bytes\n",size);
  printf("Cache associativity: %d\n",assoc);
  printf("Cache block size: %d bytes\n",block_size);
  
  return EXIT_SUCCESS;
}
