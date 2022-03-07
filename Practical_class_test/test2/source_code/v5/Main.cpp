#include <iostream>
#include "CPluginController.h"
#include <string.h>
#include <stdlib.h>

using namespace std;
int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Parameters error" << endl;
    return 0;
  } else {
    if (strcmp(argv[1], "help") == 0) {
      CPluginController pc;
      pc.ProcessHelp();
    } else {
      CPluginController pc;
      pc.InitializeController();
      if (strcmp(argv[1], "menu") == 0) {
        pc.ProcessMange();
      } else {
        int FunctionID = atoi(argv[1]);
        pc.ProcessRequest(FunctionID);
      }
      pc.UninitializeController();
    }
  }
  return 0;
}