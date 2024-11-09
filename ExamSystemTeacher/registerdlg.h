#ifndef REGISTERDLG_H
#define REGISTERDLG_H

#include <QDialog>

namespace Ui {
class RegisterDlg;
}

class RegisterDlg : public QDialog  //注册界面类
{
    Q_OBJECT

public:
    explicit RegisterDlg(QWidget *parent = nullptr);
    ~RegisterDlg();
private:
    Ui::RegisterDlg *ui;
};

#endif // REGISTERDLG_H
