# SOFE 3950U: Operating Systems

## TUTORIAL #6: POSIX Threads Part II

### Objectives
- Learn the fundamentals of multithreading
- Gain experience using POSIX threads

### Important Notes
- Work in groups of three students
- All reports must be submitted as a PDF on blackboard, if source code is included submit everything as an archive (e.g. zip, tar.gz)
- Save the file as `<tutorial_number>_<first student’s id>.pdf` (e.g. tutorial6_100123456.pdf)
- If you cannot submit the document on Blackboard then please contact the TA (Omar Hemied) [Omar.hemied@ontariotechu.ca](mailto:Omar.hemied@ontariotechu.ca)

### Notice
It is recommended for this lab activity and others that you save/bookmark the following resources as they are very useful for C programming.
- [http://en.cppreference.com/w/c](http://en.cppreference.com/w/c)
- [http://www.cplusplus.com/reference/clibrary/](http://www.cplusplus.com/reference/clibrary/)
- [http://users.ece.utexas.edu/~adnan/c-refcard.pdf](http://users.ece.utexas.edu/~adnan/c-refcard.pdf)
- [http://gribblelab.org/CBootcamp](http://gribblelab.org/CBootcamp)

The following resources are helpful as you will need to use pthreads in order to make your program multithreaded.
- [https://computing.llnl.gov/tutorials/pthreads/](https://computing.llnl.gov/tutorials/pthreads/)
- [http://randu.org/tutorials/threads/](http://randu.org/tutorials/threads/)
- [http://pages.cs.wisc.edu/~travitch/pthreads_primer.html](http://pages.cs.wisc.edu/~travitch/pthreads_primer.html)
- [http://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/](http://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/)

### Conceptual Questions
1. What is `fork()`, how does it differ from multi-threading (pthreads)?
2. What is inter-process communication (IPC)? Describe methods of performing IPC.
3. Provide an explanation of semaphores, how do they work, how do they differ from mutual exclusion?
4. Provide an explanation of wait (P) and signal (V).
5. Research the main functions used for semaphores in `<semaphore.h>` and explain each function.

### Application Questions

All of your programs for this activity can be completed using the template provided, where you fill in the remaining content. A makefile is not necessary, to compile your programs use the following command in the terminal. If you do not have clang then replace clang with gcc, if you use gcc you must use -pthread instead of -lpthread. If you are still having issues please use -std=gnu99 instead of c99.

```bash
clang -Wall -Wextra -std=c99 -lpthread <program name>.c -o <program name>
