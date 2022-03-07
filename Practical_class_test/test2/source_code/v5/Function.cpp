#include <iostream>
#include <sys/stat.h>
#include "IPrintPlugin.h"

using namespace std;

typedef long long ll;

const int FUNC_ID = 1;

class IPrintPlugin;

class CPrintPlugin : public IPrintPlugin {
public:
  CPrintPlugin() {}
  virtual ~CPrintPlugin() {}
  virtual void Print() { 
    cout << "FileSystem" << endl; 
  }
  // 获取插件帮助信息
  virtual void Help() { 
    cout << "Function ID " << FUNC_ID << " : This function will manage File" << endl; 
  }
  
  // 获取插件ID号
  virtual int GetID(void) { 
    return FUNC_ID; 
  }

  // 获取文件
  bool GetFile() {
    DIR *dir = opendir(path.c_str());
    if (dir == 0)
      return false;
    for (;;) {
      struct dirent *pentry = readdir(dir);
      if (pentry == 0)
        break;
      if (strcmp(pentry->d_name, ".") == 0)
        continue;
      if (strcmp(pentry->d_name, "..") == 0)
        continue;
      vstrPluginNames.push_back(pentry->d_name);
    }
    return true;
  }
	
	
  // 显示目录文件信息
  bool show_file_info() {
    int cnt = 0;
    for (auto s : vstrPluginNames) {
      cout << ++cnt << ". " << s << endl;
    }
    return true;
  }
   
   // 展示用户操作菜单
  void user_menu() {
    cout << "Please input the choice you want to manage the fileSystem" << endl;
    cout << "------------1. GetLineNum------------------------" << endl;
    cout << "------------2. GetCharNum------------------------" << endl;
    cout << "------------3. GetFileSize------------------------" << endl;
    cout << "------------0. exit -----------------------------" << endl;
    return;
  }
	
	
  // 用户交互操作接口
  virtual void user_mange() {
    if (!GetFile()) {
      cout << "The Direcotry is empty" << endl;
      return;
    }
    while (true) {
      user_menu();
      string choice, filename;
      cin >> choice;
      if (choice == "0") {
        break;
      }
      cout << "Please input the file you want to mange" << endl;
      show_file_info();
      cin >> filename;
      if (choice == "1") {
        GetLineNum(filename);
      } else if (choice == "2") {
        GetCharNum(filename);
      } else {
        GetFileSize(filename);
      }
    }
    return;
  }
  
  // 封装打开文件操作，使得维护更加便捷
  fstream open_file(string filename) {
    return fstream(path + filename, ios::in);
  }
  
  // 获取文件行数
  void GetLineNum(string filename) {
    fstream ReadFile = open_file(filename);
    ll cnt = 0;
    if(ReadFile.fail()) {
      cout << "open file error" << endl;
    } else {
        while(getline(ReadFile, tmp, '\n')) {
            cnt++;
        }
        cout << "The  " << filename << " LineNum is : " << cnt << endl;
        ReadFile.close();
    }
    return;
  }
  // 获取文件字符数
  void GetCharNum(string filename) {
    fstream ReadFile = open_file(filename);
    ll cnt = 0;
    if(ReadFile.fail()) {
      cout << "open file error" << endl;
    } else {
        while(getline(ReadFile, tmp, '\n')) {
            cnt += tmp.size();
        }
        cout << "The" << filename << " CharNum is : " << cnt << endl;
        ReadFile.close();
    }
    return;
  }

  // 获取文件大小
  void GetFileSize(string filename) {
    struct stat statbuf;
    cout << filename << endl;
    // 获取文件信息失败
    if (stat((path + filename).c_str(), &statbuf) == -1) {
      cout << "The file path is uncorrect, please check and retry" << endl;
      return;
    }
    // 打印文件字节数
    cout << "The File Size is ：" << statbuf.st_size << " bytes" << endl;
    return;
  }

private:
  string tmp;
  string path = "./data/";
  vector<string> vstrPluginNames;
};

extern "C" void CreateObj(IPrintPlugin **ppPlugin) {
  static CPrintPlugin plugin;
  *ppPlugin = &plugin;
}
