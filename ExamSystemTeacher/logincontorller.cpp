#include "logincontorller.h"

CLoginContorller::CLoginContorller()
{
  this->m_loginModel = new CLoginModel();
}

CLoginContorller::~CLoginContorller()
{
  if(this->m_loginModel != nullptr)
  {
      delete this->m_loginModel;
      this->m_loginModel = nullptr;
  }
}

bool CLoginContorller::login(QString acount,QString password)
{
    if(acount == "" || password == "")
    {
        return false;
    }
    QByteArray acountArr = acount.toUtf8();
    QByteArray passwordArr = password.toUtf8();
    const char* pAcount = acountArr.data();
    const char* pPassword = passwordArr.data();
    return this->m_loginModel->login(const_cast<char*>(pAcount),
                                     const_cast<char*>(pPassword),
                                     acountArr.size(),passwordArr.size());
}

void CLoginContorller::initTeacherDatabase()
{
    this->m_loginModel->initTeacherDatabase();
}

void CLoginContorller::initTeacherTable()
{
    this->m_loginModel->initTeacherTable();
}
