#include "f1.h"

using namespace std;


extern "C" void print() {
    cout << "Hello World" << endl;
}

extern "C" void help() {
    cout << "The Func ID is " << FUNC_ID  << endl;
    cout << "The Func is print the hello World" << endl;
}

extern "C" int GetID() {
    return FUNC_ID;
}