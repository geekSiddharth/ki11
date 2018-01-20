#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define LINE_LIMIT 2012
#define TOKEN_LIMIT 256
#define HISTORY_FILE ".ki11/his"
#define HISTORY_LINE 50

int init_shell() {
    printf("Welcome to ki11\n\n");
    return 0;
}

int cd(int argc, char **argv) {

    // handling too few arguments
    if (argc < 2) {
        perror("ERROR: At least one argument required");
        return -1;
    }

    // handling to may arguments
    if (argc > 2) {
        perror("ERROR: Bad arguments");
        return -1;
    }

    // finally changing the directory
    if (chdir(argv[1])) {
        perror("ERROR: in chdir");
        return -1;
    }

    return 0;
}

int pwd() {
    char line[LINE_LIMIT];
    if (getcwd(line, LINE_LIMIT)) {
        printf("%s\n", line);
        return 0;
    }
    perror("ERROR: in cwd");
    return -1;
}

int execute(int argc, char **argv) {

    if (strcmp(argv[0], "exit") == 0) {
        exit(1);
    } else if (strcmp(argv[0], "pwd") == 0) {
        return pwd();
    } else if (strcmp(argv[0], "cd") == 0) {
        return cd(argc, argv);
    } else if (strcmp(argv[0], "echo") == 0) {

    } else if (strcmp(argv[0], "history") == 0) {

    } else {
        // do fork and stuffs
    }

    return 1;
}

int main(void) {

    if (init_shell()) {
        perror("ERROR: shell initialisation");
    }


    char line[LINE_LIMIT]; // user input line
    char *argv[TOKEN_LIMIT]; // stores tokens of a input line. similar to argv of main or any other command
    int argc; // keeps tracks of the number of arguments used
    char dir_name[TOKEN_LIMIT];

    while (1) {

        getcwd(dir_name, TOKEN_LIMIT);
        printf("%s>", dir_name);

        // We empty the line buffer
        memset(line, '\0', LINE_LIMIT);

        //reads lines
        fgets(line, LINE_LIMIT, stdin);

        //for handling empty lines
        if ((argv[0] = strtok(line, " \t\n")) == NULL) {
            continue;
        }

        // now breaking input line and breaking it into tokens
        argc = 1;
        while ((argv[argc] = strtok(NULL, " \t\n")) != NULL) {
            argc++;
        }


//        FILE *file = fopen(HISTORY_FILE, "a");
//        fprintf(line, file);
//        fclose(file);


        execute(argc, argv);
    }

    return 0;
}
