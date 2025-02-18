#include "classsavedlg.h"
#include "ui_classsavedlg.h"

CClassSaveDlg::CClassSaveDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CClassSaveDlg)
{
    ui->setupUi(this);
    this->m_mutex = CreateMutex(nullptr,FALSE,nullptr);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        emit this->rejected();
    });

    QObject::connect(this->ui->pushButton_4,&QPushButton::clicked,[=](){
        //生成文件对话框  获取文件的绝对路径
        QString fileName = QFileDialog::getOpenFileName(
             this,
             tr("请选择PNG图片,并且单张图片不得超过400KB"),
             QDir::homePath(),
             tr("PNG Files (*.png);;All Files (*)")
         );
         if (!fileName.isEmpty()) {
           qDebug()<<fileName;

         } else {
           return;
         }
        //获取文件名
         QString tempFileName;
         for(int i = fileName.size() - 1 ; i >= 0 ; i--)
         {
             if(fileName.at(i) == '/')
             {
                 break;
             }
             tempFileName.push_back(fileName.at(i));
         }

         QString _fileName;
         for(QString::reverse_iterator pos = tempFileName.rbegin(); pos != tempFileName.rend(); pos++)
         {
              _fileName.push_back(*pos);
         }
        //显示信息
         this->ui->label_2->setPixmap(QPixmap(fileName));
         this->ui->label_5->setText(_fileName);
         this->filePath = fileName;
         this->fileName = _fileName;
    });

    QObject::connect(this->ui->pushButton_2,&QPushButton::clicked,[=](){
        if(this->ui->lineEdit->text().trimmed() == "" || this->ui->label_5->text().trimmed() == "")
        {
            return;
        }
        //处理上传业务,采用多线程进行处理
         //1、一个线程进行将图片资源进行上传到服务器
        HANDLE thread1 = (HANDLE)_beginthreadex(nullptr,0,&CClassSaveDlg::threadUpLoadFile,this,0,nullptr); //导致bug的原因就是当服务器还没接收完毕的时候，就把窗口删除，导致的崩溃
         //2、一个线程进行对数据库进行存储
        HANDLE thread2 = (HANDLE)_beginthreadex(nullptr,0,&CClassSaveDlg::threadAddClassInfo,this,0,nullptr);

         //3、清除UI的信息

        WaitForSingleObject(thread2,INFINITE);
        WaitForSingleObject(thread1,INFINITE);
        this->ui->lineEdit->setText("");
        this->ui->label_2->setPixmap(QPixmap());
        this->ui->label_5->setText("");
    });
}

void CClassSaveDlg::addClassInfo()
{
    QString path = "/root/picture/";
    path += this->fileName;
    QByteArray pathArr = path.toLocal8Bit();
    const char* pPath = pathArr.data();

    QString className = this->ui->lineEdit->text().trimmed();
    QByteArray classNameArr = className.toLocal8Bit();
    const char* pClassName = classNameArr.data();

    QByteArray acountArr = this->acount.toUtf8();
    const char* pAcount = acountArr.data();

    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[sizeof(char) * 1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"insert into `class` (`classIconPath`,`className`,`createTime`,`teacherId`) values('%s','%s',now(),'%s');",
            pPath,pClassName,pAcount);
    sql = sqlBuf;
    dbHelper->sqlExcute(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
}

unsigned WINAPI CClassSaveDlg::threadAddClassInfo(LPVOID arg)
{
    CClassSaveDlg* thiz = (CClassSaveDlg*)arg;
    thiz->addClassInfo();
    //_endthreadex(0);
    return 0;
}

unsigned WINAPI CClassSaveDlg::threadUpLoadFile(LPVOID arg)
{
 CClassSaveDlg* thiz = (CClassSaveDlg*)arg;
 thiz->upLoadFile(thiz->filePath);
 //_endthreadex(0);
 return 0;
}

void CClassSaveDlg::upLoadFile(QString filePath)
{
    QByteArray arr = filePath.toLocal8Bit();
    const char* pFilePath = arr.data();

//    FILE* pFile = fopen(pFilePath,"rb+");
//    if(pFile == nullptr)
//    {
//        fclose(pFile);
//        return;
//    }

//    fseek(pFile,0,SEEK_END);
//    long long fileSize =  _ftelli64(pFile);
//    fseek(pFile,0,SEEK_SET);

//    QByteArray strArr = this->fileName.toLocal8Bit();
//    const char* pStrName = strArr.data();
//    std::string headPath = "/root/picture/";
//    headPath += pStrName;
//    qDebug()<<headPath.size();
//    char* data = new char[2 + fileSize + headPath.size()]; //全是文件数据
//    memset(data,'\0',sizeof(char) * (2 + fileSize + headPath.size()));
//    WORD pathLenght = headPath.size();
//    memcpy(data,&pathLenght,sizeof(WORD));
//    long long size =  fread(data + 2,1,fileSize,pFile);
//    fclose(pFile);
//    memcpy(data + fileSize + 2,headPath.c_str(),headPath.size());
//    //进行封包操作
//    CClientSocket* clientsocket = CClientSocket::getInstance();
//    clientsocket->initSocket();
//    bool ret =  clientsocket->connectToServer();
//    if(!ret)
//    {
//        return;
//    }
//    clientsocket->makePacket(data,fileSize + headPath.size() + 2,1);
//    char* packet =  clientsocket->getPacket();
//    clientsocket->Send(packet);
//    delete[] data;
//    clientsocket->closeSocket();

    FILE* pFile = fopen(pFilePath,"rb+");
    if(pFile == nullptr)
    {
        fclose(pFile);
        qDebug()<<"打开文件失败！";
        return;
    }

    //获取文件总字节数
    fseek(pFile,0,SEEK_END);
    long long fileSize =  _ftelli64(pFile);
    fseek(pFile,0,SEEK_SET);

    char* fileData = new char[fileSize]; //用于存储文件数据
    memset(fileData,'\0',sizeof(char) * fileSize);
    size_t size = fread(fileData,1,fileSize,pFile);
    fclose(pFile);

    //存储路径
    QByteArray strArr = this->fileName.toLocal8Bit();
    const char* pStrName = strArr.data();
//    WORD  pathLenght = this->fileName.size(); //路径长度
    char* remotePath = new char[1024];
    memset(remotePath,'\0',sizeof(char) * 1024);
    sprintf(remotePath,"/root/picture/%s",pStrName);
    WORD pathLenght = strlen(remotePath);

    char* data = new char[2 + fileSize + pathLenght];
    memset(data,'\0',sizeof(char) * (2 + fileSize + pathLenght));
    char* p = data;
    memcpy(p,&pathLenght,sizeof(WORD));
    p += sizeof(WORD);
    memcpy(p,fileData,fileSize); //解决数据发送不正确的原因，因为是fileData不是&fileData
    p += fileSize;
    memcpy(p,remotePath,pathLenght);
    p += pathLenght;
    delete[] remotePath;
    delete[] fileData;
    //进行网络发送
//    CClientSocket* pSocket = CClientSocket::getInstance();
    CClientSocket* pSocket = new CClientSocket();
    pSocket->initSocket();
    if(!pSocket->connectToServer())
    {
        return;
    }
    //进行封包
    pSocket->makePacket(data,2 + fileSize + pathLenght,1);
    delete[] data;
    char* packet =  pSocket->getPacket();
    pSocket->Send(packet);
    pSocket->closeSocket();
    delete pSocket;
}

CClassSaveDlg::~CClassSaveDlg()
{
    CloseHandle(this->m_mutex);
    delete ui;
}
