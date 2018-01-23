#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE 1000
#define BUFF_STR 1024

int comparator(const void *p, const void *q) {
    return strcasecmp((char *) p, (char *) q);
}




int main(int argc, char **argv) {


    int sort = 0; // -f for not sort
    int all = 0; // -a
    int not_all = 0; //-A

    DIR *directory;



    directory = opendir(".");


    for (int j = 1; j < argc; ++j) {
        if (strcmp(argv[j], "-A") == 0) {
            not_all = 1;
        } else if (strcmp(argv[j], "-a") == 0) {
            all = 1;
        } else if (strcmp(argv[j], "-f") == 0) {
            sort = -1;
        } else if (argv[j][0] != '-' && strcmp(argv[j],"")!=0 ) {
            directory = opendir(argv[j]);
        }
    }

    //will store all the files info
    char arr[MAX_FILE][BUFF_STR];

    if (directory) {
        // if we successfully read te directory

        struct dirent *structdirent;

        int no_of_items = 0;

        while ((structdirent = readdir(directory)) != NULL) {
            strcpy(arr[no_of_items++], structdirent->d_name);
        }
        closedir(directory);

        //Sorting stuffs
        if (sort != -1) {
            qsort((void *) arr, (size_t) no_of_items, sizeof(arr[0]), comparator);
        }

        for (int i = 0; i < no_of_items; ++i) {
            if (all == 0 && not_all == 0 && arr[i][0] == '.') {
                continue;
            }
            if (not_all == 1 && (strcmp(arr[i], ".") == 0 || strcmp(arr[i], "..") == 0)) {
                continue;
            }
            printf("%s\n", arr[i]);
        }

    } else {
        printf("\"%s\" is not directory or it was not found\n", argv[1]);
    }
    return (0);
}