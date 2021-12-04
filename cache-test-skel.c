/*
Zhiwen Wu
Haoran Wang
ECE 154A - Fall 2012
Lab 2 - Mystery Caches

Mystery Cache Geometries:
mystery0:
    block size = 64B
    cache size = 4000kB
    associativity = 16
mystery1:
    block size = 4B
    cache size = 4kB
    associativity = 1 
mystery2:
    block size = 32B
    cache size = 4kB
    associativity = 128
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/* 
   Returns the size (in B) of the cache
*/
int get_cache_size(int block_size) {
  /* YOUR CODE GOES HERE */
  flush_cache(); //reinitialize cache 
  // cache size = block number * block size
  addr_t res = 0;
  access_cache(0);
  int i = 0;
  while(access_cache(0)){
    res = block_size * i; 
    access_cache(res);
    i++;
  }

  return res;
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  flush_cache(); //reinitialize cache
  int address = 0; 
  int res = 0;  //associativity
  int way = 1; // number of ways
  while(access_cache(0)){
    address = size;
    res = 0;
    int temp = way * size; // get max size for current number of ways
    while(address <= temp){
      address += size;
      res++; 
      access_cache(address);//add to the current max size, check if valid. 
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
  flush_cache(); //reinitialize cache
  int address = 0;
  access_cache(address);
  // since block size has no pattern, try each number from 0
  while(access_cache(address)){
    address++;
  }
  return address;
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
