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
#define EXIT_CODE "exit\n"
#define SHELL_PRINT printf("bakhilin@shell:")

void start(){
    char cmd[MAX_CMD_LEN];
    while (1)
    {
        SHELL_PRINT;
        if(fgets(cmd, sizeof(cmd), stdin)==NULL) {
            break;
        } else {
            if (strcmp(cmd, EXIT_CODE) == 0) {
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


