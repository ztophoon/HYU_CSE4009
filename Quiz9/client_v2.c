#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUF 10
#define MAX(a,b) ((a)>(b)?(a):(b))

void error_exit(const char* str) {
    printf("%s\n", str);
    exit(1);
}

// Usage: ./client pipe_name
int main(int argc, char* argv[]) {
    char mystring[MAX_BUF];
    char mystring2[MAX_BUF];
    mystring[0] = 0;
    
    if(argc!= 2) error_exit("incorrect usage");
    FILE* outfile = fopen("KNOWN_FIFO", "w");
    if(!outfile) error_exit("KNOWN_FIFO");
    FILE* infile = fopen(argv[1], "r");
    if(!infile) error_exit(argv[1]);
    printf("open '%s' finished\n", argv[1]);

    fd_set rset, wset;
    fd_set result_r, result_w;
    FD_ZERO(&rset); // read set
    FD_ZERO(&wset); // write set

    FD_SET(STDIN_FILENO, &rset);
    FD_SET(fileno(infile), &rset);
    FD_SET(fileno(outfile), &wset);

    int maxfdp1 =MAX(fileno(infile), fileno(outfile)) + 1;
    
    while(1) {
        result_r = rset;
        result_w = wset;
        
        if((select(maxfdp1, &result_r, &result_w, NULL, NULL) < 0))
            error_exit("select error");

        if(FD_ISSET(STDIN_FILENO, &result_r)) {
            fgets(mystring, MAX_BUF, stdin);
            printf("to KNOWN_FIFO: '%s'\n", mystring);
            fprintf(outfile, "%s", mystring);
        }

        if(FD_ISSET(fileno(infile), &result_r)) {
            fgets(mystring2, MAX_BUF, infile);
            printf("from %s to KNOWN_FIFO : '%s' \n", argv[1], mystring2);
        }

        if(FD_ISSET(fileno(outfile), &result_w)) {
            fflush(outfile);
        }
    }

    fclose(infile);
    fclose(outfile);
    
    return 0;
}
