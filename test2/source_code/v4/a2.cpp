#include <iostream>
#include "IPrintPlugin.h"

using namespace std;

const int FUNC_ID = 2;

class CPrintPlugin : public IPrintPlugin {
public:
  CPrintPlugin() {}
  virtual ~CPrintPlugin() {}
  virtual void Print() { 
    cout << "I Love coding" << endl; 
  }
  virtual void Help() { 
    cout << "Function ID " << FUNC_ID << endl; 
    cout << "The function will print \"I love coding\"." << endl; 
  }
  virtual int GetID(void) { 
    return FUNC_ID; 
  }
};

extern "C" void CreateObj(IPrintPlugin **ppPlugin) {
  static CPrintPlugin plugin;
  *ppPlugin = &plugin;
}