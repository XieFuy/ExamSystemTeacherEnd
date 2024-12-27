#include "datetimeselectdlg.h"
#include "ui_datetimeselectdlg.h"


CDateTimeSelectDlg::CDateTimeSelectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDateTimeSelectDlg)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        this->strDateTime = "";
        QDate selectedDate = this->ui->calendarWidget->selectedDate();
        if (selectedDate.isValid()) {
           this->strDateTime = selectedDate.toString("yyyy-MM-dd");
        }

        this->strDateTime += " ";
        QTime selectedTime = this->ui->timeEdit->time();
        this->strDateTime += selectedTime.toString("HH:mm:ss");
        qDebug()<<"dateTime: "<<CDateTimeSelectDlg::strDateTime;
        this->reject();     
    });
}

QString CDateTimeSelectDlg::getDateTime()
{
    return this->strDateTime;
}

CDateTimeSelectDlg::~CDateTimeSelectDlg()
{
    delete ui;
}
