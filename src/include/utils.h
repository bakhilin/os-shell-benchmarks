#ifndef UTILS_H

void start();
void exec_cmd(char * cmd);

void fill_file(const char * filename);
void load_data_from_file(const char * filename);
void *search_load(void * arg);

#endif