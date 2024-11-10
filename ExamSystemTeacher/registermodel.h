#ifndef CREGISTERMODEL_H
#define CREGISTERMODEL_H
#include"DBHelper.h"
#include<string>
class CRegisterModel //注册模型层
{
public:
    CRegisterModel();
    ~CRegisterModel();
public:
  int registerTeacherInfo(char* pAcount,char* pPassword);
private:
};

#endif // CREGISTERMODEL_H
