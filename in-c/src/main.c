#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_ssize_t.h>
#include <unistd.h>

static_assert(__STDC_VERSION__ >= 202311L, "C23 is required");

int shell_execute(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: no arguments provided \n");
            return 1;
        }
        if (chdir(args[1]) == -1) {
           perror("error when changing directories");
        }

        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        execvp(args[0], args);
        perror(args[0]);
        _exit(EXIT_FAILURE);
    } else {
        if (waitpid(pid, NULL, 0) == -1) {
            perror("waitpid");
        }
    }

    return 1;
}

char **shell_split_line(char *line) {
    int bufsize = 64;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));

    if (tokens == NULL) {
        fprintf(stderr, "initial token allocation error");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(line, " \t\r\n");

    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += 64;
            char **new_tokens = realloc(tokens, bufsize * sizeof(char*));

            if (new_tokens == NULL) {
                fprintf(stderr, "token reallocation error");
                free(tokens);
                exit(EXIT_FAILURE);
            }

            tokens = new_tokens;
        }


        token = strtok(NULL, " \t\r\n");
    };

    tokens[position] = NULL;
    return tokens;
}

char *shell_readline(void) {
    char *line = NULL;
    size_t capacity = 0;

    if (getline(&line, &capacity, stdin) == -1) {
        free(line);
        return NULL;
    }

    return line;
}

void shell_loop(void) {
    int status;

    do {
        printf("> ");
        fflush(stdout);

        char *line = shell_readline();
        if (line == NULL) {
            break;
        }

        char **args = shell_split_line(line);
        status = shell_execute(args);


        free(args);
        free(line);
    } while (status);
}

int main(void) {
    shell_loop();
    return EXIT_SUCCESS;
}

