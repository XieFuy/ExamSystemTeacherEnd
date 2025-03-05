#include "testpaperreleasedlg.h"
#include "ui_testpaperreleasedlg.h"

CTestPaperReleaseDlg::CTestPaperReleaseDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CTestPaperReleaseDlg)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        this->reject();
    });

    QObject::connect(this,&CTestPaperReleaseDlg::startShowTestPaperName,[=](){
       this->ui->label_3->setText(this->testPaperName);
    });

    QObject::connect(this,&CTestPaperReleaseDlg::startShowSubject,this,&CTestPaperReleaseDlg::showSubject);

    this->ui->comboBox->addItem("未选择",0);
    int index = this->ui->comboBox->currentIndex();
    int memberCount = this->ui->comboBox->itemData(index).toInt();
    QString str = QString::number(memberCount);
    str += "人";
    this->ui->label_6->setText(str);

    QObject::connect(this->ui->comboBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int  index){
      int memberCount =   this->ui->comboBox->itemData(index).toInt();
      QString str = QString::number(memberCount);
      str += "人";
      this->ui->label_6->setText(str);
    });

    QObject::connect(this->ui->pushButton_3,&QPushButton::clicked,[=](){
          if(this->m_dateTimeWid == nullptr)
          {
              this->m_dateTimeWid = new CDateTimeSelectDlg(this->ui->widget_2);
              this->m_dateTimeWid->move(this->ui->lineEdit->x(),this->ui->lineEdit->y() + this->ui->lineEdit->height() + 2);
              this->m_dateTimeWid->exec();
              //拿到时间数据显示到lineEdit上
              QString dateTime = this->m_dateTimeWid->getDateTime();
              qDebug()<<"获取时间字符串："<<dateTime;
              delete this->m_dateTimeWid;
              this->m_dateTimeWid = nullptr;
              this->ui->lineEdit->setText(dateTime);
          }
    });

    QObject::connect(this->ui->pushButton_4,&QPushButton::clicked,[=](){
          if(this->m_dateTimeWid == nullptr)
          {
              this->m_dateTimeWid = new CDateTimeSelectDlg(this->ui->widget_2);
              this->m_dateTimeWid->move(this->ui->lineEdit_2->x(),this->ui->lineEdit_2->y() + this->ui->lineEdit_2->height() + 2);
              this->m_dateTimeWid->exec();
              //拿到时间数据显示到lineEdit上
              QString dateTime = this->m_dateTimeWid->getDateTime();
              qDebug()<<"获取时间字符串："<<dateTime;
              delete this->m_dateTimeWid;
              this->m_dateTimeWid = nullptr;
              this->ui->lineEdit_2->setText(dateTime);
          }
    });

    QObject::connect(this->ui->pushButton_2,&QPushButton::clicked,this,&CTestPaperReleaseDlg::addTestPaperReleaseInfo);
}

typedef struct  addStudentAnswerSignalInfo{
    QString teacherId;
    QString classId;
    QString testPaperId;
    QString StudentId;
    int order;
}AddStudentAnswerSignalInfo;

//TODO：接着这里继续
unsigned WINAPI CTestPaperReleaseDlg::threadAddStudentShortAnswerCorrectInfo(LPVOID arg)
{
    std::shared_ptr<AddStudentAnswerSignalInfo>* p = (std::shared_ptr<AddStudentAnswerSignalInfo>*)arg;
    std::shared_ptr<AddStudentAnswerSignalInfo> aInfo = *p;

    QByteArray teacherIdArr= aInfo->teacherId.toLocal8Bit();
    QByteArray classIdArr = aInfo->classId.toLocal8Bit();
    QByteArray testPaperIdArr = aInfo->testPaperId.toLocal8Bit();
    QByteArray StudentIdArr = aInfo->StudentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId = testPaperIdArr.data();
    const char* pStudentId = StudentIdArr.data();

    //进行数据库操作
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"insert into `shortAnswerCorrect`(`teacherId`,`classId`,`testPaperId`,`studentId`,`order`) \
values('%s','%s','%s','%s',%d);",pTeacherId,pClassId,pTestPaperId,pStudentId,aInfo->order);
    sql = sqlBuf.get();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete p;
    //_endthreadex(0);
    return 0;
}

