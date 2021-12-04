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

/* 
   Returns the size (in B) of the cache
*/
int get_cache_size(int block_size) { // cache size = block number * block size
  /* YOUR CODE GOES HERE */
  int res = 0;
  int i = 0;
  flush_cache(); // reinitialize the cache
  while(access_cache(0)){
    int block = i * block_size;
    flush_cache(); // reinitialize the cache
    res = block_size;
    while(res <= block){ //try different number of blocks with fixed blocked size
      res += block_size;
      access_cache(res);
    }
    i++;
  }

  return res;
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  int res = 0; // associativity
  int address = 0;
  int way = 1; 
  flush_cache(); // reinitialize the cache
  while(access_cache(0)){
    address = size; 
    res = 0;
    while(address <= way * size){  
      address += size;
      res++;
      access_cache(address);
    }
    way++;
  }
  return res;
}

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size() {
  /* YOUR CODE GOES HERE */
  int res = 0;
  flush_cache(); // reinitialize the cache

  while(access_cache(res)){ // block size has no pattern, so try each size
    res++;
  }
  return res;
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
