#include "mainmenuedlg.h"
#include "ui_mainmenuedlg.h"

CMainMenueDlg::CMainMenueDlg(QWidget *parent) : //主菜单界面类
    QDialog(parent),
    ui(new Ui::CMainMenueDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("在线考试系统-教师端");
    this->setWindowIcon(QIcon(":/icons/winIcon.png"));
    //设置标题栏头像为圆形
    this->ui->label_head->setMask(QRegion(ui->label_head->rect(),QRegion::RegionType::Ellipse));
    this->ui->label_head2->setMask(QRegion(ui->label_head2->rect(),QRegion::RegionType::Ellipse));
    //鼠标进入人物姓名的时候需要实现对话框的动态效果
    this->m_exitLoginDlg = new CExitLoginDlg(this);
    this->m_exitLoginDlg->move(this->ui->label_name->x(),this->ui->label->height()+1);
    this->m_exitLoginDlg->hide();
    this->ui->label_name->installEventFilter(this);
    this->m_exitLoginDlg->installEventFilter(this);
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
    delete ui;
}
