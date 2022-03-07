#include <iostream>
#include <vector>
#include <dlfcn.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <string.h>

using namespace std;

typedef void (*PROC_PRINT)(void);
typedef void (*PROC_HELP)(void);
typedef int (*PROC_GETID)(void);

class CPluginController {
public:
    CPluginController();
    virtual ~CPluginController();

    bool InializeController(void);
    bool UninializeController(void);

    bool ProcessRequest(int FunctionID);
    bool ProcessHelp(void);

private:
    vector<void*> m_vhForPligin;
    vector<PROC_PRINT> m_vPrintFunc;
    vector<PROC_GETID> m_vGetIDFunc;
};