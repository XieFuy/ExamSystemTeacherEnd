#ifndef MAINMENUEDLG_H
#define MAINMENUEDLG_H

#include <QDialog>
#include <QIcon>
#include "exitlogindlg.h"
#include <QDebug>
#include <QTreeWidgetItem>
#include <QList>
#include "mainmenuecontorller.h"
#include <vector>
#include <string>
#include <iostream>
#include "clientsocket.h"
#include "namechangedlg.h"
#include "phonenumberchangedlg.h"
#include <QFileDialog>
#include "testpapersavedlg.h"
#include <QCheckBox>
#include <QLabel>
#include <QHBoxLayout>
#include "threadpool.h"

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
    void setLoginedAcount(QString acount); //设置已经登录的账号
signals:
    void startInitTeacherInfoTable();
    void startShowTeacherInfo(QString acount);
    void startShowHeadImage(QImage image);
    void startInitSingleChoiceTable();
    void startInitMultiChoiceTable();
    void startInitJudgeTable();
    void startInitShortAnswerTable();
    void startInitTestPaperTable();
    void startInitTestPaperTableContorl();
    void startShowPageIndex();
    void startShowCurPageIndexTable(QVector<QVector<QString>>* ret);
    void startShowTeacherAcountInfo(std::vector<std::vector<std::string>>* ret);
private:
    CExitLoginDlg* m_exitLoginDlg = nullptr;
    QTreeWidgetItem* m_signalOperator = nullptr; //单选题父项
    QTreeWidgetItem* m_multiOerator = nullptr;//多选题父项
    QTreeWidgetItem* m_judge = nullptr;//判断题父项
    QTreeWidgetItem* m_ShortAnswer = nullptr; //简答题父项
    QList<QTreeWidgetItem*> m_signalOperatorLst; //添加单选子项的容器
    int signalCount; //表示一份试卷的单选题数
    QMap<QString,int> m_signalMap; //作用就是根据题号映射整型题号
    QList<QTreeWidgetItem*> m_multiOeratorLst;//添加多选子项的容器
    int multiCount;//表示一份试卷多选的题数
    QMap<QString,int> m_multiMap;
    QList<QTreeWidgetItem*> m_judgeLst;//判断题子项容器
    int judgeCount;//表示一份试卷的判断题数
    QMap<QString,int> m_judgeMap;
    QList<QTreeWidgetItem*> m_ShortAnswerLst;//简答题容器
    int shortAnswerCount;//表示一份书卷的简答题题数
    QMap<QString,int> m_shortAnswerMap;
    CMainMenueContorller* m_mainMenueContorller = nullptr; //主菜单页面控制层
    QString m_acount; // 存储当前正在登录的用户账号
    std::string m_headPath; //用于存储用户登录的请求头像路径
    CNameChangeDlg* m_nameChangeDlg = nullptr; //修改姓名信息对话框
    CPhoneNumberChangeDlg* m_phoneNumChangeDlg = nullptr;//修改电话对话框
    HANDLE m_recvHeadThead; //接收头像信息的线程
    QString m_signalCorrectOptions;
    QString m_multiCorrectOptions;
    QString m_judgeAnswer;
    CTestPaperSaveDlg* m_testPaperSaveDlg = nullptr;
    QString m_pageCount; //表示查询结果的页数
    int curPageIndex; //表示当前页
    int sortNUmber;//试卷表的序号
    QVector<QWidget*> m_checkVec;//表示一整个列的复选框
    QVector<QLabel*> m_testPaperName;//表示试卷名称
    QVector<QLabel*> m_testPaperCount;//题量
    QVector<QLabel*> m_createTime;//创建时间
    QVector<QLabel*> m_creater;//出卷人
    QVector<QLabel*> m_status;//发布状态
    QVector<QWidget*> m_operators; //操作
