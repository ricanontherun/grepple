grepple
=======

Similar to grep/awk/ag, search a set of files for a keyword.

# Installation
* Using gcc (Ubuntu 4.8.2-19ubuntu1) 4.8.2
* make

# Usage
Examples coming
'grepple --help'

# Performance
Albeit grepple lacks the power of grep (for now), awk or ag, it executes basic keyword searches in half the time.

# To do
* Implement the ability to search a single file.
* More tests for main file parsing routine
* More tests for main file opening routine, check for binary files.
* Perform benchmarking. If performance is sub par, introduce pthreads?
