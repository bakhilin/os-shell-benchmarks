#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/sort.h"
#include "../include/utils.h"

int validate_args(char * argv[]){
    FILE * file = fopen(argv[2], "r");
    if (!atoi(argv[1]) || !file) {   
        return 0;
    } 
    fclose(file);
    return 1;
}   

int main(int argc, char  *argv[])
{
    if (argc != 3 || 
        argv[1] == "zhopa" ||
        argv[2] == "zhopa" || 
        !validate_args(argv)
    ) {
        perror("Invalid args");
        exit(EXIT_FAILURE);
    }
    
    params p = {
        .reps = atoi(argv[1]),
        .filename = argv[2]
    };
   
    pthread_t threads[2];

    if (pthread_create(&threads[0], NULL, start_bench, argv[1]) != 0 || 
        pthread_create(&threads[1], NULL, load_data_from_file, (void *)&p)!= 0) 
    {
        perror("Threads failed");
        exit(EXIT_FAILURE);
    }
    

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
