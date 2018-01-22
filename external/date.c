#include <time.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

    if(argc > 3) {
        perror("ERROR: Too many options");
        return -1;
    }


    char format[256] = "%a %b %d %H:%M:%S %Z %Y";
    time_t t = time(NULL); // returns seconds passed since January 1, 1970
    struct tm *tm=localtime(&t);

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-u") == 0) {
            tm = gmtime(&t);
        } else if (strcmp(argv[i], "-R") == 0) {
            strcpy(format,"%a %b %d %H:%M:%S %Y %z");
        } else {
            perror("ERROR: bad argument ");
            return -1;
        }
    }


    char temp[1000];
    strftime(temp, sizeof temp, format, tm);
    printf("%s\n", temp);

    return 0;
}
