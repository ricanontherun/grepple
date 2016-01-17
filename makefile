all:
	gcc -g src/main.c src/grepple.c deps/linux/list.h src/dir.c src/stack/stack.c src/lists/linked_list.c src/util.c src/search.c src/file.c src/match_printer.c -o grepple
