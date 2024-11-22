#include "loginmodel.h"

CLoginModel::CLoginModel(){}

CLoginModel::~CLoginModel(){}

//进行登录等数据库操作部分不一定需要网络模块进行操作
bool CLoginModel::login(char* acount,char* password,int acountSize,int passwordSize)
{
    if(acount == nullptr || password == nullptr)
    {
        return  false;
    }
/*
 *
 *
    //将账号和密码发送到给服务端进行接收，然后处理任务，等待服务端返回的结果
    CClientSocket* clientSocket = CClientSocket::getInstance();
    clientSocket->initSocket();
    bool ret =  clientSocket->connectToServer();
    if(!ret)
    {
        return false;
    }
    //进行封包操作
    char dou = ','; //分隔符
    const char* user = "teacher";//用户角色类型
    char* data = new char[1024];
    memcpy(data,acount,acountSize);
    memcpy(data + acountSize,&dou,1);
    memcpy(data + acountSize + 1,password,passwordSize);
    memcpy(data + acountSize + 1 + passwordSize,&dou,1);
    memcpy(data + acountSize + 1 + passwordSize + 1,user,strlen(user));
    clientSocket->makePacket(data,strlen(data),userOpeator::LOGIN);
    delete[] data;
    //发送数据包
    char* packet = clientSocket->getPacket();
    long long packetSize = clientSocket->getPacketSize();
    clientSocket->Send(packet);
    char* recvBuffer = new char[packetSize]; //服务器返回也是一个包的大小
    clientSocket->Recv(recvBuffer); //接收服务器返回的结果
    bool result = false;
    //进行解包，拿到结果后进行返回

    delete recvBuffer;
    return result;
*/
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    char buffer[1024];
    memset(buffer,'\0',sizeof(buffer));
    sprintf(buffer,"select count(*) from `Teacher` where teacherId = '%s' and password = '%s';",acount,password);
    sql = buffer;
    int ret =  dbHelper->sqlQueryCount(sql,"ExamSystem");
    bool result = false;
    if(ret == 1)
    {
        result = true;
    }else
    {
        result = false;
    }
    delete dbHelper;
    return result;
}

void CLoginModel::initTeacherDatabase()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql =  "create database if not exists `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    delete dbHelper;
}

void CLoginModel::initTeacherTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql = "use `ExamSystem`;";
    bool ret =  dbHelper->sqlExcute(sql);
    sql = "create table if not exists `Teacher`(\
`teacherId` varchar(20) primary key,\
`password` varchar(20) not null,\
`role` varchar(10) not null default 'teacher')\
ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   ret = dbHelper->sqlExcute(sql,"ExamSystem");
   delete dbHelper;
}