unsigned WINAPI CTestPaperReleaseDlg::threadAddStudentAnswerShortAnswerInfo(LPVOID arg)
{
    std::shared_ptr<AddStudentAnswerSignalInfo>* p = (std::shared_ptr<AddStudentAnswerSignalInfo>*)arg;
    std::shared_ptr<AddStudentAnswerSignalInfo> aInfo = *p;

    QByteArray teacherIdArr= aInfo->teacherId.toLocal8Bit();
    QByteArray classIdArr = aInfo->classId.toLocal8Bit();
    QByteArray testPaperIdArr = aInfo->testPaperId.toLocal8Bit();
    QByteArray StudentIdArr = aInfo->StudentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId = testPaperIdArr.data();
    const char* pStudentId = StudentIdArr.data();

    qDebug()<<pTeacherId<<pClassId<<pTestPaperId<<pStudentId;
    //进行数据库操作
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"insert into `studentAnswerShortAnswer`(`teacherId`,`classId`,`testPaperId`,`studentId`,`order`) \
values('%s','%s','%s','%s',%d);",pTeacherId,pClassId,pTestPaperId,pStudentId,aInfo->order);
     sql = sqlBuf.get();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete p;
    //_endthreadex(0);
    return 0;
}

unsigned WINAPI CTestPaperReleaseDlg::threadAddStudentAnswerJudgeInfo(LPVOID arg)
{
    std::shared_ptr<AddStudentAnswerSignalInfo>* p = (std::shared_ptr<AddStudentAnswerSignalInfo>*)arg;
    std::shared_ptr<AddStudentAnswerSignalInfo> aInfo = *p;

    QByteArray teacherIdArr= aInfo->teacherId.toLocal8Bit();
    QByteArray classIdArr = aInfo->classId.toLocal8Bit();
    QByteArray testPaperIdArr = aInfo->testPaperId.toLocal8Bit();
    QByteArray StudentIdArr = aInfo->StudentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId = testPaperIdArr.data();
    const char* pStudentId = StudentIdArr.data();

    qDebug()<<pTeacherId<<pClassId<<pTestPaperId<<pStudentId;
    //进行数据库操作
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"insert into `studentAnswerJudge`(`teacherId`,`classId`,`testPaperId`,`studentId`,`order`) \
values('%s','%s','%s','%s',%d);",pTeacherId,pClassId,pTestPaperId,pStudentId,aInfo->order);
     sql = sqlBuf.get();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete p;
    //_endthreadex(0);
    return 0;
}

unsigned WINAPI CTestPaperReleaseDlg::threadAddStudentAnswerMultiInfo(LPVOID arg)
{
    std::shared_ptr<AddStudentAnswerSignalInfo>* p = (std::shared_ptr<AddStudentAnswerSignalInfo>*)arg;
    std::shared_ptr<AddStudentAnswerSignalInfo> aInfo = *p;

    QByteArray teacherIdArr= aInfo->teacherId.toLocal8Bit();
    QByteArray classIdArr = aInfo->classId.toLocal8Bit();
    QByteArray testPaperIdArr = aInfo->testPaperId.toLocal8Bit();
    QByteArray StudentIdArr = aInfo->StudentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId = testPaperIdArr.data();
    const char* pStudentId = StudentIdArr.data();

    qDebug()<<pTeacherId<<pClassId<<pTestPaperId<<pStudentId;
    //进行数据库操作
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"insert into `studentAnswerMulti`(`teacherId`,`classId`,`testPaperId`,`studentId`,`order`) \
values('%s','%s','%s','%s',%d);",pTeacherId,pClassId,pTestPaperId,pStudentId,aInfo->order);
     sql = sqlBuf.get();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete p;
    //_endthreadex(0);
    return 0;
}

//需要将每一个学生下的所有的选择题都进行插入才能完成。
unsigned WINAPI CTestPaperReleaseDlg::threadAddStudentAnswerSignalInfo(LPVOID arg)
{
    std::shared_ptr<AddStudentAnswerSignalInfo>* p = (std::shared_ptr<AddStudentAnswerSignalInfo>*)arg;
    std::shared_ptr<AddStudentAnswerSignalInfo> aInfo = *p;

    QByteArray teacherIdArr= aInfo->teacherId.toLocal8Bit();
    QByteArray classIdArr = aInfo->classId.toLocal8Bit();
    QByteArray testPaperIdArr = aInfo->testPaperId.toLocal8Bit();
    QByteArray StudentIdArr = aInfo->StudentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId = testPaperIdArr.data();
    const char* pStudentId = StudentIdArr.data();

    qDebug()<<pTeacherId<<pClassId<<pTestPaperId<<pStudentId;
    //进行数据库操作
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"insert into `studentAnswerSingal`(`teacherId`,`classId`,`testPaperId`,`studentId`,`order`) \
values('%s','%s','%s','%s',%d);",pTeacherId,pClassId,pTestPaperId,pStudentId,aInfo->order);
     sql = sqlBuf.get();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete p;
    //_endthreadex(0);
    return 0;
}

