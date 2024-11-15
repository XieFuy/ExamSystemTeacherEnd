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
    this->m_loginContorller = new CLoginContorller(); //生成控制层
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
    QObject::connect(this,&Widget::initTeacherDatabase,[=](){ //初始化教师数据库
        this->m_loginContorller->initTeacherDatabase();
    });
    QObject::connect(this,&Widget::initTeacherTable,[=](){//初始化教师数据库表
        this->m_loginContorller->initTeacherTable();
    });   
    QObject::connect(this->ui->pushButton_2,&QPushButton::clicked,this,&Widget::initRegisterDlg);
    emit this->initTeacherDatabase(); //注意先绑定信号槽，再进行发出信号
    emit this->initTeacherTable();
}

void Widget::initRegisterDlg()
{
    if(this->m_registerDlg == nullptr)
    {
        this->m_registerDlg = new RegisterDlg();
        this->m_registerDlg->move(this->x(),this->y());
        this->hide();
        this->m_registerDlg->show();
        QObject::connect(this->m_registerDlg,&RegisterDlg::rejected,[=](){//监听信号槽必须确保监听的对象已经生成的时刻进行绑定信号槽
            this->move(this->m_registerDlg->x(),this->m_registerDlg->y());
            this->show();
            if(this->m_registerDlg != nullptr)
            {
                delete this->m_registerDlg;
                this->m_registerDlg = nullptr;
            }
            this->ui->lineEdit->setText("");
            this->ui->lineEdit_2->setText("");
            this->ui->label_7->hide();
            this->ui->label_8->hide();
        });
    }
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
    }else
    {
       //调用登录控制层
        QString acount = this->ui->lineEdit->text().trimmed();
        QString password = this->ui->lineEdit_2->text().trimmed();
        bool ret =  this->m_loginContorller->login(acount,password);
        if(ret)
        {
            //登录成功,进入到主页面
            if(this->m_mainMenueDlg == nullptr)
            {
                this->m_mainMenueDlg = new CMainMenueDlg();
                this->m_mainMenueDlg->move(20,20);
                this->m_mainMenueDlg->show();
                this->m_mainMenueDlg->setLoginedAcount(acount);
                emit this->m_mainMenueDlg->startShowTeacherInfo(acount);
                this->hide();
                //监听主菜单页面的退出消息
                QObject::connect(this->m_mainMenueDlg,&CMainMenueDlg::rejected,[=](){
                    //对界面进行销毁释放内存
                    this->show();
                    this->ui->lineEdit->setText("");
                    this->ui->lineEdit_2->setText("");
                    this->ui->label_7->hide();
                    this->ui->label_8->hide();
                    if(this->m_mainMenueDlg != nullptr)
                    {
                        delete  this->m_mainMenueDlg;
                        this->m_mainMenueDlg = nullptr;
                    }
                });
            }
        }else
        {
            //登录失败
            QMessageBox* box = new QMessageBox(QMessageBox::Warning,"登录反馈","登录失败，职工号或密码错误!",QMessageBox::Ok);
            box->exec();
            delete box;
        }
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
    if(this->m_loginContorller != nullptr)
    {
        delete this->m_loginContorller;
        this->m_loginContorller = nullptr;
    }
    if(this->m_mainMenueDlg != nullptr)
    {
        delete this->m_mainMenueDlg;
        this->m_mainMenueDlg = nullptr;
    }
    delete ui;
}

