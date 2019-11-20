#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUF 10
// Usage: ./client pipe_name

int main(int argc, char *argv[]){
    char mystring[MAX_BUF];

    FILE* outfile = fopen("KNOWN_FIFO", "W");
    if(!outfile) 
        error();
    printf("file open finished\n");

    while(fgets(mystring, MAX_BUF, stdin) != NULL){
        printf("to KNOWN_FIFO: '%s'\n", mystring);
        fprintf(outfile, "%s", mystring);
        fflush(outfile);
    }

    printf("EOF from KNOWN_FIFO\n");
    fclose(outfile);

    return 0;
}
