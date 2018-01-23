#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>


int main(int argc, char **argv) {


    int end_line = 0; // -E
    int number_line = 0; // -n

    FILE *fileptr;

    if (argc <= 1) {
        printf("At least one argument is required");
        return 1;
    }



    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-E") == 0) {
            end_line = 1;
        } else if (strcmp(argv[i], "-n") == 0) {
            number_line = 1;
        } else if (argv[i][0] != '-' && strcmp(argv[i], "") != 0) {


            //getting the real path
            char realPath[1024];
            realpath(argv[i],realPath);

            struct stat sb;

            if (stat(realPath, &sb) == 0 && S_ISDIR(sb.st_mode))
            {
                // to check if it is directory
                printf("\"%s\" is a directory\n", argv[i]);
                return -1;
            }

            fileptr = fopen(realPath, "r");
        }
    }


    if (fileptr) {
        //if file is opened


        char *line_read = NULL;
        size_t len = 0;
        int counter = 1;

        while (getline(&line_read, &len, fileptr) != -1) {
            if(number_line == 1 && end_line ==1) {
                printf("%d\t$%s", counter++, line_read);
            } else if (number_line == 1) {
                printf("%d\t%s", counter++, line_read);
            } else if (end_line==1){
                printf("$%s", line_read);
            } else{
                printf("%s",line_read);
            }
        }

//        // prints everything character by character
//        char c;
//        while ((c = (char) fgetc(fileptr)) != EOF) {
//            if (end_line == 1 && c == '\n') {
//                printf("$");
//            }
//            if (number_line >= 1 && c == '\n' ) {
//                number_line++;
//                printf("\n\t%d\t", number_line);
//                continue;
//            }
//            printf("%c", c);
//        }
        fclose(fileptr);

    } else {
        printf("Unable to read the file or it doesn't exists \"%s\" \n", argv[1]);
    }

}