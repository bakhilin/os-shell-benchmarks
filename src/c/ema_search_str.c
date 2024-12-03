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
    char *filename = argv[2];  
    
    //fill_file(filename); 

    params p;
    p.filename = filename;
    p.reps = repetitions;
    
    load_data_from_file((void *)&p); 

    return 0;
}

