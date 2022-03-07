#include <iostream>

using namespace std;

extern "C" void f() {
    cout << "Hello World" << endl;
    return;
}



