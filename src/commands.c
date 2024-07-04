#include "stdio.h"
#include "string.h"
#include "unistd.h"

int lgz_execute(char **args);
int lgz_cd(char **args);
int lgz_help(char **args);
int lgz_exit(char **args);

// List of builtin commands, followed by their corresponding functions.
char *builtin_str[] = {"cd", "help", "exit"};

int (*builtin_func[])(char **) = {lgz_cd, lgz_help, lgz_exit};

int lgz_num_builtins() { return sizeof(builtin_str) / sizeof(char *); }

// Builtins function implementations.
int lgz_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "lgz: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lgz");
    }
  }
  return 1;
}

int lgz_help(char **args) {
  int i;
  printf("Ligooz terminal, LGZ\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < lgz_num_builtins(); i++) {
    printf(" %s\n", builtin_str[i]);
  }

  printf("Use the man commanf for information on other programs.\n");
  return 1;
}

int lgz_exit(char **args) { return 0; }


int lgz_execute(char **args) {
    int i;

    if (args[0] == NULL) {
        // An emoty command was entered.
        return 1;
    }

    for (i = 0; i < lgz_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }
}   
