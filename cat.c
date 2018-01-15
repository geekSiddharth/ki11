#include <stdio.h>

int main(int argc, char **argv) {

    if (argc <= 1) {
        printf("At least one argument is required");
        return 1;
    }

    FILE *fileptr;
    fileptr = fopen(argv[1], "r");

    if (fileptr) {
        //if file is opened

        // prints everything character by character
        char c;
        while ((c = (char) fgetc(fileptr)) != EOF) {
            printf("%c", c);
        }
        fclose(fileptr);
    } else {
        printf("Unable to read the file or it doesn't exists \"%s\" \n", argv[1]);
    }

}