#include "registermodel.h"

CRegisterModel::CRegisterModel()
{

}

int CRegisterModel::registerTeacherInfo(char* pAcount,char* pPassword)
{
    if(pAcount == nullptr || pPassword == nullptr)
    {
        return -1;
    }
    CDBHelper* dbHelper = CDBHelper::getInstance();
    std::string sql;
    char buf[1024];
    memset(buf,'\0',sizeof(char) * 1024);
    //先检查是否存在相同的教职工号，存在提示账号已存在
    sprintf(buf,"select count(*) from `Teacher` where teacherId = '%s';",pAcount);
    sql = buf;
    int count =  dbHelper->sqlQueryCount(sql,"ExamSystem");
    if(count >= 1)
    {
        //返回结果进行提示账号已存在
        return 1;
    }
    memset(buf,'\0',sizeof(char) * 1024);
    sprintf(buf,"insert into `Teacher`(`teacherId`,`password`,`role`) values('%s','%s','teacher');",pAcount,pPassword);
    sql = buf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    return 0;
}

CRegisterModel::~CRegisterModel()
{

}
