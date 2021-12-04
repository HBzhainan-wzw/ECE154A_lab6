/*
Noah Lutz
Teagan Connon
ECE 154A - Fall 2012
Lab 2 - Mystery Caches
Due: 12/3/12, 11:00 pm

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
  flush_cache();
  addr_t adr = 0;
  access_cache(adr);

  int block = block_size;

  while(access_cache(0)){
    adr = block_size;
    
    while(adr <= block){
      adr += block_size;
      access_cache(adr);
    }
    block += block_size;
  }

  return adr;
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  flush_cache();
  addr_t adr = 0;
  access_cache(adr);
  int n = 0;
  int ways = 1;
  while(access_cache(0)){
    adr = size;
    n = 0;

    while(adr <= ways*size){
      adr += size;
      n += 1;
      access_cache(adr);
    }
    
    ways += 1;
    
  }
  return n;
}

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size() {
  /* YOUR CODE GOES HERE */
  flush_cache();
  addr_t adr = 0;
  access_cache(adr);
  
  while(access_cache(adr) == 1){
    adr += 1;
  }
  return adr;
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
