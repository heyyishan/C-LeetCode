#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

[[nodiscard]]
static inline uint32_t hash_fn(int32_t key, uint32_t size) {
  return ((uint32_t)key * 2654435761U) % size;
}

struct hash_entry {
  int32_t key;
  int32_t val;
  bool occupied;
};
int32_t *two_sum(const int32_t *nums, size_t nums_size, int32_t target,
                 int *return_size) {
  const size_t table_size = nums_size * 2;
  struct hash_entry *map = calloc(table_size, sizeof(struct hash_entry));

  if (map == nullptr)
    return nullptr;

  for (size_t i = 0; i < nums_size; i++) {
    int32_t complement = target - nums[i];
    uint32_t h = hash_fn(complement, (uint32_t)table_size);

    while (map[h].occupied) {
      if (map[h].key == complement) {
        int32_t *res = malloc(sizeof(int32_t) * 2);
        if (!res)
          goto cleanup;

        res[0] = map[h].val;
        res[1] = (int32_t)i;
        *return_size = 2;
        free(map);
        return res;
      }
      h = (h + 1) % table_size;
    }

    h = hash_fn(nums[i], (uint32_t)table_size);
    while (map[h].occupied)
      h = (h + 1) % table_size;

    map[h] = (struct hash_entry){
        .key = nums[i], .val = (int32_t)i, .occupied = true};
  }

cleanup:
  free(map);
  *return_size = 0;
  return nullptr;
}

int main(void) {
  const int32_t nums[] = {2, 7, 11, 15};
  int32_t target = 9;
  int count = 0;

  int32_t *result =
      two_sum(nums, sizeof(nums) / sizeof(nums[0]), target, &count);

  if (result != nullptr) {
    printf("Indices: [%d, %d]\n", result[0], result[1]);
    free(result);
  } else {
    printf("No solution found.\n");
  }

  return 0;
}
