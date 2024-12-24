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
