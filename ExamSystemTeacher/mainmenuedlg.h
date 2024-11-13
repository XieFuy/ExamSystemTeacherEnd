#ifndef MAINMENUEDLG_H
#define MAINMENUEDLG_H

#include <QDialog>
#include <QIcon>
#include "exitlogindlg.h"
#include <QDebug>
#include <QTreeWidgetItem>
#include <QList>
#include "mainmenuecontorller.h"

namespace Ui {
class CMainMenueDlg;  //主菜单管理页面
}

class CMainMenueDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CMainMenueDlg(QWidget *parent = nullptr);
    ~CMainMenueDlg();
public:
    bool eventFilter (QObject* obj, QEvent* e) override;
    int count;
signals:
    void startInitTeacherInfoTable();
    void startShowTeacherInfo();
private:
    CExitLoginDlg* m_exitLoginDlg = nullptr;
    QTreeWidgetItem* m_signalOperator = nullptr; //单选题父项
    QTreeWidgetItem* m_multiOerator = nullptr;//多选题父项
    QTreeWidgetItem* m_judge = nullptr;//判断题父项
    QTreeWidgetItem* m_ShortAnswer = nullptr; //简答题父项
    QList<QTreeWidgetItem*> m_signalOperatorLst; //添加单选子项的容器
    QList<QTreeWidgetItem*> m_multiOeratorLst;//添加多选子项的容器
    QList<QTreeWidgetItem*> m_judgeLst;//判断题子项容器
    QList<QTreeWidgetItem*> m_ShortAnswerLst;//简答题容器
    CMainMenueContorller* m_mainMenueContorller = nullptr; //主菜单页面控制层
private:
    void initTeacherInfoTable(); //初始化教职工信息数据库表
    void  showTeacherInfo(); //显示主页的职工个人信息
private:
    Ui::CMainMenueDlg *ui;
};

#endif // MAINMENUEDLG_H
