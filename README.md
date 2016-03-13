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

# Bugs
* Circumvent the exhausting of Linux file descriptors in MASSIVE code bases. AKA -- Try and reuse the same file descriptor for each file.

# To do
* Utilize signal handling to ensure, to highest possibility, that we are cleaning up memory before termination.
* Highlight keyword in output
* Utilize a testing framework.
* Check for binary files.
* Make it cross platform (win32)
