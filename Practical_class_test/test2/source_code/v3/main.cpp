#include <iostream>
#include "CPluginController.h"

using namespace std;


int main (int argc, char *argv[]) {
    if (argc == 1) {
        cout << "request error" << endl;
    } else if (argc == 2){  // 参数判断
        if (strcmp(argv[1], "help") == 0) { // 如果为help
            CPluginController pc;
            pc.ProcessHelp();
            return 0;
        } else {	// 如果为插件id
            cout << 1 << endl;
            CPluginController pc;
            pc.InializeController();	// 初始化注册列表
            int id = atoi(argv[1]);
            pc.ProcessRequest(id);
            pc.UninializeController();
            return 0;
        } 
    } else {
        cout << "faild input, please input the correct syntax [execfile] [command]" << endl;
    }
    return 0;
}
