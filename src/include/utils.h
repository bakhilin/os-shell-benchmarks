#ifndef UTILS_H

void start();
void exec_cmd(char * cmd);

void fill_file(const char * filename);
void *load_data_from_file(void * arg);
void *search_load(void * arg);

typedef struct {
    int reps;
    char * filename;
} params;

#endif