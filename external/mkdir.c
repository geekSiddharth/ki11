#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF 256
int verbose = 0; // -v
int recursive = 0; // -p


void my_mkdir(char *name, mode_t mode) {
    if (mkdir(name, mode)) {
        if (recursive == 0) {
            printf("Unable to create or it already exists \"%s\" \n", name);
        }
    } else {
        if (verbose == 1) {
            printf("\"%s\" created with mode %d", name, mode);
        }
    }
}


int main(int argc, char **argv) {

    if (argc <= 1) {
        printf("At least one argument is required");
        return 1;
    }

    char name[BUF];

    // TODO: process mode
    mode_t mode = 0777;

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            strcpy(name, argv[i]);
        } else if (strcmp(argv[i], "-p") == 0) {
            recursive = 1;
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        }
    }

    int len = (int) strlen(name);


    // to remove / at the end
    if (name[len - 1] == '/') {
        name[len - 1] = 0;
    }

    if (recursive == 0) {
        my_mkdir(name, mode);
    } else {

        // recursive directory creation
        // https://stackoverflow.com/questions/2336242/recursive-mkdir-system-call-on-unix

        char *p = NULL;

        for (p = name + 1; *p; p++) {
            if (*p == '/') {
                *p = 0;
                my_mkdir(name, mode);
                *p = '/';
            }
        }
        my_mkdir(name, mode);

        return 0;
    }

}

