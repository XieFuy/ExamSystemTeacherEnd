#include "mainmenuemodel.h"

CMainMenueModel::CMainMenueModel()
{

}

CMainMenueModel::~CMainMenueModel()
{

}

bool CMainMenueModel::addShortAnswerInfo(double grade,const char* question,
                                         const char* referenceAnswer,int order)
{
    if(question == nullptr || referenceAnswer == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = CDBHelper::getInstance();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"insert into  `shortAnswer` (`grade`,`question`,`referenceAnswer`,`order`)\
 values(%lf,'%s','%s',%d);",grade,question,referenceAnswer,order);
 std::string sql = sqlBuf;
   return  dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::addJudgeInfo(double grade,const char* question,const char* sessionTrue,
                  const char* sessionFalse,
                  const char* correctAnswer,int order)
{
    if(question==nullptr || sessionFalse == nullptr
      ||sessionTrue == nullptr || correctAnswer == nullptr )
    {
        return false;
    }
    CDBHelper* dbHelper = CDBHelper::getInstance();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"insert into  `judge` (`grade`,`question`,`sessionTrue`,`sessionFalse`,`order`,`correctAnswer`)\
values(%lf,'%s','%s','%s',%d,'%s');",grade,question,sessionTrue,sessionFalse,order,correctAnswer);
 std::string sql = sqlBuf;
   return  dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::addMultiChoiceInfo(double grade,const char* question,const char* sessionA,
                        const char* sessionB,const char* sessionC,const char* sessionD,
                        const char* sessionE,const char* sessionF,const char* correctOpetions,
                        int order)
{
    if(question == nullptr || sessionA == nullptr||
       sessionB == nullptr || sessionC == nullptr||
       sessionD == nullptr || sessionE == nullptr||
       sessionF == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = CDBHelper::getInstance();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"insert into  `multiChoice` (`grade`,`question`,`sessionA`,`sessionB`,\
`sessionC`,`sessionD`,`sessionE`,`sessionF`,`correctOptions`,`order`)\
 values(%lf,'%s','%s','%s','%s','%s','%s','%s','%s',%d);",grade,question,sessionA,sessionB,
    sessionC,sessionD,
    sessionE,sessionF,correctOpetions,order);
 std::string sql = sqlBuf;
   return  dbHelper->sqlExcute(sql,"ExamSystem");
}

void CMainMenueModel::changeHeadPicture(char* localFilePath ,char* fileName,char* acount)
{
    if(localFilePath == nullptr || fileName == nullptr || acount == nullptr)
    {
        return ;
    }
    //先进行网络通信，将头像上传到服务器磁盘保存
    FILE* pFile = fopen(localFilePath,"rb+");
    if(pFile == nullptr)
    {
        fclose(pFile);
        return;
    }

    fseek(pFile,0,SEEK_END);
    long long fileSize =  _ftelli64(pFile);
    fseek(pFile,0,SEEK_SET);

    std::string headPath = "/root/picture/";
    headPath += fileName;
    qDebug()<<headPath.size();
    char* data = new char[2 + fileSize + headPath.size()]; //全是文件数据
    memset(data,'\0',sizeof(char) * (2 + fileSize + headPath.size()));
    WORD pathLenght = headPath.size();
    memcpy(data,&pathLenght,sizeof(WORD));
    long long size =  fread(data + 2,1,fileSize,pFile);
    fclose(pFile);
    memcpy(data + fileSize + 2,headPath.c_str(),headPath.size());
    //进行封包操作
    CClientSocket* clientsocket = CClientSocket::getInstance();
    clientsocket->initSocket();
    bool ret =  clientsocket->connectToServer();
    if(!ret)
    {
        return;
    }
    clientsocket->makePacket(data,fileSize + headPath.size() + 2,1);
    char* packet =  clientsocket->getPacket();
    clientsocket->Send(packet);
    delete[] data;
    clientsocket->closeSocket();

    //对数据库进行操作,更该当前用户的头像的存储路径
    CDBHelper* dbHelper = CDBHelper::getInstance();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(sqlBuf));

    sprintf(sqlBuf,"update  `TeacherInfo` set `profilePicture` = '%s' where `teacherId` = '%s'; ",headPath.c_str(),acount);
    std::string sql = sqlBuf;
    dbHelper->sqlExcute(sql,"ExamSystem");
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

bool CMainMenueModel::initSingleChoiceTable()
{
    CDBHelper* dbHelper = CDBHelper::getInstance();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    sql= "create table  if not exists `singleChoice`(\
`id` integer primary key auto_increment,\
`grade` double default 0.0 not null,\
`question` varchar(1000)   not null default '',\
`sessionA` varchar(1000)  not null default '',\
`sessionB` varchar(1000)  not null default '',\
`sessionC` varchar(1000)  not null default '',\
`sessionD` varchar(1000) not null default '',\
`correctOptions` varchar(2) not null,\
`order` integer not null default  0, \
`testPaperId` integer not null default 0,\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`)\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   return  dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::initMultiChoiceTable()
{
    CDBHelper* dbHelper = CDBHelper::getInstance();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    sql= "create table  if not exists `multiChoice`(\
`id` integer primary key auto_increment,\
`grade` double default 0.0 not null,\
`question` varchar(1000)   not null default '',\
`sessionA` varchar(1000)  not null default '',\
`sessionB` varchar(1000)  not null default '',\
`sessionC` varchar(1000)  not null default '',\
`sessionD` varchar(1000) not null default '',\
`sessionE` varchar(1000) not null default '',\
`sessionF` varchar(1000) not null default '',\
`correctOptions` varchar(20) not null,\
`order` integer not null default  0, \
`testPaperId` integer not null default 0,\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`)\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   return  dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::initJudgeTable()
{
    CDBHelper* dbHelper = CDBHelper::getInstance();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    sql= "create table  if not exists `judge`(\
`id` integer primary key auto_increment,\
`grade` double default 0.0 not null,\
`question` varchar(1000)   not null default '',\
`sessionTrue` varchar(1000)  not null default '',\
`sessionFalse` varchar(1000)  not null default '',\
`correctAnswer` varchar(2) not null,\
`order` integer not null default  0, \
`testPaperId` integer not null default 0,\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`)\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   return  dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::initShortAnswerTable()
{
    CDBHelper* dbHelper = CDBHelper::getInstance();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    sql= "create table  if not exists `shortAnswer`(\
`id` integer primary key auto_increment,\
`grade` double default 0.0 not null,\
`question` varchar(1000)   not null default '',\
`referenceAnswer` varchar(2000) not null,\
`order` integer not null default  0,  \
`testPaperId` integer not null default 0,\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`)\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   return  dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::initTestPaperTable()
{
    CDBHelper* dbHelper = CDBHelper::getInstance();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    sql= "create table if not exists `testPaperInfo`(\
`testPaperId` integer primary key auto_increment,\
`testPaperName` varchar(100) not null ,\
`saveTime` datetime not null,\
`publishStatus` varchar(2) not null default '0',\
`teacherId` varchar(20)  not null,\
foreign key(`teacherId`) references `Teacher`(`teacherId`)\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   return  dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::addSignalChoiceInfo(double grade,const char* question,const char* sessionA,
                         const char* sessionB,const char* sessionC,const char* sessionD,
                         const char* correctOptions,int order)
{
    if(question == nullptr||question == nullptr || sessionA == nullptr||
            sessionB == nullptr || sessionC == nullptr
            ||sessionD == nullptr||correctOptions == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = CDBHelper::getInstance();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"insert into  `singleChoice` \
(`grade`,`question`,`sessionA`,`sessionB`,`sessionC`,`sessionD`,`correctOptions`,`order`)\
 values('%lf','%s','%s','%s','%s','%s','%s','%d');",grade,question,sessionA,
            sessionB,sessionC,sessionD,correctOptions,order);
 std::string sql = sqlBuf;
   return  dbHelper->sqlExcute(sql,"ExamSystem");
}
