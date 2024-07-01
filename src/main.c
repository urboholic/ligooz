#include "stdio.h"
#include <complex.h>
#include "stdlib.h"
#include "string.h"

#define LGZ_TOK_BUFSIZE 64 
#define LGZ_TOK_DELIM " \t\r\n\a" 
#define LGZ_RL_BUFSIZE 1024

void lgz_loop(void);
char *lgz_read_line(void);
char **lgz_split_line(char *line);

int main(int argc, char **argv) {
    // load config files.

    // Run command loop. 
    lgz_loop();

    // Perform any shurdown/cleanup.
    return EXIT_SUCCESS;
}

void lgz_loop(void) {
    char *line = NULL;
    char **args = NULL;
    int status = 0;

    do {
        printf("< ");
        line = lgz_read_line();
        args = lgz_split_line(line);
        status = lgz_execute(args);

        free(line);
        free(args);
    } while (status);
}

char *lgz_read_line(void) {

    int bufsize = LGZ_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "lgz: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a character.
        c = getchar();

        // If we hit EOF, replace it with a null character and return.
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate
        
        if (position >= bufsize) {
            bufsize += LGZ_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "lgz: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **lgz_split_line(char *line) {
    int bufsize = LGZ_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "lgz: allocation error\n");
        exit(EXIT_FAILURE);    
    }

    token = strtok(line, LGZ_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += LGZ_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "lgz: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token strtok(NULL, LGZ_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
