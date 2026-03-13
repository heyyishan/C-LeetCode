#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

int maxCandies(int *status, int statusSize, int *candies, int candiesSize,
               int **keys, int *keysColSize, int **containedBoxes,
               int *containedBoxesColSize, int *initialBoxes,
               int initialBoxesSize) {
  int n = statusSize;
  int total_candies = 0;

  bool *has_box = calloc(n, sizeof(bool));
  bool *used_box = calloc(n, sizeof(bool));
  int *queue = malloc(n * sizeof(int));
  int head = 0, tail = 0;

  if (!has_box || !used_box || !queue)
    goto cleanup;

  for (int i = 0; i < initialBoxesSize; i++) {
    int b = initialBoxes[i];
    has_box[b] = true;
    if (status[b]) {
      used_box[b] = true;
      queue[tail++] = b;
    }
  }

  while (head < tail) {
    int curr = queue[head++];
    total_candies += candies[curr];

    for (int i = 0; i < keysColSize[curr]; i++) {
      int k = keys[curr][i];
      if (!status[k] && has_box[k] && !used_box[k]) {
        used_box[k] = true;
        queue[tail++] = k;
      }
      status[k] = 1; /* Key permanently unlocks the box */
    }

    for (int i = 0; i < containedBoxesColSize[curr]; i++) {
      int b = containedBoxes[curr][i];
      has_box[b] = true;
      if (status[b] && !used_box[b]) {
        used_box[b] = true;
        queue[tail++] = b;
      }
    }
  }

cleanup:
  free(has_box);
  free(used_box);
  free(queue);
  return total_candies;
}
int main(int argc, char *argv[]) { return EXIT_SUCCESS; }
