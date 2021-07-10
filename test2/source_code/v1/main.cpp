#include <iostream>
#include <dlfcn.h>


using namespace std;


int main () {
    void *handle = dlopen("./libtest.so", RTLD_LAZY);

    if (handle == 0) {
        cout << "open handle faild" << endl;
        return 0;
    }


    typedef void (*Fun)();
    
    Fun p = (Fun) dlsym(handle, "f");

    if (p == 0) {
        dlerror();
        cout << "open dll file faild" << endl;
        return 0;
    }

    (*p)();

    return 0;
}
