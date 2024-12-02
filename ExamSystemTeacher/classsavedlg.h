#ifndef CLASSSAVEDLG_H
#define CLASSSAVEDLG_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include "clientsocket.h"
#include "DBHelper.h"

namespace Ui {
class CClassSaveDlg;
}

class CClassSaveDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CClassSaveDlg(QWidget *parent = nullptr);
    ~CClassSaveDlg();
    QString filePath; //文件全路径
    QString fileName;//文件名称
    QString acount;//登录者的账号
    void upLoadFile(QString filePath);
    static  unsigned WINAPI threadUpLoadFile(LPVOID arg);

    void addClassInfo();
    static unsigned WINAPI threadAddClassInfo(LPVOID arg);
    HANDLE m_mutex;
private:
    Ui::CClassSaveDlg *ui;
};

#endif // CLASSSAVEDLG_H
