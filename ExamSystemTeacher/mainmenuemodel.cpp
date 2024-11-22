#include "mainmenuemodel.h"

CMainMenueModel::CMainMenueModel()
{
 this->m_mutex = CreateMutex(nullptr,FALSE,nullptr);
}

CMainMenueModel::~CMainMenueModel()
{

}

std::vector<std::vector<std::string>> CMainMenueModel::showCurPageIndexTable(int curPageIndex,char* acount)
{
    if(curPageIndex == 0 || acount == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    // 返回的数据集是一个表
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    std::string sql;
    //拿到试卷表的全部 试卷名称，创建时间，发布状态
    sprintf(sqlBuf,"select `testPaperName`,`saveTime`,`publishStatus` from `testPaperInfo`\
 where `teacherId` = '%s' order by `testPaperId` limit 8 offset %d;",acount,((curPageIndex -1) * 8));
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret = dbHelper->sqlQuery(sql,"ExamSystem");

    //拿到每一份试卷的题量和出题人

    //获取所有符合条件的记录的出题量
    //1、拿到所有属于这个用户的所有的试卷id
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"select `testPaperId` from `testPaperInfo` where `teacherId` = '%s' limit 8 offset %d;",acount,((curPageIndex -1) * 8));
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret2 = dbHelper->sqlQuery(sql,"ExamSystem");

    //2、根据每一个试卷id进行查询所有的类型的题库的试题总数，并且求和，放入容器中
    std::vector<std::vector<std::string>> ret3;
    for(int i = 0 ; i < ret2.size();i++) //忽略第一个 id为0 的
    {

        //查询单选题总数
        memset(sqlBuf,'\0',sizeof(char) * 1024);
        sprintf(sqlBuf,"select count(*) from `singleChoice` where `testPaperId` = %s;",ret2.at(i).at(0).c_str());
        sql = sqlBuf;
        int count1 =  dbHelper->sqlQueryCount(sql,"ExamSystem");

        //查询多选题总数
        memset(sqlBuf,'\0',sizeof(char) * 1024);
        sprintf(sqlBuf,"select count(*) from `multiChoice` where `testPaperId` = %s;",ret2.at(i).at(0).c_str());
        sql = sqlBuf;
        int count2 =  dbHelper->sqlQueryCount(sql,"ExamSystem");

        //查询判断题总数
        memset(sqlBuf,'\0',sizeof(char) * 1024);
        sprintf(sqlBuf,"select count(*) from `judge` where `testPaperId` = %s;",ret2.at(i).at(0).c_str());
        sql = sqlBuf;
        int count3 =  dbHelper->sqlQueryCount(sql,"ExamSystem");

        //查询简答题总数
        memset(sqlBuf,'\0',sizeof(char) * 1024);
        sprintf(sqlBuf,"select count(*) from `shortAnswer` where `testPaperId` = %s;",ret2.at(i).at(0).c_str());
        sql = sqlBuf;
        int count4 =  dbHelper->sqlQueryCount(sql,"ExamSystem");

        int allCount = count1 + count2 + count3 + count4;
        char buf[200];
        memset(buf,'\0',sizeof(char) * 200);
        itoa(allCount,buf,10);
        std::vector<std::string> temp;
        temp.push_back(buf);
        ret3.push_back(std::move(temp));
    }

    //获取每一份试卷，根据试卷的职工id进行查询职工姓名
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"select `name` from `TeacherInfo` where `teacherId` = '%s';",acount);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> name =  dbHelper->sqlQuery(sql,"ExamSystem");

    //进行重组，组成记录表，进行返回
    std::vector<std::vector<std::string>> result;
    qDebug()<<"ret.size: "<<ret.size()<<"ret2.size:"<<ret2.size()<<"ret3.size: "<<ret3.size();
    for(int i = 0 ; i < ret.size() ; i++) // 7列 8行
    {
          std::vector<std::string> temp;
          //插入试卷名称
          temp.push_back(ret.at(i).at(0));

          //插入题量
          temp.push_back(ret3.at(i).at(0));

          //插入创建时间
          temp.push_back(ret.at(i).at(1));

          //插入出卷人
          temp.push_back(name.at(0).at(0));

          QString strTemp;
          //插入发布状态
          if(ret.at(i).at(2) == "0")
          {
              strTemp = "未发布";
              QByteArray tempArr = strTemp.toLocal8Bit();
              temp.push_back(tempArr.data());
          }else if(ret.at(i).at(2) == "1")
          {
              strTemp = "以发布";
              QByteArray tempArr = strTemp.toLocal8Bit();
              temp.push_back(tempArr.data());
          }
          result.push_back(std::move(temp));
    }
    /*测试打印结果的值*/
   /* qDebug()<<"测试循环进入";
    for(int i = 1 ; i < result.size();i++)
    {
        for(int j = 0; j < result.at(i).size();j++)
        {
            std::cout<<result.at(i).at(j).c_str()<<" ";
        }
        std::cout<<std::endl;
    }*/
    //拿到的存储结果不访问第一行，第一行是测试行
    delete dbHelper;
    return result;
}

