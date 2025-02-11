#ifndef DPIHELPER_H
#define DPIHELPER_H

#include<windows.h>
#include<shellapi.h>
#include<QMessageBox>
#include<QDebug>

class DpiHelper
{
public:
    DpiHelper();
    ~DpiHelper();
  int localScaling;
  //获取管理员权限
  bool  isRunningAsAdmin();
  bool requestAdminRights();
  //获取当前dpi
  int GetCurrentScalingPercentage();
  //进行设置dpi
  bool SetScalingPercentage(int scalingPercentage);
};
#endif // DPIHELPER_H
