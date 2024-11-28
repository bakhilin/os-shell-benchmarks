#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "../include/utils.h"

#define MAX_ARG_LEN 100
#define MAX_CMD_LEN 1024
#define STRING_LENGTH 20
#define BLOCK_SIZE 4096
#define ARRAY_SIZE 1000000

char *data[ARRAY_SIZE];


void start(){
    char cmd[MAX_CMD_LEN];
    while (1)
    {
        printf("bakhilin@shell:");
        
        if(fgets(cmd, sizeof(cmd), stdin)==NULL) {
            break;
        } else {
            if (strcmp(cmd, "exit\n") == 0) {
                break;
            }
            exec_cmd(cmd);
        }
    }
}

void exec_cmd(char * cmd) {
    char * args[MAX_ARG_LEN];
    __pid_t pid;
    int status;
    __clock_t start, end;

    args[0] = strtok(cmd, " \n");
    int i = 1;
    while ((args[i] = strtok(NULL, " \n")) != NULL) {
        i++;
    }

    // create new process 
    pid = fork();   
    if (pid == -1)
    {
        perror("fork failed");
        return;
    } 

    if (pid == 0)
    {
        execvp(args[0], args);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else {
        start = clock(); // Запоминаем время начала
        waitpid(pid, &status, 0); // Ждем завершения дочернего процесса
        end = clock(); // Запоминаем время завершения

        // Вычисляем и выводим время выполнения
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time taken: %.2f seconds\n", time_taken);
    }

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

void fill_file(const char * filename) {
    FILE * file = fopen(filename, "w");
    if (file) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            fprintf(file, "string_%d\n", i);
        }
        fclose(file);
    }

}

void load_data_from_file(const char * filename) {
    FILE * file = fopen(filename, "r");
    int index = 0;
    char buffer[BLOCK_SIZE];

    while (fgets(buffer, BLOCK_SIZE, file) != NULL && index < ARRAY_SIZE) {
        char * line = strtok(buffer, "\n");
        while (line != NULL && index < ARRAY_SIZE)
        {
            data[index] = (char*)malloc(STRING_LENGTH * sizeof(char));
            if (data[index] == NULL) {
                perror("Ошибка выделения памяти");
                fclose(file);
                exit(EXIT_FAILURE);
            }
            strncpy(data[index], line, STRING_LENGTH - 1);
            data[index][STRING_LENGTH - 1] = '0';  
            index++;
            line = strtok(NULL, "\n");
        }
    }
    fclose(file);
}