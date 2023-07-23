#include "print.h"

// compare function for qsort
int compare_entries(const void *a, const void *b)
{
    struct dirent **entry_a = (struct dirent **)a;
    struct dirent **entry_b = (struct dirent **)b;
    return strcmp((*entry_a)->d_name, (*entry_b)->d_name);

}

// recursively prints tree using a depth first search
void print_tree(char * path, int indent, char * indents[], int depth, int premissions, int size)
{
    DIR * dir = opendir(path);

    if (dir == NULL)
    {
        return;
    }

    // getting number of items so we can see when to use └──
    int num_items = 0;
    struct dirent * entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        num_items++;
    }
    rewinddir(dir);

    // allocate an array of dirent pointers
    struct dirent ** entries = (struct dirent **)malloc(num_items * sizeof(struct dirent *));
    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        entries[i++] = entry;
    }

    // sort the entries
    qsort(entries, num_items, sizeof(struct dirent *), compare_entries);

    // iterate through the sorted entries and print tree
    for (int i = 0; i < num_items; i++) {
        entry = entries[i];

        // drawing tree structure
        for (int j = 0; j < indent; j++) // printing indents
        {
            printf("%s", indents[j]);
        }

        if (i == num_items - 1) // on last item
        {
            printf("└── ");
            indents[indent] = "    ";

        }
        else // not on last item
        {
            printf("├── ");
            indents[indent] = "│   ";

        }

        print_file(path, entry, premissions, size, 0); // print file

        // if file is a directory recursively call print_tree from that directory
        if (entry->d_type == DT_DIR && ((indent + 1) < depth || depth == -1))
        {
            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
            print_tree(new_path, indent + 1, indents, depth, premissions, size);
        }
    }

    // free the array of dirent pointers
    free(entries);
}

