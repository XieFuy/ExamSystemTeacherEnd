#include "registerdlg.h"
#include "ui_registerdlg.h"
#include <QIcon>
RegisterDlg::RegisterDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("在线考试系统-教师端");
    this->setWindowIcon(QIcon(":/icons/winIcon.png"));
    this->ui->label_2->hide();
    this->ui->label_4->hide();
    this->ui->label_6->hide();
    this->m_registerContorller = new CRegisterContorller();
    this->m_isAcountOk = false;
    this->m_isPasswordOK = false;
    this->m_isRightPasswordOk = false;
    QRegularExpression regex("^[0-9]{0,16}$");
    QRegularExpression regex2(R"((?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{6,11})");
    this->reAacount = regex;
    this->rePassword = regex2;

    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        emit this->rejected();
    });
    QObject::connect(this->ui->lineEdit,&QLineEdit::textChanged,this,&RegisterDlg::onAcountChange);
    QObject::connect(this->ui->lineEdit_2,&QLineEdit::textChanged,this,&RegisterDlg::onPasswordChange);
    QObject::connect(this->ui->lineEdit_3,&QLineEdit::textChanged,this,&RegisterDlg::onRightPasswordChange);
    QObject::connect(this->ui->pushButton_2,&QPushButton::clicked,this,&RegisterDlg::checkRegisterInfo);
}

void RegisterDlg::onAcountChange(QString str)
{
    QRegularExpressionMatch match = this->reAacount.match(this->ui->lineEdit->text());
    if (match.hasMatch()) {
        this->m_isAcountOk = true;
         this->ui->label_2->hide(); // 输入符合正则表达式，隐藏错误标签
    } else {
        this->m_isAcountOk = false;
        this->ui->label_2->show(); // 输入不符合正则表达式，显示错误标签
    }
}

void RegisterDlg::onPasswordChange(QString str)
{
    if(this->ui->lineEdit_2->text().size() > 11)
    {
        this->m_isPasswordOK = false;
        this->ui->label_4->show();
        return ;
    }
    QRegularExpressionMatch match = this->rePassword.match(this->ui->lineEdit_2->text());
    if (match.hasMatch()) {
        this->m_isPasswordOK = true;
        this->ui->label_4->hide(); // 输入符合正则表达式，隐藏错误标签
    } else {
        this->m_isPasswordOK = false;
        this->ui->label_4->show(); // 输入不符合正则表达式，显示错误标签
    }
}

void RegisterDlg::onRightPasswordChange(QString str)
{
    if(str != this->ui->lineEdit_2->text())
    {
        this->m_isRightPasswordOk = false;
        this->ui->label_6->show();
    }else
    {
        this->m_isRightPasswordOk = true;
        this->ui->label_6->hide();
    }
}

void RegisterDlg::checkRegisterInfo()
{
    int sizeAcount = this->ui->lineEdit->text().size();
    int sizePassword = this->ui->lineEdit_2->text().size();
    int sizeRightPassword = this->ui->lineEdit_3->text().size();

    if(sizeAcount == 0)
    {
        QMessageBox* box = new QMessageBox(QMessageBox::Information,"注册提示","错误：职工号输入不能为空!",QMessageBox::Ok);
        box->exec();
        delete box;
    }else if(sizePassword == 0)
    {
        QMessageBox* box = new QMessageBox(QMessageBox::Information,"注册提示","错误：密码输入不能为空!",QMessageBox::Ok);
        box->exec();
        delete box;
    }else if(sizeRightPassword == 0)
    {
        QMessageBox* box = new QMessageBox(QMessageBox::Information,"注册提示","错误：确认密码输入不能为空!",QMessageBox::Ok);
        box->exec();
        delete box;
    }
    else if(!this->m_isAcountOk || !this->m_isPasswordOK || !this->m_isRightPasswordOk)
    {
        //进行错误提示
        QMessageBox* box = new QMessageBox(QMessageBox::Information,"注册提示","错误：注册信息输入格式有误，请确保输入注册信息格式正确!",QMessageBox::Ok);
        box->exec();
        delete box;
    }else
    {
         //调用控制层进行执行注册逻辑
        QString acount = this->ui->lineEdit->text().trimmed();
        QString password = this->ui->lineEdit_2->text().trimmed();
        this->m_registerContorller->registerTeacherInfo(acount,password);
        //提示注册成功
        QMessageBox* box = new QMessageBox(QMessageBox::Information,"注册提示","注册成功!",QMessageBox::Ok);
        box->exec();
        delete box;
        //返回登录界面
        emit this->rejected();
    }
}

RegisterDlg::~RegisterDlg()
{
    if(this->m_registerContorller != nullptr)
    {
        delete this->m_registerContorller;
        this->m_registerContorller = nullptr;
    }
    delete ui;
}
