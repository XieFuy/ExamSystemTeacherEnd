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

void CTestPaperReleaseDlg::addTestPaperReleaseInfo()
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
    this->reject();
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

    //进行数据库操作
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    //先拿到课程id
    sprintf(sqlBuf,"select `id` from `class` where `className` = '%s' and `teacherId` = '%s';",pClassName,pAcount);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    QString strClassId = QString::fromLocal8Bit(ret.at(0).at(0).c_str());
    int classId = strClassId.toInt();

    //再拿到试卷id
    ret.at(0).clear();
    ret.clear();

    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"select `testPaperId` from `testPaperInfo` where `testPaperName` = '%s' and `teacherId` = '%s';",pTestPaperName,pAcount);
    sql = sqlBuf;
    ret = dbHelper->sqlQuery(sql,"ExamSystem");
    QString strTestPaperId =  QString::fromLocal8Bit(ret.at(0).at(0).c_str());
    int testPaperId = strTestPaperId.toInt();

    //进行记录插入
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"insert into `testPaperRelease` (`teacherId`,`classId`,`testPaperId`,`examStartTime`,`examEndTime`,`examLongTimeMinute`,`limitSubmit`, `limitEntry`) \
values('%s',%d,%d,'%s','%s',%d,%d,%d);",pAcount,classId,testPaperId,pStartTime,pEndTime,aInfo->longTime,aInfo->limitSubmit,aInfo->limitEntry);
    sql = sqlBuf;
    dbHelper->sqlExcute(sql,"ExamSystem");

    delete[] sqlBuf;
    delete aInfo;
    _endthreadex(0);
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
     _endthreadex(0);
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
