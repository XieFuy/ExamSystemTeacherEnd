#include "mainmenuemodel.h"

CMainMenueModel::CMainMenueModel()
{

}

CMainMenueModel::~CMainMenueModel()
{

}

void CMainMenueModel::changeGender(bool isMan,char* pAcount)
{
    std::string gender;
    if(isMan)
    {
        gender = "1";
    }else
    {
        gender = "0";
    }
    CDBHelper* dbHelper = CDBHelper::getInstance();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"update  `TeacherInfo` set `gender` = '%s' where `teacherId` = '%s'; ",gender.c_str(),pAcount);
    std::string sql  = sqlBuf;
    dbHelper->sqlExcute(sql,"ExamSystem");
}

std::vector<std::vector<std::string>> CMainMenueModel::showTeacherAcountInfo(char* pAcount)
{
    if(pAcount == nullptr)
    {
        return std::vector<std::vector<std::string>>(); //返回一个空结果集
    }
    CDBHelper* dbHelper = CDBHelper::getInstance();
    std::string sql;
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"select `name`,`teacherId`,`gender`,`phoneNumber` from `TeacherInfo` where `teacherId` = '%s';",pAcount);
    sql = sqlBuf;
    return  dbHelper->sqlQuery(sql,"ExamSystem");
}

//显示主页头像和姓名
std::vector<std::vector<std::string>> CMainMenueModel::showTeacherInfo(char* pAcount)
{
    if(pAcount == nullptr)
    {
        return std::vector<std::vector<std::string>>(); //返回一个空结果集
    }
    //进行查询显示 姓名和头像
    CDBHelper* dbHelper = CDBHelper::getInstance();
    std::string sql;
    char sqlBuf[1024];
    memset(sqlBuf,0,sizeof(char)*1024);
    sprintf(sqlBuf,"select `name`,`profilePicture` from `TeacherInfo` where `teacherId` = '%s';",pAcount);
    sql = sqlBuf;
    return  dbHelper->sqlQuery(sql,"ExamSystem");
}

//进行建表操作
bool CMainMenueModel::initTeacherInfoTable()
{
    CDBHelper* dbHelper = CDBHelper::getInstance();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    sql= "create table if not exists `TeacherInfo`\
(\
`id` integer primary key auto_increment,\
`teacherId` varchar(20)  not null,\
foreign key(`teacherId`) references `Teacher`(`teacherId`),\
`name` varchar(10) not null default '未设置',\
`gender`  varchar(2) not null  default '1',\
`phoneNumber` varchar(20) not null default '未设置',\
`profilePicture` varchar(100) not null default '/root/picture/defaultHead.png')\
ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   return  dbHelper->sqlExcute(sql,"ExamSystem");
}
