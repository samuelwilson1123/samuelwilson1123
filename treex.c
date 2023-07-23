#include "print.h"

int main(int argc, char * argv[])
{

    char * path = ".";
    char * union_path = "null";
    char * indents[1024];

    int depth = -1;
    int premissions = 0;
    int size = 0;

    int isint = 1;

    if (argc > 1 && (strcmp(argv[1], "-d") != 0) 
    && (strcmp(argv[1], "-p") != 0) 
    && (strcmp(argv[1], "-s") != 0)
    && (strcmp(argv[1], "-u") != 0))
    {
        path = argv[1];
    }

    int opt;
    while ((opt = getopt(argc, argv, "hu:d:ps")) != -1)
    {
        switch (opt)
        {
            case 'h':
                return print_usage();;

            case 'u':

                union_path = optarg;
                break;

            case 'd':
                
                // checking if optarg is an int
                for (int i = 0; i < strlen(optarg); i++)
                {
                    if (isdigit(optarg[i]) == 0)
                    {
                        printf("-d requires an integer input\n");
                        isint = 0;
                        return -1;
                    }
                }

                if (isint == 1)
                {
                    depth = atoi(optarg);
                }
                break;

            case 'p':
                premissions = 1;
                break;

            case 's':
                size = 1;
                break;

        } 
    }

    if (strcmp("null", union_path) == 0)
    {
        printf("%s\n", path);
        print_tree(path, 0, indents, depth, premissions, size);
    }
    else
    {
        printf("%s U %s\n", path, union_path);
        print_union_tree(path, union_path, 0, indents, depth, premissions, size);
    }


}

int print_usage()
{
    printf("Usage: ./treex [directory] [-d depth] [-s] [-p] [-u directory] [-h]\n");
    printf("    [directory] specifies which directory you wish to be the root of \n");
    printf("the tree. If a directory is not specified then the directory is '.'\n");
    printf("    [-d depth] specifies the max depth you want the tree to go, with depth\n");
    printf("being an integer.\n");
    printf("    [-s] is used when you want to show the file sizes of all the files\n");
    printf("    [-p] is used when you want to show the premissions of all the files\n");
    printf("    [-u directory] makes it so the tree that prints is a union of the given directory\n");
    printf("and the root directory that can be provided using [directory]\n");
    printf("    [-h] displays a usage menu\n");
    return 1;
}