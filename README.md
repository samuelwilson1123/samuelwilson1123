Samuel Wilson 811234336
This program prints a tree of a given directory structure. To make this file, 
simply use the 'make' command and the Makefile will do the rest. If you want to 
use the file, follow these usage guidelines:
    ./treex [directory] [-d depth] [-s] [-p] [-u directory] [-h]
All of the arguments in [] are optional, however any two arguments in the same
[] are required together. The order does not matter as long as [directory] comes
before all other arguments.
    [directory] specifies which directory you wish to be
the root of the tree. If a directory is not specified then the directory is '.'
    [-d depth] specifies the max depth you want the tree to go, with depth being
an integer.
    [-s] is used when you want to show the file sizes of all the files
    [-p] is used when you want to show the premissions of all the files
    [-u directory] makes it so the tree that prints is a union of the given directory
and the root directory that can be provided using [directory]
    [-h] displays a usage menu
