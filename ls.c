#include <dirent.h>
#include <stdio.h>

int main(int argc, char **argv) {


    DIR *directory;

    int all = 0;
    int 

    if(argc>1) {
        // case in which argument is suplied
        directory = opendir(argv[1]);
    } else {
        //no argument case or empty argument case
        directory = opendir(".");
    }

    if (directory) {
        // if we successfully read te directory

        struct dirent *structdirent;

        while ((structdirent = readdir(directory)) != NULL) {
            printf("%s\n", structdirent->d_name);
        }

        closedir(directory);
    } else {
        printf("\"%s\" is not directory or it was not found\n", argv[1]);
    }
    return(0);
}