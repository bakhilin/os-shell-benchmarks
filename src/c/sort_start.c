#include <stdio.h>
#include <stdlib.h>
#include "../include/sort.h"
#include "../include/utils.h"

int main(int argc, char *argv[]) {
    if (argc != 2)
    {
        perror("Wrong input!");
        exit(EXIT_FAILURE);
    }

    start_bench((void*)argv[1]);
    return 0;
}
