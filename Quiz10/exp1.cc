#include <iostream>
using namespace std;

int main(){
    char *x = new char[100];
    if (x == nullptr)
        cout << "error" << endl;
    delete[] x;
    return 0;
}
