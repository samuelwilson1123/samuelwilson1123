#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>

void print_tree(char * path, int indent, char * indents[], int depth, int premissions, int size);
void print_file(char * path, struct dirent * entry, int premissions, int size, int special);
void print_union_tree(char * path1, char * path2, int indent, char * indents[], int depth, int premissions, int size);


#endif