#pragma once
#include <dirent.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>

using namespace std;

class IPrintPlugin {
public:
  IPrintPlugin();
  virtual ~IPrintPlugin();
  virtual void Help() = 0;
  virtual void Print() = 0;
  virtual int GetID() = 0;
  virtual void user_mange() = 0;
};