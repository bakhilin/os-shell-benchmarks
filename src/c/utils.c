#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../include/utils.h"
#include <pthread.h>
#include <sys/resource.h>
#include <sys/time.h>

#define MAX_PIPES 5
#define MAX_ARG_LEN 100
#define MAX_CMD_LEN 1024
#define STRING_LENGTH 20
#define BLOCK_SIZE 4096
#define ARRAY_SIZE 10000000

typedef struct {
    char * block;
    int block_size;
    int repetitions;
} ThreadData;



char *data[ARRAY_SIZE];

void start() {
    char cmd[MAX_CMD_LEN];
    for(;;){
        printf("bakhilin@shell: ");

        if (fgets(cmd, sizeof(cmd), stdin) == NULL) 
            break;
        
        if (strcmp(cmd, "exit\n") == 0) 
                break;
            
        struct timeval start_time, end_time;
        gettimeofday(&start_time, NULL);
        exec_cmd(cmd);
        gettimeofday(&end_time, NULL);

        const long seconds = end_time.tv_sec - start_time.tv_sec;
        const long microseconds = end_time.tv_usec - start_time.tv_usec;
        const long total_microseconds = seconds * 1000000 + microseconds;

        printf("Time of execution: %ld.%06ld seconds\n", total_microseconds / 1000000, total_microseconds % 1000000);
        
    }
}

void exec_cmd(char *cmd) {
    char * commands[MAX_PIPES];
    int count_cmd = 0;
    char *args[MAX_ARG_LEN];
    __pid_t pid;
    int status;

    commands[count_cmd] = strtok(cmd, "|");
    while (commands[count_cmd] != NULL && count_cmd < MAX_PIPES - 1) {
        count_cmd++;
        commands[count_cmd] = strtok(NULL, "|");
    }

    int pipe_fd[2 * (count_cmd - 1)];
    for (int i = 0; i < count_cmd - 1; i++) {
        if (pipe(pipe_fd + i * 2) == -1) {
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }
    }


    for (size_t i = 0; i < count_cmd; i++)
    {
        pid = fork();
        if (pid == -1) {
            perror("fork failed");
            return;
        }

        if (pid == 0) { 
            if (i > 0) {
                if (dup2(pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1) {
                    perror("dup2 failed");
                    exit(EXIT_FAILURE);
                }
            }

            if (i < count_cmd - 1) {
                if (dup2(pipe_fd[i * 2 + 1], STDOUT_FILENO) == -1) {
                    perror("dup2 failed");
                    exit(EXIT_FAILURE);
                }
            }

            for (int j = 0; j < 2 * (count_cmd - 1); j++) {
                close(pipe_fd[j]);
            }
            
            int arg_count = 0;
            args[arg_count] = strtok(commands[i], " \n");
            while (args[arg_count] != NULL && arg_count < MAX_ARG_LEN - 1) {
                arg_count++;
                args[arg_count] = strtok(NULL, " \n");
            }
            args[arg_count] = NULL; 

            execvp(args[0], args);
            perror("exec failed");
            exit(EXIT_FAILURE); 
        } 
    }
    
    for (int i = 0; i < 2 * (count_cmd - 1); i++) {
        close(pipe_fd[i]);
    }
    
    for (int i = 0; i < count_cmd; i++) {
        wait(NULL);
    }
}


void* search_load(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    char target[STRING_LENGTH] = "target"; 
    int found = 0; 

    for (int r = 0; r < data->repetitions; r++) {
        if (strstr(data->block, target) != NULL) {
            found = 1;
            break;
        }
    }

    free(data->block); 
    return (void*)(__intptr_t)found;
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

void* load_data_from_file(void * arg) {
    params * p = (params *)arg;
    FILE * file = fopen(p->filename, "r");
    char buffer[BLOCK_SIZE];
    pthread_t threads[6]; 
    int thread_count = 0;

    while (1)
    {
        size_t bytes_read = fread(buffer, sizeof(char), BLOCK_SIZE, file);
        if (bytes_read == 0)
        {
            break;
        }

        ThreadData * data = malloc(sizeof(ThreadData));
        data->block = malloc((bytes_read+1) * sizeof(char));

        memcpy(data->block, buffer, bytes_read);
        data->block[bytes_read] = '0'; 
        data->repetitions = p->reps;

        pthread_create(&threads[thread_count++], NULL, search_load, data);
        if (thread_count >= 6) {
            for (int i = 0; i < thread_count; i++) {
                void* result;
                pthread_join(threads[i], &result);
            }
            thread_count = 0; 
        }
    }

    for (int i = 0; i < thread_count; i++) {
        void* result;
        pthread_join(threads[i], &result);
    }

    fclose(file);
    
}