all:
	gcc -g src/main.c src/options.c src/init.c src/fs_parser.c src/stack/stack.c src/searcher.c src/filer.c src/match_printer.c -o grepple
