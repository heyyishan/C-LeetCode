#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* Use a simple struct for the hash map entries */
struct hash_entry {
  int key;
  int val;
  bool occupied;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  /* Larger table size reduces collisions; Linux style uses power-of-two or 2x
   * size */
  uint32_t table_size = (uint32_t)numsSize * 2;
  struct hash_entry *map = calloc(table_size, sizeof(struct hash_entry));

  if (map == nullptr) {
    *returnSize = 0;
    return nullptr;
  }

  for (int i = 0; i < numsSize; i++) {
    int complement = target - nums[i];

    /* Multiplicative hash for distribution */
    uint32_t h = ((uint32_t)complement * 2654435761U) % table_size;

    /* Linear probing to find the complement */
    while (map[h].occupied) {
      if (map[h].key == complement) {
        int *res = malloc(2 * sizeof(int));
        if (!res)
          goto fail;

        res[0] = map[h].val;
        res[1] = i;
        *returnSize = 2;
        free(map);
        return res;
      }
      h = (h + 1) % table_size;
    }

    /* Insert current number into the map */
    uint32_t ins_h = ((uint32_t)nums[i] * 2654435761U) % table_size;
    while (map[ins_h].occupied) {
      ins_h = (ins_h + 1) % table_size;
    }

    map[ins_h] =
        (struct hash_entry){.key = nums[i], .val = i, .occupied = true};
  }

fail:
  free(map);
  *returnSize = 0;
  return nullptr;
}
