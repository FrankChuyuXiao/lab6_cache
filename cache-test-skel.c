/*
Frank Xiao
ECE 154A - Fall 2012
Lab 2 - Mystery Caches
Due: 12/3/12, 11:00 pm

Mystery Cache Geometries:
mystery0:
    block size = 64 bytes
    cache size = 256 bytes
    associativity = 
mystery1:
    block size = 4 bytes
    cache size = 16 bytes
    associativity = 
mystery2:
    block size = 32
    cache size = 128 bytes
    associativity = 
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
  int block_size = get_block_size();  // Get the block size (already known)
  int num_sets = size / block_size;  // Number of sets in the cache
  
  // Test associativity starting from 1-way to num_sets-way
  for (int assoc = 1; assoc <= num_sets; assoc++) {
    flush_cache();  // Clear the cache before each associativity test
    
    int i;
    // Access a series of blocks and check cache hits
    for (i = 0; i < num_sets * assoc; i++) {
      addr_t probe_addr = addr + (i * block_size);
      if (!access_cache(probe_addr)) {
        // If we get a miss, break out, as we've tested this level of associativity
        break;
      }
    }

    // If the number of accesses didn't exceed the associativity, we've found the correct associativity
    if (i == num_sets * assoc) {
      return assoc;  // Return the associativity when no miss occurred
    }
  }

  return 1;  // If no associativity found, return 1 (default to direct-mapped cache)
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
