#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("在线考试系统-教师端");
    this->setWindowIcon(QIcon(":/icons/winIcon.png"));
    this->setContentsMargins(0,0,0,0);//设置布局无边界
    this->ui->label_7->hide();
    this->ui->label_8->hide();
    this->m_isAcountOk = false;
    this->m_isPasswordOk = false;
    QRegularExpression regex("^[\\d]+(\\.\\d+)?$");
    QRegularExpression regex2("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{6,}$");
    this->reAacount = regex;
    this->rePassword = regex2;
    QObject::connect(this->ui->lineEdit,&QLineEdit::textChanged,this,&Widget::onAccountChange);
    QObject::connect(this->ui->lineEdit_2,&QLineEdit::textChanged,this,&Widget::onPasswordChange);
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,this,&Widget::login);
}

void Widget::login() //执行登录逻辑
{
    if(this->ui->lineEdit->text().size() == 0 || this->ui->lineEdit_2->text().size() == 0 )
    {
        QMessageBox* box = new QMessageBox(QMessageBox::Warning,"错误提示","职工号或密码输入不能为空！",QMessageBox::Ok);
        box->exec();
        delete box;
    }
    else if((!this->m_isAcountOk) || (!this->m_isPasswordOk))
    {
        QMessageBox* box = new QMessageBox(QMessageBox::Warning,"错误提示","职工号或密码输入格式不正确！",QMessageBox::Ok);
        box->exec();
        delete box;
    }
}

void Widget::onAccountChange(QString str)
{
    QRegularExpressionMatch match = this->reAacount.match(this->ui->lineEdit->text());
    if (match.hasMatch()) {
        this->m_isAcountOk = true;
        this->ui->label_7->hide(); // 输入符合正则表达式，隐藏错误标签
    } else {
        this->m_isAcountOk = false;
        this->ui->label_7->show(); // 输入不符合正则表达式，显示错误标签
    }
}

void Widget::onPasswordChange(QString str)
{
    QRegularExpressionMatch match = this->rePassword.match(this->ui->lineEdit_2->text());
    if (match.hasMatch()) {
        this->m_isPasswordOk = true;
        this->ui->label_8->hide(); // 输入符合正则表达式，隐藏错误标签
    } else {
        this->m_isPasswordOk = false;
        this->ui->label_8->show(); // 输入不符合正则表达式，显示错误标签
    }
}

Widget::~Widget()
{
    delete ui;
}

