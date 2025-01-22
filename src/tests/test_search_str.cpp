#include <gtest/gtest.h>
#include <pthread.h>
#include <cstring>
#include <cstdlib>

#define ARRAY_SIZE 1000000
#define STRING_LENGTH 20

char *data[ARRAY_SIZE];


void* search_load(void* arg) {
    int repetitions = *((int*)arg);
    char target[STRING_LENGTH] = "target";

    for (int r = 0; r < repetitions; r++) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if (strcmp(data[i], target) == 0) {
                break;
            }
        }
    }
    return NULL;
}

// Тестовая фикстура для инициализации данных
class SearchLoadTest : public ::testing::Test {
protected:
    void SetUp() override {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            data[i] = static_cast<char*>(malloc(STRING_LENGTH));
            snprintf(data[i], STRING_LENGTH, "string%d", i);
        }
        // Устанавливаем один из элементов на "target" для тестирования
        data[ARRAY_SIZE / 2] = static_cast<char*>(malloc(STRING_LENGTH));
        snprintf(data[ARRAY_SIZE / 2], STRING_LENGTH, "target");
    }

    void TearDown() override {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            free(data[i]);
        }
    }
};

// Тест на успешный поиск
TEST_F(SearchLoadTest, TestSearchLoadSuccess) {
    int repetitions = 1;
    pthread_t thread;
    pthread_create(&thread, NULL, search_load, &repetitions);
    pthread_join(thread, NULL);
}

// Тест на отсутствие "target" в данных
TEST_F(SearchLoadTest, TestSearchLoadNoTarget) {
    // Удаляем "target" из данных
    free(data[ARRAY_SIZE / 2]);
    data[ARRAY_SIZE / 2] = static_cast<char*>(malloc(STRING_LENGTH));
    snprintf(data[ARRAY_SIZE / 2], STRING_LENGTH, "string_no_target");

    int repetitions = 1;
    pthread_t thread;
    pthread_create(&thread, NULL, search_load, &repetitions);
    pthread_join(thread, NULL);
}

// Тест на многопоточность
TEST_F(SearchLoadTest, TestSearchLoadMultipleThreads) {
    int repetitions = 10;
    pthread_t threads[6];

    for (int i = 0; i < 6; i++) {
        pthread_create(&threads[i], NULL, search_load, &repetitions);
    }

    for (int i = 0; i < 6; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
