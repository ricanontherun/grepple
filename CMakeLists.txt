cmake_minimum_required(VERSION 3.3)
project(grepple)

set(SOURCE_FILES
        src/main.c
        src/grepple.c
        src/dir.c
        src/file.c
        src/output.c
        src/search.c
        src/util.c
        deps/linux/list.h
        src/lists/linked_list.c
        src/stack/stack.c)
add_executable(grepple ${SOURCE_FILES})