private:
    void showPageIndex();//显示分页查询的下标页
    void initTableWidgetHeader(); //初始化表头
    void clearTreeItemSignal();
    void clearTreeItemMulti();
    void clearTreeItemJudge();
    void clearTreeItemShortAnswer();

    void initSingleChoiceTable();//初始化单选表
    static unsigned WINAPI threadInitSingleChoiceTableEntry(LPVOID arg);

    void initMultiChoiceTable();//初始化多选表
    static unsigned WINAPI threadInitMultiChoiceTableEntry(LPVOID arg);

    void initJudgeTable(); //初始化判断表
    static unsigned WINAPI threadInitJudgeTableEntry(LPVOID arg);

    void initShortAnswerTable(); //初始化简答题表
    static unsigned WINAPI threadInitShortAnswerTableEntry(LPVOID arg);

    void initTestPaperTable();//初始化试卷表
    static unsigned WINAPI threadInitTestPaperTableEntry(LPVOID arg);

    void initTeacherInfoTable(); //初始化教职工信息数据库表
    static unsigned WINAPI threadInitTeacherInfoTableEntry(LPVOID arg);

    void  showTeacherInfo(QString acount); //显示主页的职工个人姓名和头像
    void clearTestPaperTableContorl(); //清除表格内容
    void initTestPaperTableContorl();//初始化试卷表格控件
    static unsigned WINAPI threadShowHeadEntry(LPVOID arg); //进行与服务器进行网络通信获取头像数据的线程函数
    void threadShowHead(); //执行向服务器的网络请求头像数据线程函数
    void showHeadImageUI(QImage image); //从服务器中请求到数据后进行UI更新

    void showTeacherAcountInfo(std::vector<std::vector<std::string>>* ret);//显示职工账号管理信息
    void getTeacherAcountInfoData();//获取职工账号信息数据
    static unsigned WINAPI threadGetTeacherAcountInfoDataEntry(LPVOID arg);

    void changeGender(bool isChecked); //进行更改性别
    static unsigned WINAPI threadChangeGenderEntry(LPVOID arg);

    void headPictureChange();//进行头像更换
    void deleteAllTreeItems(QTreeWidget* treeWidget);
    void deleteTreeItemRecursively(QTreeWidgetItem* item);

    void addSignalChoiceInfo(QString grade,QString question,QString sessionA,QString sessionB,QString sessionC,QString sessionD,QString correctOptions,int order);//添加单选题信息
    static unsigned WINAPI threadAddSignalChoiceInfoEntry(LPVOID arg);


    void clearSignalOption();//清空单选区域
    void clearMultiOption();//清空多选区域

    void addMultiChoiceInfo(QString grade,QString question,QString sessionA,QString sessionB,QString sessionC,QString sessionD,QString sessionE,QString sessionF,QString correctOpetions,int order);
    static unsigned WINAPI threadAddMultiChoiceInfoEntry(LPVOID arg);

    void addJudgeInfo(QString grade,QString question,QString sessionTrue,QString sessionFalse,QString correctAnswer,int order); //添加判断题
    static unsigned WINAPI threadAddJudgeInfoEntry(LPVOID arg);

    void clearJudge(); //判断题清空

    void addShortAnswerInfo(QString grade,QString question,QString referenceAnswer,int order);
    static unsigned WINAPI threadAddShortAnswerInfoEntry(LPVOID arg);

    void clearShortAnswer();//清空简答题

    void getTablePageCount(); //获取数据库中试卷表中的总的页数
    static unsigned WINAPI threadGetTablePageCountEntry(LPVOID arg);

    void getCurPageIndexTableData();
    static unsigned WINAPI threadGetCurPageIndexTableData(LPVOID arg);

    void showCurPageIndexTable(QVector<QVector<QString>>* ret);//显示处于当前页表的查询记录,用于更新UI

    void showNextPageIndexTable(); //显示下一页的页表查询记录，更新UI

    void showLastPageIndexTable();//显示上一页的页表查询记录，更新UI

    void getCurPageIndexTableDataPubulished(); //获取状态为已发布的试卷的记录
    static unsigned WINAPI threadGetCurPageIndexTableDataPubulishedEntry(LPVOID arg);

    void getCurPageIndexTableDataNotPubulished();//获取状态为未发布的试卷的记录
    static unsigned WINAPI threadGetCurPageIndexTableDataNotPubulishedEntry(LPVOID arg);

private:
    Ui::CMainMenueDlg *ui;
};

#endif // MAINMENUEDLG_H
