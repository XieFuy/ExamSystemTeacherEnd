#include "mainmenuemodel.h"

CMainMenueModel::CMainMenueModel()
{

}

CMainMenueModel::~CMainMenueModel()
{

}

//显示
std::vector<std::vector<std::string>> CMainMenueModel::showTeacherInfo()
{
    //进行查询显示 姓名和头像
    CDBHelper* dbHelper = CDBHelper::getInstance();
    std::string sql;

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
`profilePicture` MEDIUMBLOB default NULL)\
ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   return  dbHelper->sqlExcute(sql,"ExamSystem");
}