// prints out combined tree
void print_union_tree(char * path1, char * path2, int indent, char * indents[], int depth, int premissions, int size)
{

    DIR * dir1 = opendir(path1);
    DIR * dir2 = opendir(path2);

    if (dir1 == NULL || dir2 == NULL)
    {
        return;
    }

    // getting number of items in both directories
    int num_items1 = 0;
    int num_items2 = 0;
    struct dirent * entry1;
    struct dirent * entry2;
    while ((entry1 = readdir(dir1)) != NULL) {
        if (strcmp(entry1->d_name, ".") == 0 || strcmp(entry1->d_name, "..") == 0) {
            continue;
        }

        num_items1++;
    }
    rewinddir(dir1);

    while ((entry2 = readdir(dir2)) != NULL) {
        if (strcmp(entry2->d_name, ".") == 0 || strcmp(entry2->d_name, "..") == 0) {
            continue;
        }

        num_items2++;
    }
    rewinddir(dir2);

    // allocate dirent pointers for both trees
    struct dirent ** entries1 = (struct dirent **)malloc(num_items1 * sizeof(struct dirent *));
    struct dirent ** entries2 = (struct dirent **)malloc(num_items2 * sizeof(struct dirent *));
    int i = 0;
    int j = 0;
    while ((entry1 = readdir(dir1)) != NULL)
    {
        if (strcmp(entry1->d_name, ".") == 0 || strcmp(entry1->d_name, "..") == 0)
        {
            continue;
        }

        entries1[i++] = entry1;
    }
    while ((entry2 = readdir(dir2)) != NULL)
    {
        if (strcmp(entry2->d_name, ".") == 0 || strcmp(entry2->d_name, "..") == 0)
        {
            continue;
        }

        entries2[j++] = entry2;
    }

    // sorting both entries
    qsort(entries1, num_items1, sizeof(struct dirent *), compare_entries);
    qsort(entries2, num_items2, sizeof(struct dirent *), compare_entries);


    // printing both trees
    int k = 0;
    int l = 0;
    while (k < num_items1 && l < num_items2)
    {
        // calculate and print indents
        for (int m = 0; m < indent; m++)
        {
            printf("%s", indents[m]);
        }

        if ((k + l) == (num_items1 + num_items2 - 2))
        {
            printf("└── ");
            indents[indent] = "    ";
        } else 
        {
            printf("├── ");
            indents[indent] = "│   ";
        }

        // comparing the entries and printing the correct one alphabetically
        int cmp = strcmp(entries1[k]->d_name, entries2[l]->d_name);


        // printing out the appropriate file
        if (cmp < 0) {
            print_file(path1, entries1[k], premissions, size, 0);

            if (entries1[k]->d_type == DT_DIR && ((indent + 1) < depth || depth == -1))
            {
                char new_path[1024];
                snprintf(new_path, sizeof(new_path), "%s/%s", path1, entries1[k]->d_name);
                print_tree(new_path, indent + 1, indents, depth, premissions, size);                
            }

            k++;
        } else if (cmp > 0) {
            print_file(path2, entries2[l], premissions, size, 0);

            if (entries2[l]->d_type == DT_DIR && ((indent + 1) < depth || depth == -1))
            {
                char new_path[1024];
                snprintf(new_path, sizeof(new_path), "%s/%s", path2, entries2[l]->d_name);
                print_tree(new_path, indent + 1, indents, depth, premissions, size);                
            }

            l++;
        } else {
            print_file(path1, entries1[k], premissions, size, 1);

            if (entries1[k]->d_type == DT_DIR && ((indent + 1) < depth || depth == -1))
            {
                char new_path1[1024];
                char new_path2[1024];
                snprintf(new_path1, sizeof(new_path1), "%s/%s", path1, entries1[k]->d_name);
                snprintf(new_path2, sizeof(new_path2), "%s/%s", path2, entries2[l]->d_name);
                print_union_tree(new_path1, new_path2, indent + 1, indents, depth, premissions, size);            
            }

            k++;
            l++;
        }

    }

    while (k < num_items1)
    {
        // calculate and print indents
        for (int m = 0; m < indent; m++)
        {
            printf("%s", indents[m]);
        }
        if ((k + l) == (num_items1 + num_items2 - 1))
        {
            printf("└── ");
            indents[indent] = "    ";
        } else 
        {
            printf("├── ");
            indents[indent] = "│   ";
        }


        print_file(path1, entries1[k], premissions, size, 0);
        k++;
    }

    while (l < num_items2)
    {
        // calculate and print indents
        for (int m = 0; m < indent; m++)
        {
            printf("%s", indents[m]);
        }
        if ((k + l) == (num_items1 + num_items2 - 1))
        {
            printf("└── ");
            indents[indent] = "    ";
        } else 
        {
            printf("├── ");
            indents[indent] = "│   ";
        }


        print_file(path2, entries2[l], premissions, size, 0);
        l++;
    }

    // free pointers
    free(entries1);
    free(entries2);

}

void print_file(char * path, struct dirent * entry, int premissions, int size, int special)
{
        struct stat st;

        // printing names in appropriate color
        char temp_path[1024]; // temp path for stat()
        snprintf(temp_path, sizeof(temp_path), "%s/%s", path, entry->d_name);
        if (stat(temp_path, &st) == -1)
        {
            perror("stat");
        }

        if (entry->d_type == DT_DIR && special == 1)
        {
            printf("\033[0;91m%s\033[0m", entry->d_name);
        }
        else if (entry->d_type == DT_DIR) // if directory
        {
            printf("\033[34m%s\033[0m", entry->d_name);
        }
        else if ((st.st_mode & S_IWUSR) == 0) // if read only
        {
            printf("\033[31m%s\033[0m", entry->d_name);
        }
        else if ((st.st_mode & S_IXUSR) == S_IXUSR) // if excecutable
        {
            printf("\033[32m%s\033[0m", entry->d_name);
        }
        else if (special == 1)
        {
            printf("\033[0;35m%s\033[0m", entry->d_name);
        }
        else
        {
            printf("%s", entry->d_name);
        }

        if (premissions == 1)
        {
            printf(" (%o)", st.st_mode & 0777);
        }

        if ((size == 1) && entry->d_type != DT_DIR)
        {
            printf("    %ldK", st.st_size / 1024);
        }
        printf("\n");
}