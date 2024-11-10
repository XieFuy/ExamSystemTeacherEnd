#include "registercontorller.h"

CRegisterContorller::CRegisterContorller()
{
   this->m_registerModel = new CRegisterModel();
}

CRegisterContorller::~CRegisterContorller()
{
    if(this->m_registerModel != nullptr)
    {
        delete this->m_registerModel;
        this->m_registerModel = nullptr;
    }
}

int CRegisterContorller::registerTeacherInfo(QString acount,QString password)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray passwordArr = password.toUtf8();
    const char* pAcount = acountArr.data();
    const char* pPassword = passwordArr.data();
    //调用模型层
    return  this->m_registerModel->registerTeacherInfo(const_cast<char*>(pAcount) ,const_cast<char*>(pPassword));
}
