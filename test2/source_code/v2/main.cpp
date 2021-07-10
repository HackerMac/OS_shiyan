#include <iostream>
#include <dlfcn.h>
#include <string>
#include <vector>
#include <dirent.h>

using namespace std;


string filepath = "./plugin/";

int main () {
   vector<string> filename;
   DIR *dir;
   struct dirent *ptr;
   dir = opendir(filepath.c_str());
   while ((ptr = readdir(dir)) != NULL) {
       string s;
       for (int i = 0; ptr->d_name[i]; ++i) {
           s.push_back(ptr->d_name[i]);
       }

       if (s == ".." || s == ".") {
           continue;
       }
       filename.push_back(s);
   }

    rewinddir(dir);
    if (closedir(dir) == -1) {
        cout << "close dir faild" << endl;
        return 0;
    } 

    for (auto &file : filename) {
        cout << (filepath + file).c_str() << endl;
        void *handle = dlopen((filepath + file).c_str(), RTLD_LAZY);
        
        if (handle == 0) {
            cout << "open handle faild" << endl;
            return 0;
        }

        typedef void (*Fun)();
        
        Fun p = (Fun) dlsym(handle, "f");

        if (p == 0) {
            dlerror();
            cout << "open dll file faild" << endl;
            continue;
        }

        (*p)();
        if (dlclose(handle) == -1) {
            cout << "close handle faild" << endl;
            return 0;
        }
    }    
    
    return 0;
}