typedef struct addTestPaperReleaseInfoArg{
    QString startTime;
    QString endTime;
    int longTime;
    int limitSubmit;
    int limitEntry;
    QString acount;
    QString className; //通过课程名称来获取课程id
    QString testPaperName; //通过试卷名称进行获取试卷id
    CTestPaperReleaseDlg* thiz;
}AddTestPaperReleaseInfoArg;

void CTestPaperReleaseDlg::addTestPaperReleaseInfo()  //发布执行accept
{
    AddTestPaperReleaseInfoArg* arg = new AddTestPaperReleaseInfoArg();
    arg->thiz = this;
    arg->startTime = this->ui->lineEdit->text().trimmed();
    arg->endTime = this->ui->lineEdit_2->text().trimmed();
    arg->longTime = this->ui->lineEdit_3->text().toInt();
    arg->limitSubmit = this->ui->lineEdit_4->text().toInt();
    arg->limitEntry = this->ui->lineEdit_5->text().toInt();
    arg->testPaperName = this->ui->label_3->text().trimmed();
    arg->className = this->ui->comboBox->currentText().trimmed();
    arg->acount = this->acount;
    HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadAddTestPaperReleaseInfo,arg,0,nullptr);
    WaitForSingleObject(thread,INFINITE);
//    this->reject();
    this->accept();
}

typedef struct getStudentIdVectorArg{
    QString className_in;
    QString acount_in;
    QVector<QString> studentIdVec_out;
}GetStudentIdVectorArg;

unsigned WINAPI CTestPaperReleaseDlg::threadGetStudentIdVectorEntry(LPVOID arg)
{

    GetStudentIdVectorArg* gInfo = (GetStudentIdVectorArg*)arg;
    //这里的对象在外部使用share_ptr自动进行释放内存不需要在此线程内进行管理内存
    //进行数据库的操作来获取班级的Id
    QByteArray acountArr = gInfo->acount_in.toLocal8Bit();
    QByteArray classNameArr = gInfo->className_in.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();

    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `studentId` from `joinClassStudentManeage` where `className` = '%s' and `teacherId` = '%s';",pClassName,pAcount);
    sql = sqlBuf.get();
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    for(int i = 0 ; i <ret.size();i++)
    {
        gInfo->studentIdVec_out.push_back(QString::fromLocal8Bit(ret.at(i).at(0).c_str()));
    }
    //_endthreadex(0);
    return 0;
}

typedef struct getTestPaperIdEntry{ //线程参数
    QString testPaperName_in;
    QString acount_in;
    int testPaperId_out;
}GetTestPaperIdEntry;

unsigned WINAPI CTestPaperReleaseDlg::threadGetTestPaperIdEntry(LPVOID arg)
{
    GetTestPaperIdEntry* gInfo = (GetTestPaperIdEntry*)arg;
    //这里的对象在外部使用share_ptr自动进行释放内存不需要在此线程内进行管理内存
    //进行数据库的操作来获取班级的Id
    QByteArray acountArr = gInfo->acount_in.toLocal8Bit();
    QByteArray classNameArr = gInfo->testPaperName_in.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pTestPaperName = classNameArr.data();

    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `testPaperId` from `testPaperInfo` where `testPaperName` = '%s' and `teacherId` = '%s';",pTestPaperName,pAcount);
    sql = sqlBuf.get();
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    QString strTestPaperId = QString::fromLocal8Bit(ret.at(0).at(0).c_str());
    gInfo->testPaperId_out  = strTestPaperId.toInt();
    //_endthreadex(0);
    return 0;
}

typedef struct getClassIdEntryArg{
    QString acount_in;
    QString className_in;
    int classId_out;
}GetClassIdEntryArg;

unsigned WINAPI CTestPaperReleaseDlg::threadGetClassIdEntry(LPVOID arg)
{
    GetClassIdEntryArg* gInfo = (GetClassIdEntryArg*)arg;
    //这里的对象在外部使用share_ptr自动进行释放内存不需要在此线程内进行管理内存
    //进行数据库的操作来获取班级的Id
    QByteArray acountArr = gInfo->acount_in.toLocal8Bit();
    QByteArray classNameArr = gInfo->className_in.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();

    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `id` from `class` where `className` = '%s' and `teacherId` = '%s';",pClassName,pAcount);
    sql = sqlBuf.get();
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    QString strClassId = QString::fromLocal8Bit(ret.at(0).at(0).c_str());
    gInfo->classId_out  = strClassId.toInt();
    //_endthreadex(0);
    return 0;
}

