#grepple

File searching utility for linux.

# Installation (Linux)
* git clone https://github.com/ricanontherun/grepple
* cd grepple
* make (gcc 4.6.2)
* sudo mv grepple /bin

# Usage & Examples

Display Help

`grepple --help`

Search a single file (main.c) for grepple_init

`grepple main.c "grepple_init"`

Recursively search the current directory for stat_file_type.

`grepple -r . "stat_file_type"`

Recursively search the jquery directory, ignoring all .js files, for regex_email"

`grepple -r --ignore[.js] jquery "regex_email"`

# Performance
Albeit grepple lacks the power of grep (for now), ack or ag, it executes basic keyword searches in about half the time.

# To do
* Color format terminal output
* More tests for main file parsing routine
  * Circumvent the exhausting of Linux file descriptors in MASSIVE code bases. AKA -- Try and reuse the same file     descriptor for each file.
* Check for binary files.
* Make it cross platform (win32)
* Left trim hit context.
