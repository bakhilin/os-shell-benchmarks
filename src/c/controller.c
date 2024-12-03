#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/sort.h"
#include "../include/utils.h"

int main(int argc, char  *argv[])
{
    if (argc != 3)
    {
        perror("Invalid argc");
        exit(EXIT_FAILURE);
    }
    
    int reps = atoi(argv[1]);
    char * filename = argv[2];
    params p;
    p.reps = reps;
    p.filename = filename;
    pthread_t threads[2];

    pthread_create(&threads[0], NULL, start_bench, argv[1]);
    pthread_create(&threads[1], NULL, load_data_from_file, (void *)&p);

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
