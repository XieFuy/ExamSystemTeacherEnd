#include "exitlogindlg.h"
#include "ui_exitlogindlg.h"

CExitLoginDlg::CExitLoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CExitLoginDlg)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint); //去除对话框的标题栏
}

CExitLoginDlg::~CExitLoginDlg()
{
    delete ui;
}
