#ifndef REGISTERDLG_H
#define REGISTERDLG_H

#include <QDialog>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>
#include <QMessageBox>
#include <registercontorller.h>
namespace Ui {
class RegisterDlg;
}

class RegisterDlg : public QDialog  //注册界面类
{
    Q_OBJECT
private:

public slots:
    void onAcountChange(QString str); //检查输入账号格式
    void onPasswordChange(QString str); //检查输入密码格式
    void onRightPasswordChange(QString str);//检查输入确认密码格式
    void checkRegisterInfo(); //对注册信息进行检查，如果正确则进行注册操作
private:
    bool m_isAcountOk;//账号验证通过
    bool m_isPasswordOK;//密码验证通过
    bool m_isRightPasswordOk;//确认密码验证通过
    QRegularExpression reAacount;
    QRegularExpression rePassword;
    CRegisterContorller* m_registerContorller = nullptr;
public:
    explicit RegisterDlg(QWidget *parent = nullptr);
    ~RegisterDlg();
private:
    Ui::RegisterDlg *ui;
};

#endif // REGISTERDLG_H
