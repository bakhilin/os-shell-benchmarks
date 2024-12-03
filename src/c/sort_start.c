#include <stdio.h>
#include <stdlib.h>
#include "../include/sort.h"
#include "../include/utils.h"

int main(int argc, char const *argv[]) {
    if (argc != 2)
    {
        perror("Wrong input!");
        exit(EXIT_FAILURE);
    }
    // params p = {
    //     .filename = "",
    //     .reps = atoi(argv[1])
    // };

    
    start_bench((void*)argv[1]);
    return 0;
}
