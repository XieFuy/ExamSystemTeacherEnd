#ifndef EXITLOGINDLG_H
#define EXITLOGINDLG_H

#include <QDialog>

namespace Ui {
class CExitLoginDlg;
}

class CExitLoginDlg : public QDialog //退出登录按钮
{
    Q_OBJECT

public:
    explicit CExitLoginDlg(QWidget *parent = nullptr);
    ~CExitLoginDlg();

private:
    Ui::CExitLoginDlg *ui;
};

#endif // EXITLOGINDLG_H
