#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>

#define LINE_LIMIT 2012
#define TOKEN_LIMIT 256
#define HISTORY_LINE 50

FILE *file;
char prevpath[LINE_LIMIT];

int init_shell() {
    using_history();
    printf("Welcome to ki11\n\n");
    file = fopen(".ki11", "a+");
    return 0;
}

int cd(int argc, char **argv) {

    char temp[LINE_LIMIT];
    strcpy(temp, prevpath);

    // for - option
    getcwd(prevpath, LINE_LIMIT);

    // handling blank argument
    if (argc < 2) {
        if (chdir(getenv("HOME"))) {
            perror("ERROR: Not able to go to HOME");
            return -1;
        }
        return 1;
    }

    // handling to many arguments
    if (argc > 2) {
        perror("ERROR: Bad arguments");
        return -1;
    }


    if (strcmp(argv[1], "-") == 0) {
        if (chdir(temp)) {
            perror("ERROR: Not able to go to prev path");
            return -1;
        }
        printf("\n%s\n", temp);
    } else if (strcmp(argv[1], "~") == 0) {
        if (chdir(getenv("HOME"))) {
            perror("ERROR: Not able to go to HOME");
            return -1;
        }
    } else {
        // finally changing the directory
        if (chdir(argv[1])) {
            perror("ERROR: in chdir");
            return -1;
        }

    }

    return 1;
}

int pwd() {

    char line[LINE_LIMIT]; // to store the path

    if (getcwd(line, LINE_LIMIT)) {
        printf("%s\n", line);
        return 0;
    }

    perror("ERROR: in cwd");
    return -1;
}

void print_history() {
    fseek(file,0,SEEK_SET);
    char c;
    while ((c = (char) fgetc(file)) != EOF) {
        printf("%c", c);
    }

//
//    HIST_ENTRY **the_history_list = history_list();
//
//    int counter = 0;
//    while (the_history_list[counter]!=NULL) {
//        printf(the_history_list[counter++]->line);
//    }
//
//

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
        print_history();
        return 0;
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

        if(strlen(line)>1) {
            //maintaining the history file
            fprintf(file, "%s", line);
            fflush(file);

//            add_history(line);
        }

        //for handling empty lines
        if ((argv[0] = strtok(line, " \t\n")) == NULL) {
            continue;
        }




        // now breaking input line and breaking it into tokens
        argc = 1;
        while ((argv[argc] = strtok(NULL, " \t\n")) != NULL) {
            argc++;
        }


        execute(argc, argv);
    }

    return 0;
}