typedef struct testPaperSignalOrderArg{
   QString  testPaperId_in;
   QVector<int> orderVec_out;
}TestPaperSignalOrderArg;

unsigned WINAPI CTestPaperReleaseDlg::threadGetTestPaperSignalOrderEntry(LPVOID arg)
{
    TestPaperSignalOrderArg* tInfo = (TestPaperSignalOrderArg*)arg;

    int testPaperId = tInfo->testPaperId_in.toInt();
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `order` from `singleChoice` where testPaperId = %d order by `order`;",testPaperId);
    sql = sqlBuf.get();
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    for(int i = 0 ; i < ret.size();i++)
    {
        tInfo->orderVec_out.push_back(QString::fromLocal8Bit(ret.at(i).at(0).c_str()).toInt());
    }
    //_endthreadex(0);
    return 0;
}

typedef struct getTestPaperMultiOrder{
    QString testPaperId_in;
    QVector<int> order_out;
}GetTestPaperMultiOrder;

unsigned WINAPI CTestPaperReleaseDlg::threadGetTestPaperMultiOrderEntry(LPVOID arg)
{
    GetTestPaperMultiOrder* gInfo = (GetTestPaperMultiOrder*)arg;

    int testPaperId = gInfo->testPaperId_in.toInt();
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `order` from `multiChoice` where testPaperId = %d order by `order`;",testPaperId);
    sql = sqlBuf.get();
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    for(int i = 0 ; i < ret.size();i++)
    {
        gInfo->order_out.push_back(QString::fromLocal8Bit(ret.at(i).at(0).c_str()).toInt());
    }
    //_endthreadex(0);
    return 0;
}

typedef struct getTestPaperJudgeOrderArg{
    QString testPaperId_in;
    QVector<int> order_out;
}GetTestPaperJudgeOrderArg;

unsigned WINAPI CTestPaperReleaseDlg::threadGetTestPaperJudgeOrderEntry(LPVOID arg)
{
    GetTestPaperJudgeOrderArg* gInfo = (GetTestPaperJudgeOrderArg*)arg;

    int testPaperId = gInfo->testPaperId_in.toInt();
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `order` from `judge` where testPaperId = %d order by `order`;",testPaperId);
    sql = sqlBuf.get();
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    for(int i = 0 ; i < ret.size();i++)
    {
        gInfo->order_out.push_back(QString::fromLocal8Bit(ret.at(i).at(0).c_str()).toInt());
    }
    //_endthreadex(0);
    return 0;
}

typedef struct getTestPaperShortAnswerArg{
    QString testPaperId_in;
    QVector<int> order_out;
}GetTestPaperShortAnswerArg;

unsigned WINAPI CTestPaperReleaseDlg::threadGetTestPaperShortAnswerEntry(LPVOID arg)
{
    GetTestPaperShortAnswerArg* gInfo = (GetTestPaperShortAnswerArg*)arg;

    int testPaperId = gInfo->testPaperId_in.toInt();
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `order` from `shortAnswer` where testPaperId = %d order by `order`;",testPaperId);
    sql = sqlBuf.get();
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    for(int i = 0 ; i < ret.size();i++)
    {
        gInfo->order_out.push_back(QString::fromLocal8Bit(ret.at(i).at(0).c_str()).toInt());
    }
    //_endthreadex(0);
    return 0;
}

