#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define SIZE_OF_BUFFER 1024

FILE* fp_r = NULL;
FILE* fp_w = NULL;

string defaultGitPath;
string defaultCommandString = "git ls-files `git rev-parse --show-toplevel` ";
string defaultGrepString = "| grep ";

int main(int argc, char* argv[]){
    // Exception handling
    if(argc < 2){
        perror("there is no command line argument");
        exit(1);
    }

    int sys_result;
    char* buffer = new char[SIZE_OF_BUFFER];

    string tempStr = argv[1];
    string commandStr = defaultCommandString + defaultGrepString + tempStr;
    string tcommandStr = commandStr + "> !gitvim_file_list.txt";

    sys_result = system("touch !gitvim_file_list.txt");
    sys_result = system(tcommandStr);

    int cnt = 0;
    sys_result = system("touch !gitvim_result_list.txt");
    fp_r = fopen("!gitvim_file_list.txt", "r");
    fp_w = fopen("!gitvim_result_list.txt", "w");
    fprintf(fp_w, "--------------------------------------------------------------\n");
    while(!feof(fp_r)){
        fscanf(fp_r, "%[^\n]s", buffer);
        fgetc();
        tempStr = buffer;
        fprint(fp_w, "%s (%d)\n", tempStr, ++cnt);
        if(cnt == 10) break;
    }
    fclose(fp_r);
    fclose(fp_w);

    

    //sys_result = system("rm -f !gitvim_file_list.txt");
    //sys_resutl = system("rm -f !gitvim_result_list.txt");

    delete[] buffer;
    return 0;
}
