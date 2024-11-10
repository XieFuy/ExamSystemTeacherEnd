#include "registermodel.h"

CRegisterModel::CRegisterModel()
{

}

void CRegisterModel::registerTeacherInfo(char* pAcount,char* pPassword)
{
    if(pAcount == nullptr || pPassword == nullptr)
    {
        return ;
    }
    CDBHelper* dbHelper = CDBHelper::getInstance();
    std::string sql;
    char buf[1024];
    memset(buf,'\0',sizeof(char) * 1024);
    sprintf(buf,"insert into `Teacher`(`teacherId`,`password`,`role`) values('%s','%s','teacher');",pAcount,pPassword);
    sql = buf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    return;
}

CRegisterModel::~CRegisterModel()
{

}
