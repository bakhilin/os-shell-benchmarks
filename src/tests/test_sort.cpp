#include <gtest/gtest.h>
#include "../include/sort.h"

#define ARRAY_SIZE 100

bool is_sorted(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

TEST(merge_sort, merge_sort_test) {
    int arr[ARRAY_SIZE] = {5, 3, 8, 6, 2, 7, 4, 1};
    int size = 8;

    merge_sort(arr, 0, size - 1);
    
    EXPECT_TRUE(is_sorted(arr, size));
}

// Тест для многопоточной нагрузки
TEST(start_bench, start_bench_test) {
    EXPECT_NO_THROW(start_bench(10)); 
}

// Тест для пустого массива
TEST(merge_sort, empty_array_test) {
    int arr[0] = {};
    merge_sort(arr, 0, -1); 
    EXPECT_TRUE(is_sorted(arr, 0)); 
}

// Тест для массива из одного элемента
TEST(merge_sort, single_element_array_test) {
    int arr[1] = {42};
    merge_sort(arr, 0, 0);
    EXPECT_TRUE(is_sorted(arr, 1)); 
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
