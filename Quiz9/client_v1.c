#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUF 10

void error(){
    printf("incorrect usage\n");
    exit(1);
}

int main(int argc, char *argv[]){
    char mystring[MAX_BUF];

    if(argc != 2) error();
    FILE* outfile = fopen("KNOWN_FIFO", "w");
    if(!outfile) error();
    printf("KNOWN_FIFO open finished\n");

    FILE* infile = fopen(argv[1], "r");
    if(!infile) error();
    printf("client FIFO open finished\n");

    while(fgets(mystring, MAX_BUF, stdin) != NULL){
        printf("to KNOWN_FIFO: '%s'", mystring);
        fflush(outfile);
        while(fgets(mystring, MAX_BUF, infile) != NULL){
            printf("from %s to KNOWN_FIFO : '%s'\n", argv[1], mystring);
        }
    }

    printf("EOF from KNOWN_FIFO\n");

    fclose(infile);
    fclose(outfile);

    return 0;
}
