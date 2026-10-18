#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement first fit
  //
  if (free_list_ptr->size >= size) {
    return free_list_ptr->id;
  }
  if (free_list_ptr->next != NULL) {
    int c = find_first_fit(free_list_ptr->next, size);
    return c;
  }

  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = 1;
  int best_fit_size = free_list_ptr->size;
  while (free_list_ptr != NULL) {
    if (free_list_ptr->size - size < best_fit_size && free_list_ptr->size >= size) {
      best_fit_size = free_list_ptr->size;
      best_fit_id = free_list_ptr->id;
    }
    free_list_ptr = free_list_ptr->next;
  }

  // TODO: Implement best fit
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  int worst_fit_size = free_list_ptr->size;
  while (free_list_ptr != NULL) {
    if (free_list_ptr->size - size > worst_fit_size && free_list_ptr->size >= size) {
      worst_fit_size = free_list_ptr->size;
      worst_fit_id = free_list_ptr->id;
    }
    free_list_ptr = free_list_ptr->next;
  }
  // TODO: Implement worst fit
  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  printf("first fit: %d\n", first_fit_id);
  printf("best fit: %d\n", best_fit_id);
  printf("wortst fit: %d\n", worst_fit_id);
  // TODO: Print out the IDs

  return 0;
}

// *** I was unsure if you wanted an algorithm that takes a fragmented heap and coalesces it after
// a free, or one that coallesces as you free. This algorithm assumes you coallesce a fragmented
// heap that hasnt been coallesced after every free. So the assumption being made is that the list
// pre-coalesce may have multiple instances of free called prior to runnint the algorithm
// and thus may have multiple chunks of memory that need to be coallesced.
//
// the other option would be to coallece after each free, in which case you only need to worry about
// the newly freed chunk, and its immediate neighbors in memory thus needing a different algorithm
// ***
//
// coalesce(head):
// sorted = []:
// cur = head;
//  while ( cur != NULL){
//   insertion_sort(cur, sorted)
//   cur = cur -> next;
// new_head = sorted[0];
// while (i < sorted.len):
//  ** if the next block of free memory neighbors the current one, coallesce them***
//  if (sorted[i]+ sorted[i].size) == sorted[i + 1]
//    sorted[i].size += sorted[i + 1].size
//    pop(sorted[i+1]
//  else:
//    ** if not, the next block of memory becomes the next of the current block and we continue,
//    if its the last element in our sorted list, we set its next value to NULL**
//    if(i == sorted.len)
//      sorted[i].next = NULL;
//      break;
//    sorted[i].next = sorted[i+1]
//    i++
//
//  head = new_head
//  return
//
//
//
//
//
//
//
//
//
//
