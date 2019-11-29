#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define SIZE_OF_BUFFER 1024

FILE* fp_r = NULL;
FILE* fp_w = NULL;

string defaultCommandString = "git ls-files `git rev-parse --show-toplevel`";
string defaultGrepString = " | egrep \"/?[^/]*";
string defaultGrepString2 = "[^/]*$\"";

int main(int argc, char* argv[]){
    if(argc < 2){
        perror("there is no command line argument ");
        exit(1);
    }

    int sys_result;
    char* buffer = new char[SIZE_OF_BUFFER];

    string tempStr = argv[1];
    //tempStr = "\"" + tempStr + "\"";

    string commandStr = defaultCommandString + defaultGrepString + tempStr + defaultGrepString2;
    string tcommandStr = commandStr + " > !gitvim_file_list.txt";

    sys_result = system("touch !gitvim_file_list.txt");
    sys_result = system(tcommandStr.c_str());

    int cnt = 0;
    sys_result = system("touch !gitvim_result_list.txt");
    fp_r = fopen("!gitvim_file_list.txt", "r");
    fp_w = fopen("!gitvim_result_list.txt", "w");
    fprintf(fp_w, "--------------------------------------------------------------\n");
    while(!feof(fp_r)){
        memset(buffer, 0, SIZE_OF_BUFFER);
        fscanf(fp_r, "%[^\n]s", buffer);
        fgetc(fp_r);

        string tempBuffer = buffer;
        if(tempBuffer.length()) fprintf(fp_w, "%s (%d)\n", buffer, ++cnt);
        if(cnt == 10) break;
    }
    fprintf(fp_w, "Enter file shortcut (shown on the right) or keyword to further refine the search:\n");
    fclose(fp_r);
    fclose(fp_w);

    int tflag = 0;
    while(!tflag){
        // CASE(1) : NO FILES
        if(cnt == 0){
            perror("there is no files with given string ");
            exit(1);
        }

        // CASE(2) : ONLY ONE FILE; open with vim
        else if(cnt == 1){
            fp_r = fopen("!gitvim_file_list.txt", "r");

            memset(buffer, 0, SIZE_OF_BUFFER);
            fscanf(fp_r, "%[^\n]s", buffer);
            fgetc(fp_r);

            tempStr = buffer;
            tempStr = "vim " + tempStr;
            sys_result = system(tempStr.c_str());

            fclose(fp_r);
            tflag = 1;
        }

        // CASE(3) : MORE THAN ONE FILE; loop
        else{
            sys_result = system("cat !gitvim_result_list.txt");
            cin >> tempStr;

            // case : input is integer.
            if(tempStr == "1" || tempStr == "2" || tempStr == "3" || tempStr == "4" || tempStr == "5" ||
               tempStr == "6" || tempStr == "7" || tempStr == "8" || tempStr == "9" || tempStr == "10"){
                int num = 0;
                int flag = 0;
                fp_r = fopen("!gitvim_file_list.txt", "r");
                while(num < 10){
                    fscanf(fp_r, "%[^\n]s", buffer);
                    fgetc(fp_r);
                    num++;
                    if(to_string(num) == tempStr){
                        string tempCmd = buffer;
                        tempCmd = "vim " + tempCmd;
                        sys_result = system(tempCmd.c_str());
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0){
                    perror("sorry, wrong input ");
                    exit(1);
                }
                fclose(fp_r);
                tflag = 1;
            }

            // case : input is string.
            else{
                //sys_result = system("rm -f !gitvim_file_list.txt");
                //sys_result = system("touch !gitvim_file_list.txt");
                sys_result = system("rm -f !gitvim_result_list.txt");
                sys_result = system("touch !gitvim_result_list.txt");

                sys_result = system("cp !gitvim_file_list.txt !gitvim_temp_list.txt");

                commandStr = "egrep \"/?[^/]*" + tempStr + defaultGrepString2 + " !gitvim_temp_list.txt";
                //string tempCmd = argv[1];
                //commandStr = "grep"
                tcommandStr = commandStr + " > !gitvim_file_list.txt";
                sys_result = system(tcommandStr.c_str());

                fp_r = fopen("!gitvim_file_list.txt", "r");
                fp_w = fopen("!gitvim_result_list.txt", "w");
                fprintf(fp_w, "--------------------------------------------------------------\n");

                cnt = 0;
                while(!feof(fp_r) && cnt < 10){
                    memset(buffer, 0, SIZE_OF_BUFFER);
                    fscanf(fp_r, "%[^\n]s", buffer);
                    fgetc(fp_r);
                    string tempBuffer = buffer;
                    if(tempBuffer.length()) fprintf(fp_w, "%s (%d)\n", buffer, ++cnt);
                }
                fprintf(fp_w, "Enter file shortcut (shown on the right) or keyword to further refine the search:\n");

                sys_result = system("rm -f !gitvim_temp_list.txt");

                fclose(fp_r);
                fclose(fp_w);
            }
        }
    }

    sys_result = system("rm -f !gitvim_file_list.txt");
    sys_result = system("rm -f !gitvim_result_list.txt");

    delete[] buffer;
    return 0;
}