unsigned WINAPI CTestPaperReleaseDlg::threadAddTestPaperReleaseInfo(LPVOID arg)
{
    AddTestPaperReleaseInfoArg* aInfo = (AddTestPaperReleaseInfoArg*)arg;

    //对数据进行处理
    QByteArray startTimeArr = aInfo->startTime.toLocal8Bit();
    QByteArray endTimeArr = aInfo->endTime.toLocal8Bit();
    QByteArray testPaperNameArr = aInfo->testPaperName.toLocal8Bit();
    QByteArray classNameArr = aInfo->className.toLocal8Bit();
    QByteArray acountArr = aInfo->acount.toLocal8Bit();

    const char* pStartTime = startTimeArr.data();
    const char* pEndTime = endTimeArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    const char* pClassName = classNameArr.data();
    const char* pAcount = acountArr.data();

    std::shared_ptr<GetClassIdEntryArg> classIdArg = std::make_shared<GetClassIdEntryArg>();
    classIdArg->acount_in = QString::fromLocal8Bit(pAcount);
    classIdArg->className_in = QString::fromLocal8Bit(pClassName);
    classIdArg->classId_out = 0;

    std::shared_ptr<GetTestPaperIdEntry> testPaperIdArg = std::make_shared<GetTestPaperIdEntry>();
    testPaperIdArg->acount_in = QString::fromLocal8Bit(pAcount);
    testPaperIdArg->testPaperName_in = QString::fromLocal8Bit(pTestPaperName);
    testPaperIdArg->testPaperId_out = 0;

    std::shared_ptr<GetStudentIdVectorArg> studentIdVecArg = std::make_shared<GetStudentIdVectorArg>();
    studentIdVecArg->acount_in = QString::fromLocal8Bit(pAcount);
    studentIdVecArg->className_in = QString::fromLocal8Bit(pClassName);

    HANDLE threadgetClassId = (HANDLE)_beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadGetClassIdEntry,classIdArg.get(),0,nullptr);
    HANDLE threadGetTestPaperId = (HANDLE)_beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadGetTestPaperIdEntry,testPaperIdArg.get(),0,nullptr);
    HANDLE threadGetStudentIdVec = (HANDLE)_beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadGetStudentIdVectorEntry,studentIdVecArg.get(),0,nullptr);

    WaitForSingleObject(threadGetStudentIdVec,INFINITE);
    WaitForSingleObject(threadGetTestPaperId,INFINITE);
    WaitForSingleObject(threadgetClassId,INFINITE); //从数据库进行获取数据的使用多线程同时获取，然后同时进行等待

    int classId = classIdArg->classId_out;
    int testPaperId = testPaperIdArg->testPaperId_out;


    //拿到选择题的每一题的题号集合，放到子线程去执行
    std::shared_ptr<TestPaperSignalOrderArg> signalOrderArg = std::make_shared<TestPaperSignalOrderArg>();
    signalOrderArg->testPaperId_in = QString::number(testPaperId);

    //拿到多选题的每一题的题号集合，放到子线程执行
    std::shared_ptr<GetTestPaperMultiOrder> multiOrderArg = std::make_shared<GetTestPaperMultiOrder>();
    multiOrderArg->testPaperId_in = QString::number(testPaperId);

    //拿到判断题的每一题的题号集合，放到子线程执行
    std::shared_ptr<GetTestPaperJudgeOrderArg> judgeOrderArg = std::make_shared<GetTestPaperJudgeOrderArg>();
    judgeOrderArg->testPaperId_in = QString::number(testPaperId);

    //拿到简答题的每一题的题号集合，放到子线程执行
    std::shared_ptr<GetTestPaperShortAnswerArg> shortAnswerOrderArg = std::make_shared<GetTestPaperShortAnswerArg>();
    shortAnswerOrderArg->testPaperId_in = QString::number(testPaperId);

    HANDLE threadGetSignalOrder = (HANDLE)_beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadGetTestPaperSignalOrderEntry,signalOrderArg.get(),0,nullptr);
    HANDLE threadGetMultiOrder = (HANDLE)_beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadGetTestPaperMultiOrderEntry,multiOrderArg.get(),0,nullptr);
    HANDLE threadGetJudgeOrder = (HANDLE)_beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadGetTestPaperJudgeOrderEntry,judgeOrderArg.get(),0,nullptr);
    HANDLE threadGetShortAnswerOrder = (HANDLE)_beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadGetTestPaperShortAnswerEntry,shortAnswerOrderArg.get(),0,nullptr);
    WaitForSingleObject(threadGetJudgeOrder,INFINITE);
    WaitForSingleObject(threadGetSignalOrder,INFINITE);
    WaitForSingleObject(threadGetMultiOrder,INFINITE);
    WaitForSingleObject(threadGetShortAnswerOrder,INFINITE);

    //拿到单选题的题号
    //拿到多选题的题号
    //拿到判断题的题号
    //拿到简答题的题号

    //进行数据库操作  放到子线程操作
   /* std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    //先拿到课程id
    sprintf(sqlBuf,"select `id` from `class` where `className` = '%s' and `teacherId` = '%s';",pClassName,pAcount);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    QString strClassId = QString::fromLocal8Bit(ret.at(0).at(0).c_str());
    int classId = strClassId.toInt();*/

    //再拿到试卷id
