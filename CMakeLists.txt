cmake_minimum_required(VERSION 3.3)
project(grepple)

set(SOURCE_FILES src/lists/linked_list.c src/stack/stack.c src/file.c
    src/fs_parser.c
    src/match_printer.c
    src/options.c
    src/search.c
    src/util.c
    tests/dir_list.c
    tests/file_type_test.c
    tests/ignore.c
    tests/init.c
    tests/init_test.c
    tests/main.c
    tests/opts.c
    tests/searcher_test.c src/grepple.c)

add_executable(grepple ${SOURCE_FILES})