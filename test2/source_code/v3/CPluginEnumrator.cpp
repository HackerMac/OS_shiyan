#include "CPluginEnumrator.h"

using namespace std;

CPluginEmulator::CPluginEmulator() {
	// 初始化文件插件路径
    filepath = "./plugin/";
}

CPluginEmulator::~CPluginEmulator() {

}

string CPluginEmulator::Get_Path() {
    return filepath;
}

vector<string> CPluginEmulator::Get_Plugin() {
    return m_set;
}

bool CPluginEmulator::GetPluginName() {
    DIR *dir = opendir(filepath.c_str());
   struct dirent *ptr;
   while ((ptr = readdir(dir)) != NULL) {
       string s;
       for (int i = 0; ptr->d_name[i]; ++i) {
           s.push_back(ptr->d_name[i]);
       }
    	// 跳过当前路径和父路径
       if (s == ".." || s == ".") {
           continue;
       }
       // 插件名列表添加当前插件
       m_set.push_back(s);
   }
    // 重置文件偏移
    rewinddir(dir);
    if (closedir(dir) == -1) {
        cout << "close dir faild" << endl;
        return false;
    } 
    return true;
}
