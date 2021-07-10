#include "CPluginController.h"
#include "CPluginEnumerator.h"
#include "IPrintPlugin.h"
#include "dlfcn.h"
#include <iostream>

using namespace std;


CPluginController::CPluginController(void) {}

CPluginController::~CPluginController(void) {}

bool CPluginController::ProcessHelp(void) {
  vector<string> vstrPluginNames;
  CPluginEnumerator enumerator;
  if (!enumerator.GetPluginNames(vstrPluginNames))
    return false;
  for (unsigned int i = 0; i < vstrPluginNames.size(); i++) {
    typedef int (*PLUGIN_CREATE)(IPrintPlugin **);
    PLUGIN_CREATE CreateProc;
    IPrintPlugin *pPlugin = NULL;
    void *hinstLib = dlopen(vstrPluginNames[i].c_str(), RTLD_LAZY);
    if (hinstLib != NULL) {
      CreateProc = (PLUGIN_CREATE)dlsym(hinstLib, "CreateObj");
      if (NULL != CreateProc) {
        (CreateProc)(&pPlugin);
        if (pPlugin != NULL) {
          pPlugin->Help();
        }
      }

      dlclose(hinstLib);
    }
  }
  return true;
}


bool CPluginController::ProcessRequest(int FunctionID) {
  for (unsigned int i = 0; i < m_vpPlugin.size(); i++) {
    if (m_vpPlugin[i]->GetID() == FunctionID) {
      m_vpPlugin[i]->Print();
      break;
    }
  }
  return true;
}

bool CPluginController::InitializeController(void) {
  vector<string> vstrPluginNames;
  CPluginEnumerator enumerator;
  if (!enumerator.GetPluginNames(vstrPluginNames))
    return false;
  for (unsigned int i = 0; i < vstrPluginNames.size(); i++) {
    typedef int (*PLUGIN_CREATE)(IPrintPlugin **);
    PLUGIN_CREATE CreateProc;
    IPrintPlugin *pPlugin = NULL;
    void *hinstLib = dlopen(vstrPluginNames[i].c_str(), RTLD_LAZY);
    if (hinstLib == NULL) {
      cout << dlerror() << endl;
      continue;
    }
    if (hinstLib != NULL) {
      m_vhForPlugin.push_back(hinstLib);
      CreateProc = (PLUGIN_CREATE)dlsym(hinstLib, "CreateObj");
      if (NULL != CreateProc) {
        (CreateProc)(&pPlugin);
        if (pPlugin != NULL) {
          m_vpPlugin.push_back(pPlugin);
        }
      }
    }
  }
  return true;
}

bool CPluginController::UninitializeController() {
  for (unsigned int i = 0; i < m_vhForPlugin.size(); i++) {
    dlclose(m_vhForPlugin[i]);
  }
  return true;
}