#ifndef REGISTERDLG_H
#define REGISTERDLG_H

#include <QDialog>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>
namespace Ui {
class RegisterDlg;
}

class RegisterDlg : public QDialog  //注册界面类
{
    Q_OBJECT
private:
    void onAcountChange(QString str); //检查输入账号格式
    void onPasswordChange(QString str); //检查输入密码格式
    void onRightPasswordChange(QString str);//检查输入确认密码格式
private:
    QRegularExpression reAacount;
    QRegularExpression rePassword;
public:
    explicit RegisterDlg(QWidget *parent = nullptr);
    ~RegisterDlg();
private:
    Ui::RegisterDlg *ui;
};

#endif // REGISTERDLG_H
