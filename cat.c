#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {


    int end_line = 0;
    int number_line = 0;

    if (argc <= 1) {
        printf("At least one argument is required");
        return 1;
    }

    if (argc > 2) {
        for (int i = 1; i < argc; ++i) {
            if (strcmp(argv[i], "-E") == 0) {
                end_line = 1;
            } else if (strcmp(argv[i], "-n") == 0) {
                printf("\t1\t");
                number_line = 1;
            }
        }
    }

    FILE *fileptr;
    fileptr = fopen(argv[1], "r");

    if (fileptr) {
        //if file is opened

        // prints everything character by character
        char c;
        while ((c = (char) fgetc(fileptr)) != EOF) {
            if(end_line == 1 && c=='\n') {
                printf("$");
            }
            if(number_line >= 1 && c=='\n') {
                number_line++;
                printf("\n\t%d\t", number_line);
                continue;
            }
            printf("%c", c);
        }
        fclose(fileptr);
    } else {
        printf("Unable to read the file or it doesn't exists \"%s\" \n", argv[1]);
    }

}