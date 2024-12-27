#ifndef DATETIMESELECTDLG_H
#define DATETIMESELECTDLG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class CDateTimeSelectDlg;
}

class CDateTimeSelectDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CDateTimeSelectDlg(QWidget *parent = nullptr);
    ~CDateTimeSelectDlg();
public:
    QString getDateTime();
public:
    QString strDateTime;
private:
    Ui::CDateTimeSelectDlg *ui;
};

#endif // DATETIMESELECTDLG_H
