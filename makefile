all:
	gcc -g src/main.c src/options.c src/init.c src/fs_parser.c src/stack/stack.c src/lists/linked_list.c src/util.c src/searcher.c src/filer.c src/match_printer.c -o grepple
