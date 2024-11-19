#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define ARRAY_SIZE 1000000
#define STRING_LENGTH 20

char *data[ARRAY_SIZE];

void* search_load(void* arg) {
    int repetitions = *((int*)arg);
    char target[STRING_LENGTH] = "target";

    for (int r = 0; r < repetitions; r++) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if (strcmp(data[i], target) == 0) {
                break;
            }
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_repetitions>n", argv[0]);
        return 1;
    }

    int repetitions = atoi(argv[1]);

    // Инициализация данных
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = malloc(STRING_LENGTH);
        snprintf(data[i], STRING_LENGTH, "string%d", i);
    }

    pthread_t threads[6]; // Creates 6 threads for load all yaders of processor

    for (int i = 0; i < 6; i++) {
        pthread_create(&threads[i], NULL, search_load, &repetitions);
    }

    for (int i = 0; i < 6; i++) {
        pthread_join(threads[i], NULL);
    }

    // Освобождение памяти
    for (int i = 0; i < ARRAY_SIZE; i++) {
        free(data[i]);
    }

    return 0;
}
