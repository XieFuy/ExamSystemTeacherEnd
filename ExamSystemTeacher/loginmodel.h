#ifndef CLOGINMODEL_H
#define CLOGINMODEL_H
#include <QString>
#include "clientsocket.h"
#include "DBHelper.h"
#include <string>
class CLoginModel //登录模型层
{
public:
    CLoginModel();
    ~CLoginModel();
     bool login(char* acount,char* password,int acountSize,int passwordSize);
     void initTeacherDatabase();
     void initTeacherTable();
private:
};

#endif // CLOGINMODEL_H
