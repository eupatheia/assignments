/* mylloc_list.c
 * re-implementation of malloc() and free() using a struct chunk
 * to store metadata; also has a function to print fragmentation stats
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

// represents a "chunk" of metadata in the space
// before an allocated block of memory
struct chunk {
  int size;
  int used;
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  // no allocation
  if (size == 0) {
    return NULL;
  }
  struct chunk * next = flist;
  struct chunk * prev = NULL;

  // look in free list first
  while (next != NULL) {
    if (next->size >= size) {
      if (prev != NULL) {
	// relink list by skipping over this block (next)
        prev->next = next->next;
      } else {
	// new head of list is the block after this one
        flist = next->next;
      }
      // update used variable
      next->used = size;
      // skip over metadata chunk and return pointer to usable memory
      return (void *)(next + 1);
    } else {
      prev = next;
      next = next->next;
    }
  }

  // no suitable blocks in free list, so new allocation;
  // make sure to allocate space for metadata chunk
  void *memory = sbrk(size + sizeof(struct chunk));
  if (memory == (void *) -1) {
    // unsuccessful allocation
    return NULL;
  } else {
    // treat memory as chunk so we can skip ahead by a chunk size
    // and return a pointer to the allocated memory after the metadata
    struct chunk* cnk = (struct chunk*) memory;
    cnk->size = size;
    cnk->used = size;
    return (void*) (cnk + 1);
  }
}

void free(void *memory) {
  if (memory != NULL) {
    // jump back one chunk position, i.e. go to beginning of chunk metadata
    struct chunk * cnk = (struct chunk *) ((struct chunk *) memory - 1);
    // add to front of free list
    cnk->next = flist;
    flist = cnk;
  }
  return;
}

void fragstats(void* buffers[], int len) {
  int free_blocks, used_blocks;
  int in_total, in_min, in_max, ex_total, ex_min, ex_max;
  double in_avg, ex_avg;

  in_total = 0;
  ex_total = 0;
  in_min = INT_MAX;
  ex_min = INT_MAX;
  in_max = -1;
  ex_max = -1;
  in_avg = 0;
  ex_avg = 0;

  // count free blocks
  struct chunk * temp = flist;
  free_blocks = 0; 
  while (temp != NULL) {
    free_blocks += 1;
    // get external fragmentation stats
    if (temp->size < ex_min) {
      ex_min = temp->size;
    }
    if (temp->size > ex_max) {
      ex_max = temp->size;
    }
    ex_total += temp->size;
    ex_avg += temp->size;
    
    temp = temp->next;
  }

  // count used blocks
  used_blocks = 0;
  for (int i = 0; i < len; i++) {
    temp = (struct chunk *) buffers[i];
    if (temp != NULL) {
      used_blocks += 1;
      // jump back to chunk metadata
      temp = temp - 1;
      // get internal fragmentation stats
      int unused = temp->size - temp->used;
      if (unused < in_min) {
        in_min = unused;
      }
      if (unused > in_max) {
        in_max = unused;
      }
      in_total += unused;
      in_avg += unused;
    }
  }

  in_avg = in_avg / used_blocks;
  ex_avg = ex_avg / free_blocks;

  printf("Total blocks: %d, Free: %d, Used: %d\n", (free_blocks + used_blocks),
		  free_blocks, used_blocks);
  printf("Internal unused: total: %d, average: %.2f, smallest: %d, largest: %d\n",
		  in_total, in_avg, in_min, in_max);
  printf("External unused: total: %d, average: %.2f, smallest: %d, largest: %d\n",
		  ex_total, ex_avg, ex_min, ex_max);
}

