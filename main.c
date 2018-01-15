#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char **argv) {

    if (argc <= 1) {
        printf("At least one argument is required");
        return 1;
    }

    if (mkdir(argv[1], 0777)) {
        printf("Unable to create \"%s\" \n", argv[1]);
        return 1;
    }
    return 0;

}

