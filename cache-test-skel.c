/*
Frank Xiao
ECE 154A - Fall 2012
Lab 2 - Mystery Caches
Due: 12/3/12, 11:00 pm

Mystery Cache Geometries:
mystery0:
    block size = 16 bytes
    cache size = 65336 bytes
    associativity = 2
mystery1:
    block size = 
    cache size = 
    associativity = 
mystery2:
    block size = 
    cache size = 
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
  /*
  int num_blocks = 0;
  addr_t addr = 0;
  bool_t is_filled = FALSE;

  flush_cache();
  while (TRUE) {
    for(int i = 0; i < block_size; i++){
      if(access_cache(addr + i)){
        is_filled = TRUE;
        break;
      }
    }
    if(!is_filled){
      break;
    }
    num_blocks++;
    addr += block_size;
  }
  return num_blocks * block_size;
  */
  return 0;
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
  int assoc;
  

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
