COMPILER=gcc
COMPILER_FLAGS=-g

EXECUTABLE=grepple
EXECUTABLE_DIR=/usr/bin

FILES=src/main.c src/grepple.c deps/linux/list.h src/dir.c src/stack/stack.c src/lists/linked_list.c src/util.c src/search.c src/file.c src/output.c

all: build install

build:
	$(COMPILER) $(COMPILER_FLAGS) $(FILES) -o $(EXECUTABLE)

install:
	mv $(EXECUTABLE) $(EXECUTABLE_DIR)/${EXECUTABLE}

clean:
	rm -f src/*.o

rebuild: clean build install
