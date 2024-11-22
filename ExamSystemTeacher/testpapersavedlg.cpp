#include "testpapersavedlg.h"
#include "ui_testpapersavedlg.h"

CTestPaperSaveDlg::CTestPaperSaveDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CTestPaperSaveDlg)
{
    ui->setupUi(this);
    this->m_acount ="";
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //去除对话框的标题栏
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        //执行更新的sql语句 然后才进行返回
        if(this->ui->lineEdit->text().size() > 0)
        {
            //直接进行sql数据库的操作，这里不再设置控制层和模型层
//            CDBHelper* dbHelper = CDBHelper::getInstance();
            CDBHelper* dbHelper = new CDBHelper();
            char sqlBuf[1024];
            memset(sqlBuf,'\0',sizeof(char) * 1024);
            std::string sql;
            //插入记录进入试卷表
            QString testName = this->ui->lineEdit->text().trimmed();
            QByteArray testNameArr = testName.toLocal8Bit();
            QByteArray acountArr = this->m_acount.toUtf8();
            const char* pTestName = testNameArr.data();
            const char* pAcount = acountArr.data();
            sprintf(sqlBuf,"insert into `testPaperInfo` (`testPaperName`,`saveTime`,`teacherId`)\
 values('%s',NOW(),'%s');",pTestName,pAcount);
            sql = sqlBuf;
            bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
            //获取刚刚插入的试卷的id,一定是最大的id
            memset(sqlBuf,'\0',sizeof(char) * 1024);
            sprintf(sqlBuf,"select `testPaperId` from `testPaperInfo` order by `testPaperId` desc limit 1;");
            sql = sqlBuf;
            std::vector<std::vector<std::string>> result =  dbHelper->sqlQuery(sql,"ExamSystem");
            std::cout<<result.at(0).at(0).c_str()<<std::endl;
            //更新添加的所有类型的试题的试卷id为新插入的id
            memset(sqlBuf,'\0',sizeof(char) * 1024);
            sprintf(sqlBuf,"update `singleChoice` set `testPaperId` = %s\
 where  `testPaperId` = 0;",result.at(0).at(0).c_str());
            sql = sqlBuf;
            dbHelper->sqlExcute(sql,"ExamSystem");

            memset(sqlBuf,'\0',sizeof(char) * 1024);
            sprintf(sqlBuf,"update `multiChoice` set `testPaperId` = %s\
 where  `testPaperId` = 0;",result.at(0).at(0).c_str());
            sql = sqlBuf;
            dbHelper->sqlExcute(sql,"ExamSystem");

            memset(sqlBuf,'\0',sizeof(char) * 1024);
            sprintf(sqlBuf,"update `judge` set `testPaperId` = %s\
 where  `testPaperId` = 0;",result.at(0).at(0).c_str());
            sql = sqlBuf;
            dbHelper->sqlExcute(sql,"ExamSystem");

            memset(sqlBuf,'\0',sizeof(char) * 1024);
            sprintf(sqlBuf,"update `shortAnswer` set `testPaperId` = %s\
 where  `testPaperId` = 0;",result.at(0).at(0).c_str());
            sql = sqlBuf;
            dbHelper->sqlExcute(sql,"ExamSystem");
            delete dbHelper;
        }
        emit this->rejected();
    });
}

CTestPaperSaveDlg::~CTestPaperSaveDlg()
{
    delete ui;
}
