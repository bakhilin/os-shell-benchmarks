#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define ARRAY_SIZE 1000000
#define STRING_LENGTH 20

char *data[ARRAY_SIZE];

void fill_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Ошибка открытия файла для записи");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        fprintf(file, "string_%d\n", i); 
    }

    fclose(file);
}

void load_data_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла для чтения");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = (char*)malloc(STRING_LENGTH * sizeof(char)); 
        if (data[i] == NULL) {
            perror("Ошибка выделения памяти");
            fclose(file);
            exit(EXIT_FAILURE);
        }

        if (fgets(data[i], STRING_LENGTH, file) == NULL) { 
            free(data[i]);
            data[i] = NULL; 
            break; 
        }
    }

    fclose(file);
}

void* search_load(void* arg) {
    int repetitions = *((int*)arg);
    char target[STRING_LENGTH] = "target"; 

    for (int r = 0; r < repetitions; r++) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if (data[i] != NULL && strcmp(data[i], target) == 0) {
                break;
            }
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_repetitions> <filename>\n", argv[0]);
        return 1;
    }

    int repetitions = atoi(argv[1]);
    const char *filename = argv[2];

    fill_file(filename); 
    load_data_from_file(filename); 

    pthread_t threads[6]; 

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
