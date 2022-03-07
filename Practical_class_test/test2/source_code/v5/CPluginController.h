#ifndef CPLUGINCONTROLLER_H
#define CPLUGINCONTROLLER_H
#include <vector>
#include <iostream>

using namespace std;

class IPrintPlugin;

class CPluginController {
public:
  CPluginController(void);

  virtual ~CPluginController(void);
  bool InitializeController(void);
  bool UninitializeController(void);
  bool ProcessHelp(void);
  bool ProcessRequest(int FunctionID);
  bool ProcessMange(void);

private:
  vector<void *> m_vhForPlugin;
  vector<IPrintPlugin *> m_vpPlugin;
};

#endif