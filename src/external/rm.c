#define _XOPEN_SOURCE 500

#include <ftw.h>
#include <stdio.h>
#include <string.h>
#include <zconf.h>

int force = 0;
int recursive = 0;
int _dir = 0;

static int remove_file(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {

    if (force == 1 || _dir == 1) {

        // removes files and directory
        if (remove(fpath)) {
            perror("ERROR: remove");
            return -1;
        }
    } else {

        //removes files
        if (unlink(fpath)) {
            perror("ERROR: unlink");
            return -1;
        }
    }
}

int main(int argc, char **argv) {

    char name[256];

    for (int j = 1; j < argc; ++j) {
        if (strcmp(argv[j], "-f") == 0) {
            force = 1;
        } else if (strcmp(argv[j], "-r") == 0) {
            recursive = 1;
        } else if (strcmp(argv[j], "-d") == 0) {
            _dir = 1;
        } else if (argv[j][0] != '-') {
            strcpy(name, argv[j]);
        } else {
            perror("ERROR: unknown arguments");
            return -1;
        }
    }


    if (recursive == 1) {

        //this is the ultimate rm -rf
        if (nftw(name, remove_file, 10, (FTW_DEPTH | FTW_MOUNT | FTW_PHYS))) {
            perror("ERROR: ftw");
            return -1;
        }

    } else if (_dir == 1) {

        // removes empty directory only
        if(rmdir(name)) {
            perror("ERROR: rmdir");
            return -1;
        }
    } else {

        // removes files only
        if(unlink(name)) {
            perror("ERROR: unlink");
            return -1;
        }
    }

    return 1;
}