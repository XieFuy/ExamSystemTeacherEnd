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
}

Widget::~Widget()
{
    delete ui;
}

