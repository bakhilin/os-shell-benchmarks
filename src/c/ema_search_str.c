#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "../include/utils.h"

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

    return 0;
}
