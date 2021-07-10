#include <iostream>
#include <vector>
#include <dlfcn.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <string.h>

using namespace std;

class CPluginEmulator {

public:
    CPluginEmulator();
    virtual ~CPluginEmulator();
    bool GetPluginName(void);
    vector<string> Get_Plugin();
    string Get_Path();
private:
    vector<string> m_set;
    string filepath;
};