cmake_minimum_required(VERSION 3.3)
project(grepple)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/lists/linked_list.c
    src/lists/linked_list.h
    src/stack/stack.c
    src/stack/stack.h
        src/file.c
        src/file.h
    src/fs_parser.c
    src/fs_parser.h
    src/init.c
    src/init.h
    src/main.c
    src/match_printer.c
    src/match_printer.h
    src/options.c
    src/options.h
        src/search.c
        src/search.h
    src/util.c
    src/util.h
    src/mem.h
    tests/dir_list.c
    tests/file_type_test.c
    tests/ignore.c
    tests/init.c
    tests/init_test.c
    tests/main.c
    tests/opts.c
    tests/searcher_test.c src/grepple.h src/grepple.c)

add_executable(grepple ${SOURCE_FILES})