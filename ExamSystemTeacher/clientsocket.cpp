#include "clientsocket.h"

CClientSocket* CClientSocket::m_instance = nullptr;
CClientSocket::CHelper  CClientSocket::m_helper;

CClientSocket::CClientSocket()
{
    this->initSocketVal(); //初始化网络环境
    this->m_packetSize = 2 + 4 + 2 + (1024*1024*2) + 1;
    this->m_packet = new char[this->m_packetSize]; //数据部分的大小是2MB的大小
    memset(this->m_packet,'\0',sizeof(char)*this->m_packetSize);
}

CClientSocket::~CClientSocket()
{
    this->clearUpSocketVal(); //清除网络环境
    if(this->m_packet != nullptr)
    {
        delete[] this->m_packet;
        this->m_packet = nullptr;
    }
}

CClientSocket* CClientSocket::getInstance()
{
    if(CClientSocket::m_instance == nullptr)
    {
        CClientSocket::m_instance = new CClientSocket();
    }
    return CClientSocket::m_instance;
}

void CClientSocket::releaseInstance()
{
    if(CClientSocket::m_instance != nullptr)
    {
        delete CClientSocket::m_instance;
        CClientSocket::m_instance = nullptr;
    }
}

CClientSocket::CHelper::CHelper()
{
    CClientSocket::getInstance();
}

CClientSocket::CHelper::~CHelper()
{
    CClientSocket::releaseInstance();
}

void CClientSocket::initSocketVal()
{
    WORD wVersionRequested;
        WSADATA wsaData;
        int err;
        wVersionRequested = MAKEWORD(2, 2);

        err = WSAStartup(wVersionRequested, &wsaData);
        if (err != 0) {
            return ;
        }
        if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
            WSACleanup();
            return;
        }
}

void CClientSocket::clearUpSocketVal()
{
     WSACleanup();
}

void CClientSocket::initSocket()
{
    this->m_clientSocket = socket(AF_INET,SOCK_STREAM,0);
    if(this->m_clientSocket == INVALID_SOCKET)
    {
        qDebug()<<"socket Error！ errorno: "<<WSAGetLastError();
        return ;
    }
    int size = 1024*1024*2;
    setsockopt(this->m_clientSocket, SOL_SOCKET, SO_SNDBUF, (const char *)&size, sizeof(size));
    this->m_sockAddrClient.sin_port = htons(9527); //客户端连接9527端口
    this->m_sockAddrClient.sin_family = AF_INET;
    this->m_sockAddrClient.sin_addr.S_un.S_addr = inet_addr("120.78.122.212"); //填入服务器的地址
}

bool CClientSocket::connectToServer()
{
    if(connect(this->m_clientSocket,(SOCKADDR*)&this->m_sockAddrClient,sizeof(SOCKADDR)) != 0)
    {
        qDebug()<<"connect Error! Errno: "<<WSAGetLastError();
        return false;
    }
    return true;
}


/*以后优化的点，send*/
int CClientSocket::Send(char* pData)
{
    if(pData == nullptr)
    {
        return -1;
    }

    long long alReadySend = 0;
    long long sendCount = this->m_packetSize;
    while (true) {
        int ret  =  send(this->m_clientSocket,pData + alReadySend,sendCount - alReadySend,0);
        if(ret <= 0)
        {
            break;
        }
        alReadySend += ret;
    }
    return  alReadySend;
}

int CClientSocket::Recv(char* buffer)
{
    if(buffer == nullptr)
    {
        return -1;
    }

    //循环接收直到接收完毕一个数据包为止
    long long alReadRecv = 0;
    long long recvCount = this->m_packetSize;
    while(true)
    {
        int ret =  recv(this->m_clientSocket,buffer + alReadRecv,recvCount - alReadRecv,0);
        if(ret <= 0)
        {
            break;
        }
        alReadRecv += ret;
    }
    return alReadRecv;
}

void CClientSocket::closeSocket()
{
    if(this->m_clientSocket != INVALID_SOCKET)
    {
        closesocket(this->m_clientSocket);
        this->m_clientSocket = INVALID_SOCKET;
    }
}

char* CClientSocket::getPacket()
{
    return this->m_packet;
}

long long CClientSocket::getPacketSize()
{
    return this->m_packetSize;
}

void CClientSocket::makePacket(char* pData,size_t length,WORD cmd) //注意单个数据包的数据位长度不能超过2MB
{
    if(pData == nullptr || length <= 0)
    {
        return;
    }
    WORD head = 0xFEFF;
    DWORD dataLength = length; //确保是四字节
    memset(this->m_packet,'\0',this->m_packetSize * sizeof(char));
    memcpy(this->m_packet,&head,sizeof(WORD));
    memcpy(this->m_packet + 2,&dataLength,sizeof(DWORD));
    memcpy(this->m_packet + 2 + 4,&cmd,sizeof(WORD));
    memcpy(this->m_packet + 2 + 4 + 2,pData,length);
}
