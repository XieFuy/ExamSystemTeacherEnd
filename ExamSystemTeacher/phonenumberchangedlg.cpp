#include "phonenumberchangedlg.h"
#include "ui_phonenumberchangedlg.h"

CPhoneNumberChangeDlg::CPhoneNumberChangeDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPhoneNumberChangeDlg)
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
            QString qPhoneNumber =  this->ui->lineEdit->text();
            QByteArray PhoneNumberArr = qPhoneNumber.toLocal8Bit();
            const char* pPhoneNumber = PhoneNumberArr.data();
            QByteArray acountArr =this->m_acount.toUtf8();
            const char* pAcount = acountArr.data();
            sprintf(sqlBuf,"update  `TeacherInfo` set `phoneNumber` = '%s' where `teacherId` = '%s'; ",pPhoneNumber,pAcount);
            std::string sql = sqlBuf;
//            CDBHelper* dbHelper = CDBHelper::getInstance();
            CDBHelper* dbHelper = new CDBHelper();
            dbHelper->sqlExcute(sql,"ExamSystem");
            delete dbHelper;
        }
        emit this->rejected();
    });
}

CPhoneNumberChangeDlg::~CPhoneNumberChangeDlg()
{
    delete ui;
}
