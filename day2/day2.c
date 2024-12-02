#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

bool check(int *line, int size) {
  bool increasing = true;
  bool decreasing = true;

  for (int i = 0; i < size - 1; i++) {
    if (line[i] >= line[i + 1]) {
      increasing = false;
    }
    if (line[i] <= line[i + 1]) {
      decreasing = false;
    }
  }

  if (!(increasing || decreasing)) {
    return false;
  }

  qsort(line, size, sizeof(int), compare);

  for (int i = 0; i < size - 1; i++) {
    int diff = line[i + 1] - line[i];
    if (diff > 3 || diff < 1) {
      return false;
    }
  }

  return true;
}

int main() {
  FILE *file = fopen("input.txt", "r");
  if (file == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  int score = 0;
  char line[1000];

  while (fgets(line, sizeof(line), file)) {
    int nums[8];
    int count = 0;

    char *token = strtok(line, " \n");
    while (token != NULL && count < 8) {
      nums[count++] = atoi(token);
      token = strtok(NULL, " \n");
    }

    if (check(nums, count)) {
      score++;
      continue;
    }

    bool found = false;
    for (int i = 0; i < count; i++) {
      int temp[8];
      int temp_count = 0;

      for (int j = 0; j < count; j++) {
        if (j != i) {
          temp[temp_count++] = nums[j];
        }
      }

      if (check(temp, temp_count)) {
        score++;
        break;
      }
    }
  }

  printf("%d\n", score);
  fclose(file);
  return 0;
}
