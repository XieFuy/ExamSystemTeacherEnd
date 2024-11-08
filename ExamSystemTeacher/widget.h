#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QRegularExpressionMatch>
#include <QMessageBox>
#include "logincontorller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget //该界面为教职工登录界面
{
    Q_OBJECT
signals:
    void initTeacherDatabase();
    void initTeacherTable();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void onAccountChange(QString str);//账号输入改变
    void onPasswordChange(QString str);//密码输入改变
private:
    void login(); //登录函数
private:
    QRegularExpression reAacount;
    QRegularExpression rePassword;
    bool m_isAcountOk;
    bool m_isPasswordOk;
    CLoginContorller* m_loginContorller = nullptr;
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
