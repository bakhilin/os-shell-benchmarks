#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/sort.h"
#include "../include/utils.h"

#define ARRAY_SIZE 10


void print_arr(int arr[]){
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        if (i % 9 == 0)
            printf("\n");
        printf("%d ", arr[i]);
    }

    printf("\n------- \n");
}

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1; // test
    int n2 = right - mid;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);

}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void sort_load(int reps) {

    for (int r = 0; r < reps; r++) {
        int* arr = (int*)malloc(ARRAY_SIZE * sizeof(int));
        
        // Инициализация массива случайными числами
        for (int i = 0; i < ARRAY_SIZE; i++) {
            arr[i] = rand() % 10000;
        }
        merge_sort(arr, 0, ARRAY_SIZE - 1);    
        free(arr);
    }
    
}

void *start_bench(void * arg) {
    int reps = atoi((const char*)arg);
    sort_load(reps);
}   


