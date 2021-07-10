#include <iostream>


using namespace std;

extern "C" void f() {
    cout << "Hello China" << endl;
    return;
}
