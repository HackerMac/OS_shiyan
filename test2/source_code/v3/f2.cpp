#include "f2.h"

using namespace std;

extern "C" void print() {
    cout << "Good Job" << endl;
}

extern "C" void help() {
    cout << "The Func ID is " << FUNC_ID << endl;
    cout << "The Func is print the Good Job" << endl;
}

extern "C" int GetID() {
    return FUNC_ID;
}