#ifndef SORT_H
#define SORT_H

void merge(int arr[], int left, int mid, int right);
void merge_sort(int arr[], int left, int right);
void print_arr(int arr[]);
void* sort_load(void* arg);
void start_bench(int reps);

#endif 
