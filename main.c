#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <zconf.h>
#include <sys/wait.h>

#define LINE_LIMIT 2012
#define TOKEN_LIMIT 256
#define HISTORY_LINE 50

FILE *file;
char prevpath[LINE_LIMIT];
char PATH[LINE_LIMIT];

int init_shell() {

    printf("\n\t===============================\n");
    printf("\t\tWelcome to ki11\n");
    printf("\t\tMade by Siddharth\n");
    printf("\t===============================\n\n");

    char line[LINE_LIMIT];
    getcwd(line, LINE_LIMIT);


    setenv("PATH", strcat(line, "/bin/"), 1);

    file = fopen(strcat(getenv("HOME"), "/ki11"), "a+");
    return 0;
}

int echo(char *line) {


    if(line[0]=='-' && line[1]=='E') {
        line = line + 3;
    }


    int a=0, b = 0;
    // to remove the outer " or '
    // keeps inner " or '
    for (char *x = line; *x != 0; x++) {
        if (*x == '\'' && !a) {
            a = 1, b = 1;
        } else if (*x == '\'' && a && b) {
            a = 0, b = 0;
        } else if (*x == '"' && !a) {
            a = 1, b = 0;
        } else if (*x == '"' && a && !b) {
            a = 0, b = 0;
        } else {
            printf("%c", *x);
        }
    }
    return 0;
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

int print_history(int argc, char **argv) {

    int tail = 0;
    if (argc > 1) {

        // clear history
        if (strcmp(argv[1], "-c") == 0) {
            ftruncate(fileno(file), 0);
            fprintf(file, "history -c\n");
            return 0;
        }

        // read content from a file and append it to this history
        if (strcmp(argv[1], "-a") == 0) {

            if (argc < 3) {
                perror("ERROR: Mention the file name to read from");
                return -1;
            }

            FILE *toopen = fopen(argv[2], "r");
            fseek(file, 0, SEEK_END);
            if (toopen) {
                char c;
                while ((c = (char) fgetc(toopen)) != EOF) {
                    fprintf(file, "%c", c);
                }
                fclose(toopen);
            } else {
                perror("ERROR: ");
                return -1;
            }
            return 0;
        }

        // last option for printing last x lines
        tail = atoi(argv[1]);
        int seek_val = 2;
        fseek(file, 0, SEEK_END);
        int end = (int) ftell(file);

        while (tail != 0 && seek_val < end) {

            fseek(file, end - seek_val, SEEK_SET);
            if (fgetc(file) == '\n') {
                tail--;
            }
            seek_val++;
        }

    } else {
        fseek(file, 0, SEEK_SET);
    }

    char *line_read = NULL;
    size_t len = 0;
    int counter = 1;

    while (getline(&line_read, &len, file) != -1) {
        printf("%d\t%s", counter++, line_read);
    }

}


int execute(int argc, char **argv) {

    if (strcmp(argv[0], "exit") == 0) {
        exit(1);
    } else if (strcmp(argv[0], "pwd") == 0) {
        return pwd();
    } else if (strcmp(argv[0], "cd") == 0) {
        return cd(argc, argv);
    } else if (strcmp(argv[0], "history") == 0) {
        print_history(argc, argv);
        return 0;
    } else {

        pid_t pid;
        pid = fork();

        if (pid < 0) {
            perror("ERROR: ");
        } else if (pid == 0) {
            //child process
            if (execvp(argv[0], argv) == -1) {
                perror("ERROR:");
                kill(getpid(), SIGTERM);
            }

        } else {
            // parent process
            int pid_status;
            if (waitpid(pid, &pid_status, 0) == -1) {
                printf("Error waiting for child process");
            }
        }

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
        printf("[ %s ] $", dir_name);

        // We empty the line buffer
        memset(line, '\0', LINE_LIMIT);

        //reads lines
        fgets(line, LINE_LIMIT, stdin);


        if (strlen(line) > 3 && line[0] == 'e' && line[1] == 'c' && line[2] == 'h' && line[3] == 'o') {
            echo(line + 5);
            continue;
        }

        if (strlen(line) > 1) {
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
