#include <iostream>
#include <ctime>
using namespace std;

int main(){
    int x = 1;

    if (time(nullptr) == 42)
        x = 42;

    if (x == 0)
        cout << "x is zero" << endl;

    else
        cout << "x is non-zero" << endl;

    return 0;
}
