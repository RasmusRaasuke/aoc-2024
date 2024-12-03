#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *file = fopen("input.txt", "r");
  if (file == NULL) {
    perror("Failed to open file");
    return 1;
  }

  regex_t regex;
  const char *pattern = "mul\\(([0-9]+),([0-9]+)\\)|(do\\(\\)|don't\\(\\))";
  int reti = regcomp(&regex, pattern, REG_EXTENDED);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    fclose(file);
    return 1;
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int total_matches = 0;
  int total_instructions = 0;
  int sum_of_all_multiplications = 0;
  bool enabled = true;

  while ((read = getline(&line, &len, file)) != -1) {
    char *ptr = line;
    regmatch_t matches[4];
    while (regexec(&regex, ptr, 4, matches, 0) == 0) {
      if (matches[2].rm_so != -1) {
        char num1[20] = {0};
        char num2[20] = {0};

        snprintf(num1, matches[1].rm_eo - matches[1].rm_so + 1, "%s",
                 ptr + matches[1].rm_so);
        snprintf(num2, matches[2].rm_eo - matches[2].rm_so + 1, "%s",
                 ptr + matches[2].rm_so);

        if (enabled) {
          // printf("Found match: mul(%s, %s)\n", num1, num2);
          total_matches++;
          int int_num1 = atoi(num1);
          int int_num2 = atoi(num2);
          sum_of_all_multiplications += int_num1 * int_num2;
        }

      } else if (matches[3].rm_so != -1) {
        total_instructions++;
        char instuction[20] = {0};
        snprintf(instuction, matches[3].rm_eo - matches[3].rm_so + 1, "%s",
                 ptr + matches[3].rm_so);

        if (strcmp(instuction, "don't()") == 0) {
          enabled = false;
        } else {
          enabled = true;
        }

        // printf("Current Instruction: %s\n", instuction);
      }

      ptr += matches[0].rm_eo;
    }
  }

  free(line);
  fclose(file);
  regfree(&regex);

  printf("Total matches: %d\n", total_matches);
  printf("Total instructions: %d\n", total_instructions);
  printf("Sum: %d\n", sum_of_all_multiplications);
  return 0;
}
