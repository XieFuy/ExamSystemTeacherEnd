#include "namechangedlg.h"
#include "ui_namechangedlg.h"

CNameChangeDlg::CNameChangeDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CNameChangeDlg)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //去除对话框的标题栏
    this->m_acount = "";
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        //执行更新的sql语句 然后才进行返回
        if(this->ui->lineEdit->text().size() > 0)
        {
            char sqlBuf[1024];
            memset(sqlBuf,'\0',sizeof(char) * 1024);
            QString qName =  this->ui->lineEdit->text();
            QByteArray nameArr = qName.toLocal8Bit();
            const char* pName = nameArr.data();
            QByteArray acountArr =this->m_acount.toUtf8();
            const char* pAcount = acountArr.data();
            sprintf(sqlBuf,"update  `TeacherInfo` set `name` = '%s' where `teacherId` = '%s'; ",pName,pAcount);
            std::string sql = sqlBuf;
            CDBHelper* dbHelper = CDBHelper::getInstance();
            dbHelper->sqlExcute(sql,"ExamSystem");
        }
        emit this->rejected();
    });
}



CNameChangeDlg::~CNameChangeDlg()
{
    delete ui;
}
