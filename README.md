# grepple
A simple and super fast source code searching utility.

# Installation (Linux)
* git clone https://github.com/ricanontherun/grepple
* cd grepple
* sudo make
* sudo make clean

# Usage & Examples

### Basic

Display Help

`grepple --help`

Search a single file (main.c) for "grepple_init"

`grepple main.c grepple_init`

Recursively search the current directory for stat_file_type.

`grepple -r . "stat_file_type"`

Recursively search the src directory for uint32_t

`grepple -r src uint32_t`

The p flag tells grepple to treat the needle argument as a POSIX regular expression.

`grepple -rp src ^[a-zA-Z0-9_]*$`

# Performance
Although grepple lacks the power of grep (for now), ack or ag, it executes basic keyword searches in about half the time. As I continue adding features, this speed will no doubt diminish. Benchmark analysis to come.

# Bugs
* Circumvent the exhausting of Linux file descriptors in MASSIVE code bases. AKA -- Try and reuse the same file descriptor for each file.
* When displaying results, file lines are printed last to first.

# To do
* Improve output: Colors, group results by file, when a user specifies a single file don't print it in the results.
* Utilize a testing framework.
* Check for binary files.
* Make it cross platform (win32)