//    ret.at(0).clear();
//    ret.clear();

    //进行拿到试卷的Id 放到子线程去进行执行
   /* memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"select `testPaperId` from `testPaperInfo` where `testPaperName` = '%s' and `teacherId` = '%s';",pTestPaperName,pAcount);
    sql = sqlBuf;
    ret = dbHelper->sqlQuery(sql,"ExamSystem");
    QString strTestPaperId =  QString::fromLocal8Bit(ret.at(0).at(0).c_str());
    int testPaperId = strTestPaperId.toInt();*/

    //再拿到属于这个课程的所有的学生id 放到子线程去执行
   /* memset(sqlBuf,'\0',sizeof(char) * 1024000);
    //先拿到课程id
    sprintf(sqlBuf,"select `studentId` from `joinClassStudentManeage` where `className` = '%s' and `teacherId` = '%s';",pClassName,pAcount);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret2 =  dbHelper->sqlQuery(sql,"ExamSystem");*/


    //等待所有的线程都完成才进行获取值进行插入操作
    //进行插入单选题答题记录
    QVector<HANDLE> temp;
    qDebug()<<studentIdVecArg->studentIdVec_out.size()<<" "<<signalOrderArg->orderVec_out.size();
    for(int i = 0 ; i < studentIdVecArg->studentIdVec_out.size();i++)
    {
        for(int j = 0;j < signalOrderArg->orderVec_out.size();j++)
        {
            std::shared_ptr<AddStudentAnswerSignalInfo> arg = std::make_shared<AddStudentAnswerSignalInfo>();
            arg->teacherId =QString::fromLocal8Bit(pAcount);
            arg->classId = QString::number(classId);
            arg->testPaperId = QString::number(testPaperId);
            arg->StudentId  = studentIdVecArg->studentIdVec_out.at(i);
            arg->order = signalOrderArg->orderVec_out.at(j);

            std::shared_ptr<AddStudentAnswerSignalInfo>* p = new std::shared_ptr<AddStudentAnswerSignalInfo>(arg);
            //执行插入学生答案单选题记录
            HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadAddStudentAnswerSignalInfo,p,0,nullptr);
            temp.push_back(thread);
        }
    }
    WaitForMultipleObjects(temp.size(),temp.data(),TRUE,INFINITE);
    temp.clear();

    /*for(int i = 0 ; i < ret2.size();i++)
    {
        std::shared_ptr<AddStudentAnswerSignalInfo> arg = std::make_shared<AddStudentAnswerSignalInfo>();
        arg->teacherId =QString::fromLocal8Bit(pAcount);
        arg->classId = QString::number(classId);
        arg->testPaperId = QString::number(testPaperId);
        arg->StudentId  = QString::fromLocal8Bit(ret2.at(i).at(0).c_str());

        std::shared_ptr<AddStudentAnswerSignalInfo>* p = new std::shared_ptr<AddStudentAnswerSignalInfo>(arg);
        //执行插入学生答案单选题记录
       _beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadAddStudentAnswerSignalInfo,p,0,nullptr);
    }*/

    //进行插入多选题答题记录
    qDebug()<<studentIdVecArg->studentIdVec_out.size()<<" "<<multiOrderArg->order_out.size();
    for(int i = 0 ; i < studentIdVecArg->studentIdVec_out.size();i++)
    {
        for(int j = 0;j < multiOrderArg->order_out.size();j++)
        {
            std::shared_ptr<AddStudentAnswerSignalInfo> arg = std::make_shared<AddStudentAnswerSignalInfo>();
            arg->teacherId =QString::fromLocal8Bit(pAcount);
            arg->classId = QString::number(classId);
            arg->testPaperId = QString::number(testPaperId);
            arg->StudentId  = studentIdVecArg->studentIdVec_out.at(i);
            arg->order = multiOrderArg->order_out.at(j);
            std::shared_ptr<AddStudentAnswerSignalInfo>* p = new std::shared_ptr<AddStudentAnswerSignalInfo>(arg);
            //执行插入学生答案记录
            HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadAddStudentAnswerMultiInfo,p,0,nullptr);
            temp.push_back(thread);
        }
    }
    WaitForMultipleObjects(temp.size(),temp.data(),TRUE,INFINITE);
    temp.clear();

    /*for(int i = 0 ; i < ret2.size();i++)
    {
        std::shared_ptr<AddStudentAnswerSignalInfo> arg = std::make_shared<AddStudentAnswerSignalInfo>();
        arg->teacherId =QString::fromLocal8Bit(pAcount);
        arg->classId = QString::number(classId);
        arg->testPaperId = QString::number(testPaperId);
        arg->StudentId  = QString::fromLocal8Bit(ret2.at(i).at(0).c_str());

        std::shared_ptr<AddStudentAnswerSignalInfo>* p = new std::shared_ptr<AddStudentAnswerSignalInfo>(arg);
        //执行插入学生答案记录
       _beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadAddStudentAnswerMultiInfo,p,0,nullptr);
    }*/

    qDebug()<<studentIdVecArg->studentIdVec_out.size()<<" "<<judgeOrderArg->order_out.size();
    //进行插入判断题答题记录
    for(int i = 0 ; i < studentIdVecArg->studentIdVec_out.size();i++)
    {
        for(int j = 0;j < judgeOrderArg->order_out.size();j++)
        {
            std::shared_ptr<AddStudentAnswerSignalInfo> arg = std::make_shared<AddStudentAnswerSignalInfo>();
            arg->teacherId =QString::fromLocal8Bit(pAcount);
            arg->classId = QString::number(classId);
            arg->testPaperId = QString::number(testPaperId);
            arg->StudentId  = studentIdVecArg->studentIdVec_out.at(i);
            arg->order = judgeOrderArg->order_out.at(j);
            std::shared_ptr<AddStudentAnswerSignalInfo>* p = new std::shared_ptr<AddStudentAnswerSignalInfo>(arg);
            //执行插入学生答案记录
           _beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadAddStudentAnswerJudgeInfo,p,0,nullptr);
        }
    }
    WaitForMultipleObjects(temp.size(),temp.data(),TRUE,INFINITE);
    temp.clear();
    /*for(int i = 0 ; i < ret2.size();i++)
    {
        std::shared_ptr<AddStudentAnswerSignalInfo> arg = std::make_shared<AddStudentAnswerSignalInfo>();
        arg->teacherId =QString::fromLocal8Bit(pAcount);
        arg->classId = QString::number(classId);
        arg->testPaperId = QString::number(testPaperId);
        arg->StudentId  = QString::fromLocal8Bit(ret2.at(i).at(0).c_str());

        std::shared_ptr<AddStudentAnswerSignalInfo>* p = new std::shared_ptr<AddStudentAnswerSignalInfo>(arg);
        //执行插入学生答案记录
       _beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadAddStudentAnswerJudgeInfo,p,0,nullptr);
    }*/

    qDebug()<<studentIdVecArg->studentIdVec_out.size()<<" "<<shortAnswerOrderArg->order_out.size();
    //进行插入简答题答题记录
    for(int i = 0 ; i < studentIdVecArg->studentIdVec_out.size();i++)
    {
        for(int j = 0;j < shortAnswerOrderArg->order_out.size();j++)
        {
            std::shared_ptr<AddStudentAnswerSignalInfo> arg = std::make_shared<AddStudentAnswerSignalInfo>();
            arg->teacherId =QString::fromLocal8Bit(pAcount);
            arg->classId = QString::number(classId);
            arg->testPaperId = QString::number(testPaperId);
            arg->StudentId  = studentIdVecArg->studentIdVec_out.at(i);
            arg->order = shortAnswerOrderArg->order_out.at(j);
            std::shared_ptr<AddStudentAnswerSignalInfo>* p = new std::shared_ptr<AddStudentAnswerSignalInfo>(arg);
            //执行插入学生答案记录
           _beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadAddStudentAnswerShortAnswerInfo,p,0,nullptr);
        }
    }
    WaitForMultipleObjects(temp.size(),temp.data(),TRUE,INFINITE);
    temp.clear();

    //进行插入简答题评分记录
    for(int i = 0 ; i < studentIdVecArg->studentIdVec_out.size();i++)
    {
        for(int j = 0;j < shortAnswerOrderArg->order_out.size();j++)
        {
            std::shared_ptr<AddStudentAnswerSignalInfo> arg = std::make_shared<AddStudentAnswerSignalInfo>();
            arg->teacherId =QString::fromLocal8Bit(pAcount);
            arg->classId = QString::number(classId);
            arg->testPaperId = QString::number(testPaperId);
            arg->StudentId  = studentIdVecArg->studentIdVec_out.at(i);
            arg->order = shortAnswerOrderArg->order_out.at(j);
            std::shared_ptr<AddStudentAnswerSignalInfo>* p = new std::shared_ptr<AddStudentAnswerSignalInfo>(arg);
            //执行插入学生答案记录
           _beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadAddStudentShortAnswerCorrectInfo,p,0,nullptr);
        }
    }
    WaitForMultipleObjects(temp.size(),temp.data(),TRUE,INFINITE);
    temp.clear();

    /*for(int i = 0 ; i < ret2.size();i++)
    {
        std::shared_ptr<AddStudentAnswerSignalInfo> arg = std::make_shared<AddStudentAnswerSignalInfo>();
        arg->teacherId =QString::fromLocal8Bit(pAcount);
        arg->classId = QString::number(classId);
        arg->testPaperId = QString::number(testPaperId);
        arg->StudentId  = QString::fromLocal8Bit(ret2.at(i).at(0).c_str());

        std::shared_ptr<AddStudentAnswerSignalInfo>* p = new std::shared_ptr<AddStudentAnswerSignalInfo>(arg);
        //执行插入学生答案记录
       _beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadAddStudentAnswerShortAnswerInfo,p,0,nullptr);
    }*/

    //清除ret2所有的元素
   /* for(int i = 0 ; i < ret2.size();i++)
    {
        ret2.at(i).clear();
    }
    ret2.clear();*/

    //进行记录插入
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"insert into `testPaperRelease` (`teacherId`,`classId`,`testPaperId`,`examStartTime`,`examEndTime`,`examLongTimeMinute`,`limitSubmit`, `limitEntry`) \
values('%s',%d,%d,'%s','%s',%d,%d,%d);",pAcount,classId,testPaperId,pStartTime,pEndTime,aInfo->longTime,aInfo->limitSubmit,aInfo->limitEntry);
    sql = sqlBuf.get();
    dbHelper->sqlExcute(sql,"ExamSystem");
    delete aInfo;
    //_endthreadex(0);
    return 0;
}

