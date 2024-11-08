#ifndef CLOGINCONTORLLER_H
#define CLOGINCONTORLLER_H
#include <QString>
#include "loginmodel.h"

class CLoginContorller //登录界面的控制层
{
public:
    CLoginContorller();
    ~CLoginContorller();
    bool login(QString acount,QString password);
    void initTeacherDatabase(); //初始化教师数据库
    void initTeacherTable();//初始化教师表
private:
    CLoginModel* m_loginModel = nullptr;
};

#endif // CLOGINCONTORLLER_H
