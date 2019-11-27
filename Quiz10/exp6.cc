#include <iostream>
#include <string.h>
using namespace std;

int main(){
    char *greeting = new char[1024];
    strcpy(greeting, "Dear");
    cout << greeting << " Sir/Madam" << endl;
    delete[] greeting;
    return 0;
}
