#include <stdio.h>

#define TRUE 1

int main(){

    while(TRUE){
        type_prompt();
        read_command(command, parameters);

        if(fork() != 0){
            /*Codigo do processo pai.*/
            waitpid(-1, &status, 0);
        } else {
            /* Codigo do processo filho*/
            execve(command, paramenters, 0);
        }
    }




    return 0;
}