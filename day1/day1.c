#include <stdio.h>
#include <stdlib.h>

int compare( const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    char *filename = "input.txt";
    int array1[1000];
    int array2[1000];

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error\n");
        return 1;
    }
    for (int i = 0; i < 1000; i++) {
        fscanf(fp, "%5d", &array1[i]);
        fscanf(fp, "%5d", &array2[i]);
    }
    fclose(fp);

    qsort(array1, 1000, sizeof(int), compare);
    qsort(array2, 1000, sizeof(int), compare);

    int sum = 0;
    for (int i = 0; i < 1000; i++) {
        sum += abs(array1[i] - array2[i]);
    }

    printf("[Part 1] Total sum: %d\n", sum);

    int total_score = 0;
    for (int i = 0; i < 1000; i++) {
        int times_seen = 0;
        for (int j = 0; j < 1000; j++) {
            if (array1[i] == array2[j]) {
                times_seen++;
            }
        }
        total_score += array1[i] * times_seen;
    }

    printf("[Part 2] Similarity score: %d\n", total_score);

    return 0;
}
