#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void type_prompt();
char *getBeforeSpace(char *);
void read_command(char *, char *);

#define TRUE 1

int main() {
  int status;
  char command[600], parameters[600];

  while (TRUE) {
    type_prompt();
    read_command(command, parameters);

    char *args[3];
    args[0] = (char *)malloc(strlen(command) + 6);
    if (args[0] == NULL) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    strcpy(args[0], "/bin/");
    strcat(args[0], command);
    if (!strcmp(parameters, "")) {
      args[1] = NULL;
    } else {
      int numParameters = 1;
      char *token = strtok(parameters, " ");
      while (token != NULL) {
        args[numParameters] = token;
        numParameters++;
        token = strtok(NULL, " ");
      }
      args[numParameters] = NULL;
    }

    if (fork() != 0) {
      /*Codigo do processo pai.*/
      waitpid(-1, &status, 0);
    } else {
      char *envp[] = {"TERM=xterm", NULL};
      execve(args[0], args, envp);
      perror("execve");
    }
  }
  return 0;
}

void type_prompt(){
    char currentDirectory[300];
  if (getcwd(currentDirectory, sizeof(currentDirectory)) != NULL) {
    printf("%s$ ", currentDirectory);
  } else {
    perror("getcwd() error");
  }
}

char *getBeforeSpace(char *string) {
  char *newString = malloc(strlen(string) + 1);
  for (int i = 0; i < strlen(string); i++) {
    if (string[i] == ' ') {
      break;
    } else {
      newString[i] = string[i];
    }
  }
  return newString;
}

void read_command(char *command, char *parameters) {
  char input[600];
  fgets(input, sizeof(input), stdin);
  char *newline = strchr(input, '\n');
  if (newline != NULL) {
    *newline = '\0'; // Remover a quebra de linha
  }

  char *firstSpace = strchr(input, ' ');

  if (firstSpace != NULL) {
    firstSpace[0] = '\0'; // Separar o comando dos parâmetros
    strcpy(parameters, firstSpace + 1);
  } else {
    strcpy(parameters, ""); // Sem parâmetros
  }
  strcpy(command, getBeforeSpace(input));
}