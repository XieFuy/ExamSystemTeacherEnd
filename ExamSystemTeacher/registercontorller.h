#ifndef CREGISTERCONTORLLER_H
#define CREGISTERCONTORLLER_H
#include "registermodel.h"
#include<QString>
#include<QByteArray>

class CRegisterContorller //注册控制层
{
public:
    CRegisterContorller();
    ~CRegisterContorller();
    void registerTeacherInfo(QString acount,QString password);//注册教师信息
private:
    CRegisterModel* m_registerModel = nullptr;
};

#endif // CREGISTERCONTORLLER_H
