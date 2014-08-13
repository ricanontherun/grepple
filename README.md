grepple
=======

Similar to grep/awk/ag, search a set of files or a file for a keyword.

# Installation
## Linux (Ubuntu)
* git clone https://github.com/ricanontherun/grepple
* cd grepple
* make
* sudo mv grepple /bin

# Usage & Examples
## Display Help
`grepple --help`

## Search a single file (main.c) for "grepple_init"
`grepple main.c "grepple_init"`

## Recursively search the current directory for "stat_file_type"
`grepple -r . "stat_file_type"`

# Performance
Albeit grepple lacks the power of grep (for now), awk or ag, it executes basic keyword searches in almost half the time.

# To do
* Color format terminal output
* More tests for main file parsing routine
  * Circumvent the exhausting of Linux file descriptors in MASSIVE code bases. AKA -- Try and reuse the same file     descriptor for each file.
* Check for binary files.
* Perform benchmarking. If performance is sub par, introduce pthreads?