QString CMainMenueModel::getTablePageCount(char* acount)
{
    if(acount == nullptr)
    {
        return "";
    }
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    std::string sql;
    sprintf(sqlBuf,"select count(*) from `testPaperInfo` where `teacherId` = '%s';",acount);
    sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    int result = (tableCount / 8) ;
    if(result <= 0) //表示总的记录条数小于8
    {
         result += 1;
    }else
    {
       int yuShu = tableCount - (result * 8);
        if(yuShu > 0)
        {
            result += 1;
        }
    }
    delete dbHelper;
    return QString::number(result);
}

bool CMainMenueModel::addShortAnswerInfo(double grade,const char* question,
                                         const char* referenceAnswer,int order)
{
    if(question == nullptr || referenceAnswer == nullptr)
    {
        return false;
    }
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"insert into  `shortAnswer` (`grade`,`question`,`referenceAnswer`,`order`)\
 values(%lf,'%s','%s',%d);",grade,question,referenceAnswer,order);
 std::string sql = sqlBuf;
   bool ret =   dbHelper->sqlExcute(sql,"ExamSystem");
   delete dbHelper;
   return ret;
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
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"insert into  `judge` (`grade`,`question`,`sessionTrue`,`sessionFalse`,`order`,`correctAnswer`)\
values(%lf,'%s','%s','%s',%d,'%s');",grade,question,sessionTrue,sessionFalse,order,correctAnswer);
 std::string sql = sqlBuf;
    bool ret =   dbHelper->sqlExcute(sql,"ExamSystem");
    delete dbHelper;
    return ret;
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
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"insert into  `multiChoice` (`grade`,`question`,`sessionA`,`sessionB`,\
`sessionC`,`sessionD`,`sessionE`,`sessionF`,`correctOptions`,`order`)\
 values(%lf,'%s','%s','%s','%s','%s','%s','%s','%s',%d);",grade,question,sessionA,sessionB,
    sessionC,sessionD,
    sessionE,sessionF,correctOpetions,order);
 std::string sql = sqlBuf;
 bool ret =   dbHelper->sqlExcute(sql,"ExamSystem");
 delete dbHelper;
 return ret;
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
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(sqlBuf));

    sprintf(sqlBuf,"update  `TeacherInfo` set `profilePicture` = '%s' where `teacherId` = '%s'; ",headPath.c_str(),acount);
    std::string sql = sqlBuf;
    bool ret2 =   dbHelper->sqlExcute(sql,"ExamSystem");
    delete dbHelper;
    return;
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
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"update  `TeacherInfo` set `gender` = '%s' where `teacherId` = '%s'; ",gender.c_str(),pAcount);
    std::string sql  = sqlBuf;
    bool ret =   dbHelper->sqlExcute(sql,"ExamSystem");
    delete dbHelper;
    return;
}

std::vector<std::vector<std::string>> CMainMenueModel::showTeacherAcountInfo(char* pAcount)
{
    if(pAcount == nullptr)
    {
        return std::vector<std::vector<std::string>>(); //返回一个空结果集
    }
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"select `name`,`teacherId`,`gender`,`phoneNumber` from `TeacherInfo` where `teacherId` = '%s';",pAcount);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete dbHelper;
    return ret;
}

//显示主页头像和姓名
std::vector<std::vector<std::string>> CMainMenueModel::showTeacherInfo(char* pAcount)
{
    if(pAcount == nullptr)
    {
        return std::vector<std::vector<std::string>>(); //返回一个空结果集
    }
    //进行查询显示 姓名和头像
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    char sqlBuf[1024];
    memset(sqlBuf,0,sizeof(char)*1024);
    sprintf(sqlBuf,"select `name`,`profilePicture` from `TeacherInfo` where `teacherId` = '%s';",pAcount);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete dbHelper;
    return ret;
}

//进行建表操作
bool CMainMenueModel::initTeacherInfoTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
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
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
   std::cout<<"initTeacherInfoTable task end"<<std::endl;
   delete dbHelper;
   return ret;
}

bool CMainMenueModel::initSingleChoiceTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    //std::cout<<"initSingleChoiceTable task1 end"<<std::endl;
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
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
   std::cout<<"initSingleChoiceTable task end"<<std::endl;
   delete dbHelper;
   return ret;
}

bool CMainMenueModel::initMultiChoiceTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
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
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
   delete dbHelper;
   std::cout<<"initMultiChoiceTable task end"<<std::endl;
   return ret;
}

bool CMainMenueModel::initJudgeTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
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
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
   std::cout<<"initJudgeTable task end"<<std::endl;
   delete dbHelper;
   return ret;
}

bool CMainMenueModel::initShortAnswerTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
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
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
   std::cout<<"initShortAnswerTable task end"<<std::endl;
   delete dbHelper;
   return ret;
}

bool CMainMenueModel::initTestPaperTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
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
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
   std::cout<<"initTestPaperTable task end"<<std::endl;
   delete dbHelper;
   return ret;
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
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"insert into  `singleChoice` \
(`grade`,`question`,`sessionA`,`sessionB`,`sessionC`,`sessionD`,`correctOptions`,`order`)\
 values('%lf','%s','%s','%s','%s','%s','%s','%d');",grade,question,sessionA,
            sessionB,sessionC,sessionD,correctOptions,order);
 std::string sql = sqlBuf;
 bool ret =   dbHelper->sqlExcute(sql,"ExamSystem");
 delete dbHelper;
 return ret;
}
