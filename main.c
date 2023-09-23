#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void type_prompt();

#define TRUE 1

int main(){

    int status, res;

    while(TRUE){
        type_prompt();
        //read_command(command, parameters);
        res = fork();
        if(res != 0){
            /*Codigo do processo pai.*/
            //waitpid(-1, &status, 0);
        } else {
            /* Codigo do processo filho*/
            //execve(command, paramenters, 0);
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