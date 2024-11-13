#include "mainmenuedlg.h"
#include "ui_mainmenuedlg.h"

CMainMenueDlg::CMainMenueDlg(QWidget *parent) : //主菜单界面类
    QDialog(parent),
    ui(new Ui::CMainMenueDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("在线考试系统-教师端");
    this->setWindowIcon(QIcon(":/icons/winIcon.png"));

    //生成控制层
    this->m_mainMenueContorller = new CMainMenueContorller();
    //设置标题栏头像为圆形
    this->ui->label_head->setMask(QRegion(ui->label_head->rect(),QRegion::RegionType::Ellipse));
    this->ui->label_head2->setMask(QRegion(ui->label_head2->rect(),QRegion::RegionType::Ellipse));
    //鼠标进入人物姓名的时候需要实现对话框的动态效果
    this->m_exitLoginDlg = new CExitLoginDlg(this);
    this->m_exitLoginDlg->move(this->ui->label_name->x(),this->ui->label->height()+1);
    this->m_exitLoginDlg->hide();
    this->ui->label_name->installEventFilter(this);
    this->m_exitLoginDlg->installEventFilter(this);

    //界面初始化的默认选中项
    this->ui->pushButton_3->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
    this->ui->pushButton_8->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
    this->ui->stackedWidget->setCurrentIndex(0);
    this->ui->stackedWidget_2->setCurrentIndex(0);

    QObject::connect(this,&CMainMenueDlg::startInitTeacherInfoTable,this,&CMainMenueDlg::initTeacherInfoTable);
    emit this->startInitTeacherInfoTable();

    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(5);
    });

    QObject::connect(this->ui->pushButton_3,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(0);
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_4,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(1);
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_5,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(2);
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_6,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(3);
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_7,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(4);
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    this->m_signalOperator = new QTreeWidgetItem(QStringList()<<"1、单选题");
    this->m_multiOerator = new QTreeWidgetItem(QStringList()<<"2、多选题");
    this->m_judge = new QTreeWidgetItem(QStringList()<<"3、判断题");
    this->m_ShortAnswer = new QTreeWidgetItem(QStringList()<<"4、简答题");
    this->ui->treeWidget->addTopLevelItem(this->m_signalOperator);
    this->ui->treeWidget->addTopLevelItem(this->m_multiOerator);
    this->ui->treeWidget->addTopLevelItem(this->m_judge);
    this->ui->treeWidget->addTopLevelItem(this->m_ShortAnswer);
    QTreeWidgetItem* test = new QTreeWidgetItem(QStringList()<<"测试");
    this->m_signalOperator->addChild(test);

    QObject::connect(this->ui->pushButton_8,&QPushButton::clicked,[=](){
        this->ui->stackedWidget_2->setCurrentIndex(0);
        this->ui->pushButton_8->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_9->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_10->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_11->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_9,&QPushButton::clicked,[=](){
        this->ui->stackedWidget_2->setCurrentIndex(1);
        this->ui->pushButton_9->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_8->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_10->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_11->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_10,&QPushButton::clicked,[=](){
        this->ui->stackedWidget_2->setCurrentIndex(2);
        this->ui->pushButton_10->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_8->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_9->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_11->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_11,&QPushButton::clicked,[=](){
        this->ui->stackedWidget_2->setCurrentIndex(3);
        this->ui->pushButton_11->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_8->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_9->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_10->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    //进行员工职员信息回显
    QObject::connect(this,&CMainMenueDlg::startShowTeacherInfo,this,&CMainMenueDlg::showTeacherInfo);
    emit this->startShowTeacherInfo();

}

void  CMainMenueDlg::showTeacherInfo()
{
   this->m_mainMenueContorller->showTeacherInfo();
}

void CMainMenueDlg::initTeacherInfoTable()
{
  this->m_mainMenueContorller->initTeacherInfoTable();
}

bool CMainMenueDlg::eventFilter (QObject* obj, QEvent* e) //原理底层跟一个定时器一样一直触发执行的函数
{
    if(obj == this->ui->label_name)
    {
        if(e->type() == QEvent::Enter)
        {
            this->m_exitLoginDlg->show();
        }
    }else if(obj == this->m_exitLoginDlg)
    {
        if(e->type() == QEvent::Leave)
        {
            this->m_exitLoginDlg->hide();
        }
    }
    return QDialog::eventFilter(obj,e);
}

CMainMenueDlg::~CMainMenueDlg()
{
    if(this->m_exitLoginDlg != nullptr)
    {
        delete this->m_exitLoginDlg;
        this->m_exitLoginDlg = nullptr;
    }
    if(this->m_signalOperator != nullptr)
    {
        delete this->m_signalOperator;
        this->m_signalOperator = nullptr;
    }
    if(this->m_multiOerator != nullptr)
    {
        delete this->m_multiOerator;
        this->m_multiOerator = nullptr;
    }
    if(this->m_judge != nullptr)
    {
        delete this->m_judge;
        this->m_judge = nullptr;
    }
    if(this->m_ShortAnswer != nullptr)
    {
        delete this->m_ShortAnswer;
        this->m_ShortAnswer = nullptr;
    }
    if(this->m_mainMenueContorller != nullptr)
    {
        delete this->m_mainMenueContorller;
        this->m_mainMenueContorller = nullptr;
    }
    delete ui;
}
