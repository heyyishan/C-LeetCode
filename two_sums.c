#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int key;
  int val;
  bool occupied;
} HashEntry;

typedef struct {
  struct hash_entry *buckets;
  size_t size;
} HashTable;

static inline size_t Hash(int key, size_t size) {
  unsigned int ukey = (unsigned int)key;
  return (ukey * 2654435761U) % size;
}

int *two_sum(const int *nums, size_t nums_size, int target, int *return_size) {
  size_t table_size = nums_size * 2;
  map = {.buckets = calloc(table_size, sizeof(HashEntry)), .size = table_size};

  if (!map.buckets)
    return nullptr;

  for (size_t i = 0; i < nums_size; i++) {
    int complement = target - nums[i];
    size_t h = Hash(complement, map.size);

    while (map.buckets[h].occupied) {
      if (map.buckets[h].key == complement) {
        int *res = malloc(sizeof(int) * 2);
        res[0] = map.buckets[h].val;
        res[1] = (int)i;
        *return_size = 2;
        free(map.buckets);
        return res;
      }
      h = (h + 1) % map.size;
    }

    /* Insert current value */
    h = Hash(nums[i], map.size);
    while (map.buckets[h].occupied)
      h = (h + 1) % map.size;

    map.buckets[h] =
        (HashEntry){.key = nums[i], .val = (int)i, .occupied = true};
  }

  free(map.buckets);
  *return_size = 0;
  return NULL;
}

int main(int argc, char *argv[]) { return EXIT_SUCCESS; }
