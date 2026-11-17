#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/_types/_ssize_t.h>

static_assert(__STDC_VERSION__ >= 202311L, "C23 is required");

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
    /* int status; */

    while (1) {
        printf("> ");
        fflush(stdout);

        char *line = shell_readline();
        if (line == NULL) {
            break;
        }

        shell_split_line(line);
        free(line);
    }
}

int main(void) {
    shell_loop();
    return EXIT_SUCCESS;
}

