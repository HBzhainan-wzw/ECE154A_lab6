/*
YOUR NAME HERE
ECE 154A - Fall 2012
Lab 2 - Mystery Caches
Due: 12/3/12, 11:00 pm

Mystery Cache Geometries:
mystery0:
    block size = 
    cache size = 
    associativity = 
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

#define MAX_CACHE_SIZE_BITS 24
#define MAX_CACHE_BLOCK_SIZE 1024
#define MAX_CACHE_ASSOC_BITS 24

/* 
   Returns the size (in B) of the cache
*/
int get_cache_size(int block_size) {
  /* YOUR CODE GOES HERE */
  int retsize = -1;
  int i, j;
  for (i = 0; i < MAX_CACHE_SIZE_BITS; ++i) {
    int cache_size = (1 << i);
    flush_cache();
    for (j = 0; j <= cache_size / size; ++j) {
      access_cache(j*size);
    }
    
    if (!access_cache(0)) {
      retsize = cache_size;
      break;
    }
  }
  return retsize;
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  int i, j;
  int retsize = -1;

  for (i = 0; i < MAX_CACHE_ASSOC_BITS; ++i) {
    int assoc_size = (1 << i);
    flush_cache();
    for (j = 0; j <= assoc_size; ++j) {
      access_cache(j * size);
    }
    if (!access_cache(0)) {
      retsize = assoc_size;
      break;
    }
  }
  return retsize;
}

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size() {
  /* YOUR CODE GOES HERE */
  int retsize = -1;
  int i;
  flush_cache();
  access_cache(0);

  for (i = 1; i < MAX_CACHE_BLOCK_SIZE; ++i) {
    if (!access_cache(i)) {
      retsize = i;
      break;
    }
  }
  return retsize;
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
