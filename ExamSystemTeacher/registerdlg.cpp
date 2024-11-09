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
}

void RegisterDlg::onAcountChange(QString str)
{
    QRegularExpressionMatch match = this->reAacount.match(this->ui->lineEdit->text());
    if (match.hasMatch()) {
         this->ui->label_2->hide(); // 输入符合正则表达式，隐藏错误标签
    } else {
         this->ui->label_2->show(); // 输入不符合正则表达式，显示错误标签
    }
}

void RegisterDlg::onPasswordChange(QString str)
{
    if(this->ui->lineEdit_2->text().size() > 11)
    {
        this->ui->label_4->show();
        return ;
    }
    QRegularExpressionMatch match = this->rePassword.match(this->ui->lineEdit_2->text());
    if (match.hasMatch()) {
         this->ui->label_4->hide(); // 输入符合正则表达式，隐藏错误标签
    } else {
         this->ui->label_4->show(); // 输入不符合正则表达式，显示错误标签
    }
}

void RegisterDlg::onRightPasswordChange(QString str)
{
    qDebug()<<"str: "<<str;
    if(str != this->ui->lineEdit_2->text())
    {
        this->ui->label_6->show();
    }else
    {
        this->ui->label_6->hide();
    }
}

RegisterDlg::~RegisterDlg()
{
    delete ui;
}
