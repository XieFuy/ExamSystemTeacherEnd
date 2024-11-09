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
    this->ui->label_2->setVisible(false);
    this->ui->label_4->setVisible(false);
    this->ui->label_6->setVisible(false);
}

RegisterDlg::~RegisterDlg()
{
    delete ui;
}
