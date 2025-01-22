rm -rf ./build/* tests
mkdir build

echo "SHELL compilation"
gcc -o build/shell src/c/shell.c src/c/utils.c cache.so

echo "SORT compilation"
gcc -o build/sort src/c/sort.c src/c/sort_start.c

echo "EMA-SEARCH-STR compilation"
gcc -o build/ema-search-str src/c/utils.c src/c/ema_search_str.c cache.so

echo "BENCH compilation"
gcc -o build/bench src/c/sort.c src/c/utils.c src/c/controller.c


mkdir -p tests/build

g++ -o  tests/build/test_sort src/c/sort.c  src/tests/test_sort.cpp -lgtest -lgtest_main -pthread
g++ -o  tests/build/test_search_str src/tests/test_search_str.cpp -lpthread -lgtest -lgtest_main -pthread

./tests/build/test_sort
./tests/build/test_search_str


