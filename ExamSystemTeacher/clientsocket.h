#ifndef CCLIENTSOCKET_H
#define CCLIENTSOCKET_H
#include <winsock2.h>
#include <QDebug>
enum userOpeator //用户操作的命令类型
{
    LOGIN //用户登录
};

//将客户端的网络模块进行修改为不是单例模式，用于多线程的并发量提升效率

class CClientSocket //套接字类，网络通信的主要负责类，这里采用饿汉式单例设计模式
{
public:
//    static CClientSocket* getInstance();
public:
    void initSocket(); //初始化套接字
    bool connectToServer();//连接服务器
    int Send(char* pData); //向服务器发送数据 ,每次发送一个数据包大小的数据
    int Recv(char* buffer);//接收服务器发送的数据,每次接收一个数据包大小的数据 固定的包大小
    int Recv(char* buffer,int recvDataSize);//接收服务器发送的数据，每次接收指定的字节数大小
    void closeSocket();
    char* getPacket();
    long long getPacketSize(); //返回整个数据包的大小
    void makePacket(char* pData,size_t length,WORD cmd);//进行封包操作
    CClientSocket();
    ~CClientSocket();
private:
    void initSocketVal(); //初始化网络环境
    void clearUpSocketVal();//清除网络环境
private:

    CClientSocket(const CClientSocket& clientsocket) = delete ;
    CClientSocket& operator=(const CClientSocket& clientSocket) = delete ;
//    static void releaseInstance();
//    class CHelper
//    {
//    public:
//        CHelper();
//        ~CHelper();
//    };
private:
    char* m_packet = nullptr;//数据包 ，包含两字节包头，四字节数据长度、两字节命令、数据部分 加上一个'\0'
    long long m_packetSize; //一个数据包的大小
    SOCKET m_clientSocket;
    SOCKADDR_IN m_sockAddrClient;
//    static CClientSocket* m_instance;
//    static CHelper m_helper;
};

#endif // CCLIENTSOCKET_H
