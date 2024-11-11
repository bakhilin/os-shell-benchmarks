project(os-shell-benchmarks)
include_directories(include)

set(SOURCES
    source/main.c
    source/utils.c
)

add_executable(build/os-shell-benchmarks ${SOURCES})
