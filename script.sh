rm -rf ./build/*

echo "SHELL compilation"
gcc -o build/shell src/c/shell.c src/c/utils.c

echo "SORT compilation"
gcc -o build/sort src/c/sort.c src/c/sort_start.c

echo "EMA-SEARCH-STR compilation"
gcc -o build/ema-search-str src/c/utils.c src/c/ema_search_str.c

echo "BENCH compilation"
gcc -o build/bench src/c/sort.c src/c/utils.c src/c/controller.c