void CTestPaperReleaseDlg::SetClassName(QString className)
{
    this->className = className;
}

void CTestPaperReleaseDlg::showSubject(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return;
    }
    //进行绑定comboBox
    for(int i = 0 ; i < ret->size();i++)
    {
        int memberCount = ret->at(i).at(1).toInt();
        this->ui->comboBox->addItem(ret->at(i).at(0),memberCount);
        qDebug()<<ret->at(i).at(0)<<"  总人数"<<memberCount;
    }
    delete ret;
}

typedef  struct getClassNameByAcountArg
{
    QString acount;
    CTestPaperReleaseDlg* thiz;
}GetClassNameByAcountArg;

void CTestPaperReleaseDlg::getClassNameByAcount()
{
    GetClassNameByAcountArg* arg = new GetClassNameByAcountArg();
    arg->acount = this->acount;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CTestPaperReleaseDlg::threadGetClassNameByAcount,arg,0,nullptr);
}

unsigned WINAPI CTestPaperReleaseDlg::threadGetClassNameByAcount(LPVOID arg)
{
     GetClassNameByAcountArg* gInfo = (GetClassNameByAcountArg*)arg;

     //进行数据处理
     QByteArray acountArr = gInfo->acount.toUtf8();
     const char* pAcount = acountArr.data();

     //进行数据库查询操作
     std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
     char* sqlBuf = new char[1024000];
     memset(sqlBuf,'\0',sizeof(char) * 1024000);
     std::string sql;
     sprintf(sqlBuf,"SELECT \n\
c.`className`,\n\
COUNT(j.`studentId`) AS `totalStudents`\n\
FROM \n\
`class` c\n\
JOIN \n\
`joinClassStudentManeage` j ON c.`className` = j.`className` AND c.`teacherId` = j.`teacherId`\n\
WHERE \n\
c.`teacherId` = '%s'\n\
GROUP BY \n\
c.`className`;",pAcount);
     sql = sqlBuf;
     std::vector<std::vector<std::string>> ret = dbHelper->sqlQuery(sql,"ExamSystem");

     //进行存储进入QVector
     QVector<QVector<QString>>* result = new QVector<QVector<QString>>();
     for(int i = 0 ; i < ret.size();i++)
     {
         QVector<QString> temp;
         for(int j = 0 ; j < ret.at(i).size();j++)
         {
             QString str = QString::fromLocal8Bit(ret.at(i).at(j).c_str());
             temp.push_back(str);
         }
         result->push_back(temp);
     }
     emit gInfo->thiz->startShowSubject(result);
     delete[] sqlBuf;
     delete gInfo;
     //_endthreadex(0);
     return 0;
}

void CTestPaperReleaseDlg::SetAcount(QString acount)
{
    this->acount = acount;
    this->getClassNameByAcount();
}

void CTestPaperReleaseDlg::SetTestPaperName(QString testPaperName)
{
    this->testPaperName = testPaperName;
    emit this->startShowTestPaperName(this->testPaperName);
}

CTestPaperReleaseDlg::~CTestPaperReleaseDlg()
{
    delete ui;
}
