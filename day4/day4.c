#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 140

int check_diagonals(int x, int y, char grid[GRID_SIZE][GRID_SIZE]) {
  int count = 0;

  // Check left up
  if (x - 3 >= 0 && y - 3 >= 0) {
    if (grid[y - 1][x - 1] == 'M' && grid[y - 2][x - 2] == 'A' &&
        grid[y - 3][x - 3] == 'S') {
      count++;
    }
  }

  // Check left down
  if (x - 3 >= 0 && y + 3 < GRID_SIZE) {
    if (grid[y + 1][x - 1] == 'M' && grid[y + 2][x - 2] == 'A' &&
        grid[y + 3][x - 3] == 'S') {
      count++;
    }
  }

  // Check right up
  if (x + 3 < GRID_SIZE && y - 3 >= 0) {
    if (grid[y - 1][x + 1] == 'M' && grid[y - 2][x + 2] == 'A' &&
        grid[y - 3][x + 3] == 'S') {
      count++;
    }
  }

  // Check right down
  if (x + 3 < GRID_SIZE && y + 3 < GRID_SIZE) {
    if (grid[y + 1][x + 1] == 'M' && grid[y + 2][x + 2] == 'A' &&
        grid[y + 3][x + 3] == 'S') {
      count++;
    }
  }

  return count;
}

int check_regular(int x, int y, char grid[GRID_SIZE][GRID_SIZE]) {
  int count = 0;

  // Check left
  if (x - 3 >= 0) {
    if (grid[y][x - 1] == 'M' && grid[y][x - 2] == 'A' &&
        grid[y][x - 3] == 'S') {
      count++;
    }
  }

  // Check right
  if (x + 3 < GRID_SIZE) {
    if (grid[y][x + 1] == 'M' && grid[y][x + 2] == 'A' &&
        grid[y][x + 3] == 'S') {
      count++;
    }
  }

  // Check up
  if (y - 3 >= 0) {
    if (grid[y - 1][x] == 'M' && grid[y - 2][x] == 'A' &&
        grid[y - 3][x] == 'S') {
      count++;
    }
  }

  // Check down
  if (y + 3 < GRID_SIZE) {
    if (grid[y + 1][x] == 'M' && grid[y + 2][x] == 'A' &&
        grid[y + 3][x] == 'S') {
      count++;
    }
  }

  return count;
}

int check_valid_x(int x, int y, char grid[GRID_SIZE][GRID_SIZE]) {
  int count = 0;

  if (y - 1 >= 0 && x - 1 >= 0 && y + 1 < GRID_SIZE && x + 1 < GRID_SIZE) {
    // Check:
    // M . M
    // . A .
    // S . S
    if (grid[y - 1][x - 1] == 'M' && grid[y - 1][x + 1] == 'M' &&
        grid[y + 1][x - 1] == 'S' && grid[y + 1][x + 1] == 'S') {
      count++;
    }

    // Check:
    // S . S
    // . A .
    // M . M
    if (grid[y - 1][x - 1] == 'S' && grid[y - 1][x + 1] == 'S' &&
        grid[y + 1][x - 1] == 'M' && grid[y + 1][x + 1] == 'M') {
      count++;
    }

    // Check:
    // M . S
    // . A .
    // M . S
    if (grid[y - 1][x - 1] == 'M' && grid[y - 1][x + 1] == 'S' &&
        grid[y + 1][x - 1] == 'M' && grid[y + 1][x + 1] == 'S') {
      count++;
    }

    // Check:
    // S . M
    // . A .
    // S . M
    if (grid[y - 1][x - 1] == 'S' && grid[y - 1][x + 1] == 'M' &&
        grid[y + 1][x - 1] == 'S' && grid[y + 1][x + 1] == 'M') {
      count++;
    }
  }

  return count;
}

int main() {
  FILE *file = fopen("input.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  char grid[GRID_SIZE][GRID_SIZE];
  int y = 0;
  // I don't know why this can not be just GRID_SIZE, but it can't
  char line[1000];
  while (fgets(line, sizeof(line), file) && y < GRID_SIZE) {
    line[strcspn(line, "\n")] = 0;
    for (int x = 0; x < GRID_SIZE && line[x] != '\0'; x++) {
      grid[y][x] = line[x];
    }
    y++;
  }
  fclose(file);

  int xmas_sum = 0;
  int x_mas_sum = 0;
  for (y = 0; y < GRID_SIZE; y++) {
    for (int x = 0; x < GRID_SIZE; x++) {
      if (grid[y][x] == 'X') {
        xmas_sum += check_regular(x, y, grid) + check_diagonals(x, y, grid);
      }
      if (grid[y][x] == 'A') {
        x_mas_sum += check_valid_x(x, y, grid);
      }
    }
  }

  printf("XMAS count: %d\n", xmas_sum);
  printf("X-MAS count: %d\n", x_mas_sum);

  return 0;
}
