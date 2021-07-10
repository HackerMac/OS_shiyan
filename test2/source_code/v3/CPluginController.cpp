#include "CPluginController.h"
#include "CPluginEnumrator.h"


using namespace std;

CPluginController::CPluginController() {}
CPluginController::~CPluginController() {}

bool CPluginController::ProcessHelp(void) {
    vector<string> vstrPluginName;
    CPluginEmulator c;
    c.GetPluginName();
    vstrPluginName = c.Get_Plugin();
    for (auto plugin : vstrPluginName) {
        cout << (c.Get_Path() + plugin).c_str() << endl;
        void *handle = dlopen((c.Get_Path() + plugin).c_str(), RTLD_LAZY);
        // 如果打开文件句柄失败
        if (handle == 0) {
            cout << "open handle faild" << endl;
            return 0;
        }
	// 自定义函数名
        typedef void (*Fun)();
	// 获得函数名为“help”的函数地址
        Fun p = (Fun) dlsym(handle, "help");
	// 获取失败
        if (p == 0) {
            dlerror();
            cout << "open dll file faild" << endl;
            return 0;
        }
        // 获取成功，执行函数
        (p)();
        // 关闭当前文件句柄
        if (dlclose(handle) == -1) {
            cout << "close handle faild" << endl;
            return 0;
        }
    }
}

bool CPluginController::ProcessRequest(int FunctionID) {
    for (int i = 0; i < m_vPrintFunc.size(); ++i) {
    	// 获取当其那ID是否和想要获取的ID一样，一样则向列表添加
        if ((int)m_vGetIDFunc[i]() == FunctionID) {
            m_vPrintFunc[i]();
        }
    }
    return true;
}

bool CPluginController::InializeController(void) {
    vector<string> vstrPluginName;
    CPluginEmulator c;
    // 初始化插件名列表
    c.GetPluginName();
    // 遍历插件名列表
    for (auto plugin : c.Get_Plugin()) {
    	// 通过文件名调用dlopen获得文件句柄
        void *handle = dlopen((c.Get_Path() + plugin).c_str(), RTLD_LAZY);
        
        if (handle == 0) {
            cout << "open handle faild" << endl;
            return 0;
        }
        
	// 通过句柄，获取指定函数链接
        PROC_PRINT p = (PROC_PRINT) dlsym(handle, "print");
        PROC_GETID h = (PROC_GETID) dlsym(handle, "GetID");
	// 如果这两个函数都获取成功，则向列表添加元素
        if (p != 0 && h != 0) {
            m_vhForPligin.push_back(handle);
            m_vPrintFunc.push_back(p);
            m_vGetIDFunc.push_back(h);
        }

    }
    return true;
}

bool CPluginController::UninializeController(void) {
	// 遍历逐一关闭已经打开的文件句柄
    for (int i = 0; i < m_vGetIDFunc.size(); ++i) {
        dlclose((void*)m_vhForPligin[i]);
    } 
    return true;
}
