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
#include "classsavedlg.h"
#include "testpaperreleasedlg.h"
#include "previewtestpaperdlg.h"
#include "correctsubjectivequestionsdlg.h"
#include "xlsxdocument.h"
#include <QFileDialog>
#include "bar_widget.h"
#include <QAxObject>
#include <QRegularExpression>
#include <QProcess>
namespace Ui {
class CMainMenueDlg;  //主菜单管理页面
}

// 题目结构体（仅处理三种题型）
/*typedef struct question {
    QString type;       // "单选题"/"多选题"/"判断题"
    QString content;    // 题目正文 （可能包含换行符）
    QStringList options; // 选项（仅选择题）
    QStringList answers; // 正确答案（选择题为选项字母，判断题为"对"/"错"）
    double score = 0.0;  // 分值
}Question;*/

class Question {
public:
    QString type;       // 题型：单选题/多选题/判断题
    QString stem;       // 题干
    double score;       // 分数
    QStringList options;// 选项列表（判断题的选项为["对", "错"]）
    QString answer;     // 答案（如 "B"、"B,C"、"1"）
    Question() : score(0.0) {}
};

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
    void startShowStudentRequestTableUI(QVector<QVector<QString>>* ret);
    void startShowCurPageIndexTable(QVector<QVector<QString>>* ret);
    void startShowTeacherAcountInfo(std::vector<std::vector<std::string>>* ret);
    void startShowClassTable(QVector<QVector<QString>>* ret);
    void startInitClassTable(); //初始化课程表信号
    void startShowClassIcon(QImage* image);
    void startGetClassTableInfo();
    void startGetClassTableIndex();
    void startShowClassTableIndex(); //显示课程表页数信号
    void startShowClassIconInStudentRequest(QImage* image);//显示课程详情图标
    void startInitStudentRequestDataBaseTable();
    void startGetStudentRequestTableData();
    void startShowStudentRequestIndexUI();
    void startGetStudentRequestCount();
    void startInitJoinClassStudentManeageTable();
    void startShowClassIconInStudentManagerUI(QImage* image);
    void startShowStudentHeadIconUI(QImage* image);
    void startShowStudentManegerCurPagaUI(QVector<QVector<QString>>* ret);
    void startShowStudentManegerTableIndex();
    void startShowCorrectTestPaper(QVector<QVector<QString>>* ret);
    void startShowCorrectTestPaperIndex();
    void startShowCorrectMemberUI(QVector<QVector<QString>>* ret);
    void startShowCorrectMemberCount();
    void showEndSignal();
    void startShowTestPaperName(QVector<QVector<QString>>* ret);
    void startSendStudentScoreCount(int count);
    void startInitStudentScoreContorlUI(int count);
    void startGetStudentScoreInfo();
    void startShowStudentScore(QVector<QVector<QString>>* ret);
private:
    QVector<HANDLE> m_deleteTestPaperThread; //进行删除试卷的线程任务
    CTestPaperReleaseDlg* m_testPaperReleaseDlg = nullptr;
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
    int sortNumberClass;//课程表的序号
    QVector<QWidget*> m_checkVec;//表示一整个列的复选框
    QVector<QLabel*> m_testPaperName;//表示试卷名称
    QVector<QLabel*> m_testPaperCount;//题量
    QVector<QLabel*> m_createTime;//创建时间
    QVector<QLabel*> m_creater;//出卷人
    QVector<QLabel*> m_status;//发布状态
    QVector<QWidget*> m_operators; //操作
    int m_testPaperStatusChoise;//表示试卷管理状态选择的类型
    QMap<QPushButton*,int> m_deleteBtnMap;//用于存储删除按钮映射的行
    QMap<QPushButton*,int> m_updateBtnMap;//用于存储发布按钮映射的行

    //课程表
    QVector<QWidget*> m_classCheckVec;
    QVector<QWidget*> m_classIconVec;
    QVector<QLabel*> m_classNameVec;
    QVector<QLabel*> m_classCreateTimeVec;
    QVector<QLabel*> m_classCreatorVec;
    QVector<QWidget*> m_classOperationsVec;

    CClassSaveDlg* m_classSaveDlg = nullptr;//课程信息输入对话框
    std::string m_ClassIconPath;
    int classIconIndex; //用于显示课程图标的下标
    HANDLE m_Event;
    HANDLE m_Event_2;

    HANDLE m_studentManegerEvent;
    HANDLE m_studentManegerEvent_2;

    int m_classCurPageIndex;//课程表 表示当前的页数
    QString m_classCount;//表示总记录的所有

    QString m_classInfoSelected; //记录点击查看的课程详情的名称

    //学生请求表部分
    int m_sortNumStudentRequest;
    QVector<QWidget*> m_studentRequestCheckVec;
    QVector<QLabel*>  m_studentRequestNameVec;
    QVector<QLabel*>  m_studentRequestStudentIdVec;
    QVector<QLabel*>  m_studentRequestTimeVec;
    QVector<QWidget*> m_studentRequestOpetators;
    int m_curStudentRequestIndex;
    QString m_studentRequestCount;

    //学生管理部分
    int m_sortNumStudentManeger;
    QVector<QWidget*> m_studentManegerCheckVec;
    QVector<QWidget*> m_studentManegerHeadIconVec;
    QVector<QLabel*>  m_studentManagerStudentNameVec;
    QVector<QLabel*>  m_studentManagerStudentIdVec;
    QVector<QLabel*>  m_studentManegerPhoneNumberVec;
    QVector<QLabel*>  m_studentManegerJoinTimeVec;
    QVector<QWidget*> m_studentManegerOperators;
    int m_studentManegerCurPageIndex;
    int m_studentManegerClassIconIndex;
    std::string m_studentManegerHeadIconPath;
    QString m_studentManegerCount;

    //试卷预览
    CPreviewTestPaperDlg* m_previewTestPaper = nullptr;

    QVector<QString> m_teacherIdVec; //用于存储获取试卷信息时查询到的教师Id
    QVector<QString> m_testPaperIdVec;//用于存储获取试卷信息时查询到的试卷iD

    //待批改模块
    QVector<QLabel*> m_correctTestPaperName;
    QVector<QLabel*> m_corrected;
    QVector<QLabel*> m_notCorrected;
    QVector<QWidget*> m_correctOprator;
    int curPageIndexCorrect;

    QString strSignalLabelStyleSheet; //单数行的label表格样式字符串
    QString strSignalWidgetStyleSheet; //单数行的widget表格样式字符串

    QString strDoubleLabelStyleSheet; //双数行的表格样式字符串
    QString strDoubleWidgetStyleSheet; //双数行的widget表格样式字符串

    QString m_correctTestPaperCount;

    QVector<int> m_correctTestPaperClassIdVec;
    QVector<int> m_correctTestPaperTestPaperIdVec;

    //待批成员模块部分
    QVector<QLabel*> m_correctMemberName;
    QVector<QLabel*> m_correctMemberSubject;
    QVector<QLabel*> m_correctMemberKeGuan;
    QVector<QLabel*> m_correctMemberZhuGuan;
    QVector<QLabel*> m_correctMemberSum;
    QVector<QWidget*> m_correctMemberOperator;

    int m_correctMemberCurIndex;
    QString m_correctMemberCount;

    QString m_tmpTestPaperName;
    int m_classId;  //表示当前进入批改的科目id
    int m_testPaperId;//表示当前进入批改的试卷id
    QVector<QString> m_correctMemberStudentId;//存储所有的

    //客观题评分界面
    std::shared_ptr<CCorrectSubjectiveQuestionsDlg> m_correctSubjectDlg; //主科对话框


    //学生成绩部分
    QVector<QLabel*> m_studentScoreName;
    QVector<QLabel*> m_studentScoreId;
    QVector<QLabel*> m_studentScoreSubject;
    QVector<QLabel*> m_studentScoreKeGuanScore;
    QVector<QLabel*> m_studentScoreZhuGuanScore;
    QVector<QLabel*> m_studentScoreSumScore;

    //矩形图
    std::shared_ptr<BarWidget> barWidget;

    //各区间中的人数
    int zoreToTen;
    int TenToTwoty;
    int twotyToThirty;
    int thirtyToForty;
    int fourtyToFifty;
    int FiftyToSixty;
    int SixtyToSeventy;
    int seventyToEighty;
    int EightToNighty;
    int nightyToHunder;

private:
    void showPageIndex();//显示分页查询的下标页
    void initTableWidgetHeader(); //初始化表头
    void clearTreeItemSignal();
    void clearTreeItemMulti();
    void clearTreeItemJudge();
    void clearTreeItemShortAnswer();

    //初始化学生单选题答题记录表
    void initStudentAnswerSingaleTable();
    static unsigned WINAPI threadInitStudentAnswerSingaleTableEntry(LPVOID arg);

    //初始化学生多选题答题记录表
    void initStudentAnswerMultiTable();
    static unsigned WINAPI threadInitStudentAnswerMultiTableEntry(LPVOID arg);

    //初始化学生判断题答题记录表
    void initStudentAnswerJudgeTable();
    static unsigned WINAPI threadInitStudentAnswerJudgeTableEntry(LPVOID arg);

    //初始化学生简答题答题记录表
    void initStudentAnswerShortAnswerTable();
    static unsigned WINAPI threadInitStudentAnswerShortAnswerTableEntry(LPVOID arg);

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

    void showTeacherInfo(QString acount); //显示主页的职工个人姓名和头像
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

    void getTablePageCountPublished();//获取查询结果为已发布的总数
    static unsigned WINAPI threadGetTablePageCountPublishedEntry(LPVOID arg);

    void getTablePageCountNotPublished();//获取查询结果为未发布的总数
    static unsigned WINAPI threadGetTablePageCountNotPublishedEntry(LPVOID arg);

    void getTableDataByFindTestNameCount(); //获取模糊查询的结果的条数
    static unsigned WINAPI threadGetTableDataByFindTestNameCountEntry(LPVOID arg);

    void getCurPageIndexTableData();
    static unsigned WINAPI threadGetCurPageIndexTableData(LPVOID arg);

    void showCurPageIndexTable(QVector<QVector<QString>>* ret);//显示处于当前页表的查询记录,用于更新UI

    void showNextPageIndexTable(); //显示下一页的页表查询记录，更新UI

    void showLastPageIndexTable();//显示上一页的页表查询记录，更新UI

    void getCurPageIndexTableDataPubulished(); //获取状态为已发布的试卷的记录
    static unsigned WINAPI threadGetCurPageIndexTableDataPubulishedEntry(LPVOID arg);

    void getCurPageIndexTableDataNotPubulished();//获取状态为未发布的试卷的记录
    static unsigned WINAPI threadGetCurPageIndexTableDataNotPubulishedEntry(LPVOID arg);

    void getTableDataByFindTestName();//根据试卷的名称进行模糊查询
    static unsigned WINAPI threadGetTableDataByFindTestNameEntry(LPVOID arg);

    //删除点击删除的记录
    void deleteClickBtn(int row);
    static unsigned WINAPI threadDeleteClickBtnEntry(LPVOID arg);

    // 更改点击发布的记录
    void updateStatusClickBtn(int row);
    static unsigned WINAPI threadUpdateStatusClickBtn(LPVOID arg);

    //给所有的操作按钮进行信号槽的绑定
    void bindOperatorBtns();

    //删除指定的试卷的发布信息
    void deleteTestPaperReleaseInfo(QString testPaperName);
    static unsigned WINAPI threadDeleteTestPaperReleaseInfo(LPVOID arg);

    //删除试卷的单选题的答题记录表
    void deleteSignalAnswer(QString testPaperName);
    static unsigned WINAPI threadDeleteSignalAnswer(LPVOID arg);
    //删除试卷的多选题的答题记录表
    void deleteMultiAnswer(QString testPaperName);
    static unsigned WINAPI threadDeleteMultiAnswer(LPVOID arg);
    //删除试卷的判断题的答题记录表
    void deleteJudgeAnswer(QString testPaperName);
    static unsigned WINAPI threadDeleteJudgeAnswer(LPVOID arg);
    //删除试卷的简答题的答题记录表
    void deleteShortAnswer(QString testPaperName);
    static unsigned WINAPI threadDeleteShortAnswer(LPVOID arg);
    //删除试卷的简答题的评分记录表
    void deleteCorrectShortAnswer(QString testPaperName);
    static unsigned WINAPI threadDeleteCorrectShortAnswer(LPVOID arg);

    //删除该份试卷的提交记录  明天接着继续
    void deleteTestPaperCommitInfo(QString testPaperName);
    static unsigned WINAPI threadDeleteTestPaperCommitInfo(LPVOID arg);

    //更新试卷状态信息
    void updateTestPaperStatus(QString testPaperName);
    static unsigned WINAPI threadUpdateTestPaperStatus(LPVOID arg);

    //预览点击的试卷
    void previewTestPaper(int row);

    //将当前页的所有选项进行设置状态
    void changeCurPageCheckBoxStatus(bool status);

    //下面四个函数通常配合 deleteClickBtn函数 ，删除试卷表记录使用
    //从单选题库中删除指定的题
    void deleteFromSignalChoise(QString createTime);
    static unsigned WINAPI threadDeleteFromSignalChoiseEntry(LPVOID arg);
    //从多选题库中删除指定的题
    void deleteFromMultiChoise(QString createTime);
    static unsigned WINAPI threadDeleteFromMultiChoiseEntry(LPVOID arg);
    //从判断题库中删除指定的题
    void deleteFromJudge(QString createTime);
    static unsigned WINAPI threadDeleteFromJudgeEntry(LPVOID arg);
    //从简答题库中删除指定的题
    void deleteFromShortAnswer(QString createTime);
    static unsigned WINAPI threadDeleteFromShortAnswerEntry(LPVOID arg);

    //批量删除当前页被选中的记录
    void deleteMultiClickBtn();
    static unsigned WINAPI threadDeleteMultiClickBtnEntry(LPVOID arg);

    //进行初始化课程表的行高和列宽等
    void initClassTable();

    //进行初始化课程表的每列的控件
    void initClassTableControl();

    //初始化课程数据库表
    void initClassTableDatabase();
    static unsigned WINAPI threadInitClassTableDatabaseEntry(LPVOID arg);

    //获取课程表的数据
    void getClassTableData();
    static unsigned WINAPI threadGetClassTableDataEntry(LPVOID arg);

    //UI显示课程表信息(更新UI)
    void showClassTableInfo(QVector<QVector<QString>>* ret);

    void clearClassTableControl(); //清除课程表UI

    void showClassIconUI(QImage* image);

    void showStudentHeadIconUI(QImage* image);

    static unsigned WINAPI showClassIcon(LPVOID arg);//显示一行的课程图标,这个线程函数进行负责从服务器中进行接收图片数据

    void Dump(const BYTE* Data, size_t nSize);  //打印输出测试设计的包的数据是什么


    void getClassTableCount();//进行获取课程表所有符合条件的总页数
    static unsigned WINAPI threadGetClassTableCountEntry(LPVOID arg);

    void showClassTableIndex(); //用于更新课程表的页数下标

    //拿取课程表的下一页数据
    void showClassTableNextPage(); //显示课程表的下一页

    //拿到课程表的上一页数据
    void showClassTableLastPage();//显示课程表的上一页数据

    //删除课程表单条记录
    void deleteClassInfoByDateTime(int row);//删除课程表的单条记录
    static unsigned WINAPI threadDeleteClassInfoByDateTimeEntry(LPVOID arg);

    //绑定所有课程表的操作按钮的信号槽
    void bindClassOperators();

    //将课程表当前页的所有选项进行设置状态
    void changeClassCurPageCheckBoxStatus(bool status);

    //实现课程表的批量删除
    void deleteMultiClassInfo();
    static unsigned WINAPI threadDeleteMultiClassInfo(LPVOID arg);

    //进行显示学生申请
    void showStudentRequestInfo();

    //显示学生申请的课程图标
    void showClassIconInStudentRequest();
    static unsigned WINAPI threadShowClassIconInStudentRequest(LPVOID arg);

    void showClassIconInStudentRequestUI(QImage* image); //进行UI显示

    //初始化学生申请记录表格UI
    void initStudentRequestTable();

    //初始化学生申请表的控件
    void initStudentRequestTableControl();

    //初始化学生申请数据库表
    void initStudentRequestDataBaseTable();
    static  unsigned WINAPI threadInitStudentRequestDataBaseTableEntry(LPVOID arg);

    //显示对应课程详情的学生申请数据
    void getStudentRequestTableData();
    static unsigned WINAPI threadGetStudentRequestTableDataEntry(LPVOID arg);

    //显示学生申请的记录信息
    void showStudentRequestTableUI(QVector<QVector<QString>>* ret);

    //清除学生申请表的记录UI显示信息
    void clearStudentRequestTableUI();

    //获取学生申请表的总页数
    void getStudentRequestTableCount();
    static unsigned WINAPI threadGetStudentRequestTableCountEntry(LPVOID arg);

    //显示学生申请当前页下标
    void showStudentRequestIndexUI();

    //显示学生申请表的下一页
    void showStudentRequestNextPage();

    //显示学生申请表的上一页
    void showStudentRequestLastPage();

    //根据查询的条件进行对条件进行模糊查询
    void getStudentRequestByCondition();
    static unsigned WINAPI threadGetStudentRequestByCondition(LPVOID arg);

    //根据学生申请姓名进行模糊查询
    void getStudentRequestByStudentName(QString studentName);
    static unsigned WINAPI threadGetStudentRequestByStudentName(LPVOID arg);

    //获取学生申请姓名进行模糊查询的总页数
    void getStudentRequestByStudentNameCount(QString studentName);
    static unsigned WINAPI threadGetStudentRequestByStudentNameCount(LPVOID arg);

    //根据学生姓名进行模糊查询的结果集的下一页操作
    void showStudentRequestByStudentNameNextPage(QString studentName);

    //根据学生姓名进行模糊查询的结果集的上一页操作
    void showStudentRequestByStudentNameLastPage(QString studentName);

    //根据学生申请学号进行模糊查询
    void getStudentRequestByStudentId(QString studentId);
    static unsigned WINAPI threadGetStudentRequestByStudentId(LPVOID arg);

     //获取学生申请进行模糊查询的总页数
    void getStudentRequestByStudentIdCount(QString studentId);
    static unsigned WINAPI threadGetStudentRequestByStudentIdCount(LPVOID arg);

    //根据学生学号进行模糊查询的结果集的下一页操作
    void showStudentRequestByStudentIdNextPage(QString studentId);

     //根据学生学号进行模糊查询的结果集的上一页操作
    void showStudentRequestByStudentIdLastPage(QString studentId);

    //根据申请时间进行模糊查询
    void  getStudentRequestByRequestTime(QString createTime);
    static unsigned WINAPI threadGetStudentRequestByRequestTime(LPVOID arg);

    //获取学生申请时间进行模糊查询的总页数
    void  getStudentRequestByRequestTimeCount(QString createTime);
    static unsigned WINAPI threadGetStudentRequestByRequestTimeCount(LPVOID arg);

    //根据学生申请时间进行模糊查询的结果集的下一页操作
    void showStudentRequestByRequestTimeNextPage(QString createTime);

     //根据学生申请时间进行模糊查询的结果集的上一页操作
    void showStudentRequestByRequestTimeLastPage(QString createTime);

    //学生申请表当前页的所有选项进行设置状态
    void changeStudentRequestCurPageCheckBoxStatus(bool status);

    //绑定所有申请表的操作按钮的信号槽
    void bindStudentRequestOperators();

    //学生申请的同意单条记录
    void agreeStudentRequestByStudentId(int row);
    static unsigned WINAPI threadAgreeStudentRequestByStudentId(LPVOID arg);

    //学生申请的不同意单条记录
    void degreeStudentRequestByStudentId(int row);
    static unsigned WINAPI threadDegreeStudentRequestByStudentId(LPVOID arg);

    void initJoinClassStudentManeageTable();
    static unsigned WINAPI threadInitJoinClassStudentManeageTable(LPVOID arg);

    //批量同意功能
    void agreeMultiRequestByStudentId();
    static unsigned WINAPI threadAgreeMultiRequestByStudentId(LPVOID arg);

    //批量不同意功能
    void degreeMultiRequestByStudentId();
    static unsigned WINAPI threadDegreeMultiRequestByStudentId(LPVOID arg);

    //进行初始化显示学生信息管理页的动态数据信息
    void initStudentInfoManagerData(int index);

    //进行回显学生管理页课程图标
    void showClassIconInStudentManeger();
    static unsigned WINAPI threadShowClassIconInStudentManeger(LPVOID arg);

    void showClassIconInStudentManagerUI(QImage* image); //进行学生信息管理UI显示

    void getStudentMenberCountData(); //获取学生管理总人数
    static unsigned WINAPI threadGetStudentMenberCountData(LPVOID arg);

    //初始化学生管理表格
    void  initStudentManegerTable();

    //初始化学生管理表控件
    void initStudentManegerTableContorl();

    //获取学生管理当前页数据
    void getStudentManegerCurPageData();
    static unsigned WINAPI threadGetStudentManegerCurPageData(LPVOID arg);

    //显示当前页的学生管理数据UI
    void showStudentManegerCurPagaUI(QVector<QVector<QString>>* ret);//TODO:明天接着这个函数继续进行写

    //清除学生管理表UI
    void clearStudentManegerTableUI();

    //显示学生头像
    static unsigned WINAPI  showStudentHeadIcon(LPVOID arg);

    //获取学生管理表的总页数
    void getStudentManegerTableCount();
    static unsigned WINAPI threadGetStudentManegerTableCountEntry(LPVOID arg);

    void showStudentManegerTableIndex(); //显示学生管理总页数下表

    //显示学生管理表的下一页，注意下一页的逻辑，避免bug
    void  showStudentManegerTableNextPage();

    //显示学生管理表的上一页
    void  showStudentManegerTableLastPage();

    void changeStudentManegerCurPageCheckBoxStatus(bool status);

    //完成学生管理操作绑定
    void bindStudentManegerOperators();

    //删除单条学生管理记录
    void deleteStudentManegerByStudentId(QString studentId);
    static unsigned WINAPI threadDeleteStudentManegerByStudentId(LPVOID arg);

    //批量当前页的删除学生管理记录
    void deleteMultiManegerByStudentId();
    static unsigned WINAPI threadDeleteMultiManegerByStudentId(LPVOID arg);

    //根据学生姓名进行模糊查询当前页的结果集
    void getStudentManegerCurPageDataByStudentName(QString studentName);
    static unsigned WINAPI threadGetStudentManegerCurPageDataByStudentName(LPVOID arg);

    //获取学生姓名模糊查询的结果集的总页数
    void getStudentManegerTableCountByStudentName(QString studentName);
    static unsigned WINAPI threadGetStudentManegerTableCountByStudentNameEntry(LPVOID arg);

    //显示学生管理表的姓名模糊查询结果集下一页，注意下一页的逻辑，避免bug
    void  showStudentManegerTableNextPageByStudentName(QString studentName);

    //显示学生管理表的姓名模糊查询结果集的上一页
    void  showStudentManegerTableLastPageByStudentName(QString studentName);

    //初始化数据库试卷发布表
    void initDataBaseTestPaperReleaseTable();
    static unsigned WINAPI threadInitDataBaseTestPaperReleaseTable(LPVOID arg);

    //初始化待改试卷表格UI
    void initCorrectTestPaperTableUI();

    //初始化待批改试卷表格控件
    void initCorrectTestPaperTableContorl();

    //初始化数据库提交表
    void initCommitTestPaperTable();
    static unsigned WINAPI threadInitCommitTestPaperTable(LPVOID arg);

    //获取提交表的当前页的记录
    void getCurPageIndexCorrect(); //获取待批改的表的当前页记录
    static unsigned WINAPI threadGetCurPageIndexCorrect(LPVOID arg);

    //显示批改试卷信息
    void showCorrectTestPaperUI(QVector<QVector<QString>>* ret);

    void clearCorrectTestPaperTable();//清除批改表UI

    //进行获取待批表的总页数
    void getCorrectTestPaperCount();
    static unsigned WINAPI threadGetCorrectTestPaperCount(LPVOID arg);

    void showCorrectTestPaperIndex();

    //试卷待批表的上一页操作
    void showLastCorrectTestPaper();
    //试卷待批表的下一页操作
    void showNextCorrectTestPaper();

    //试卷批改表的模糊查询操作
    void getCorrectTestPaperDataByName(QString testPaperName);
    static unsigned WINAPI threadGetCorrectTestPaperDataByName(LPVOID arg);

    //获取待批表模糊查询结果集的下标总数
    void getCorrectTestPaperCountByName(QString testPaperName);
    static unsigned WINAPI threadGetCorrectTestPaperCountByName(LPVOID arg);

    //实现当进行模糊查询结果集的上一页
    void getCorrectTestPaperLastByName(QString testPaperName);

    //实现当进行模糊查询结果集的下一页
    void getCorrectTestPaperNextByName(QString testPaperName);

    void bindOperatorCorrect();

    //进入批改试卷页面
    void joinCorrectTestPaper(QString testPaperName,QString teacherId,int classId,int testPaperId);

    //批改待批成员表UI
    void initCorrectMemberTableUI();

    //初始化批改人员表控件
    void initCorrectMemberTableContorl();

    //获取当前页待批学生的信息
    void getCurPageCorrectMember(QString testPaperName,int classId,int testPaperId);
    static unsigned WINAPI threadGetCurPageCorrectMember(LPVOID arg);

    //初始化简答题数据库评分表
    void initCorrectShortAnswerTable();
    static unsigned WINAPI threadCorrectShortAnswerTable(LPVOID arg);

    void showCorrectMemberUI(QVector<QVector<QString>>* ret);

    void clearCorrectMemberUI();

    void getCorrectMemberCount(QString testPaperName,int classId,int testPaperId);
    static unsigned WINAPI threadGetCorrectMemberCount(LPVOID arg);

    void showCorrectMemberCount();

    void showLastCorrectMember();

    void showNextCorrectMember();

    void bindCorrectMemberOperator();//进行绑定批改成员

    void joinCorrectSubjectDlg(QString studentName,QString subject,QString testPaperName,QString studentId,int row);//进入到批改对话框界面

    //进行删除简答题批改表记录
    void deleteTestPaperCorrectInfo(QString testPaperName);
    static unsigned WINAPI threadDeleteTestPaperCorrectInfo(LPVOID arg);

    //进行删除学生成绩表记录
    void deleteStudentScoreInfo(QString testPaperName);
    static unsigned WINAPI threadDeleteStudentScoreInfo(LPVOID arg);

    //创建学生成绩数据库表
    void initStudentScoreTable();
    static unsigned WINAPI threadInitStudentScoreTable(LPVOID arg);

    //进行插入学生成绩记录
    void insertStudentScore(QString teacherId,QString studetId,int classId,int testPaperId,double keGuanScore,double zhuGuanScore);
    static unsigned WINAPI threadInsertStudentScore(LPVOID arg);
    //进行更新学生成绩记录
    void updateStudentScore(QString teacherId,QString studetId,int classId,int testPaperId,double keGuanScore,double zhuGuanScore);
    static unsigned WINAPI threadUpdateStudentScore(LPVOID arg);

    //进行获取发布了的试卷绑定科目并且已批改的试卷
    void getSubjectTestPaperRelease();
    static unsigned WINAPI threadGetSubjectTestPaperRelease(LPVOID arg);

    void showTestPaperNameUI(QVector<QVector<QString>>* ret);

    //进行获取该试卷下的所有的学生的记录条数
    void getStudentScoreCount(int testPaperId,HANDLE& out_handle);
    static unsigned WINAPI  threadGetStudentScoreCount(LPVOID arg);

    //进行获取该试卷下的所有学生的成绩
    void getStudentScoreInfo();
    static unsigned WINAPI threadGetStudentScoreInfo(LPVOID arg);

    //设置成绩表UI
    void setStudentScoreContorlUI(int rowCount); //进行设置成绩表UI和控件

    void showStudentScoreUI(QVector<QVector<QString>>* ret); //进行显示查询到的学生信息

    /*Excel表格操作接口*/
    //导出学生成绩
    void writeStudentScoreToExcel();

    //解析读取word文档后的试题函数
    QList<Question> parseQuestions(const QStringList& paragraphs);

    //进行读取word文档
    QStringList readWordDocument(const QString& filePath);

    void finalizeQuestion(Question& question, QList<Question>& questions);
private:
    Ui::CMainMenueDlg *ui;
};

#endif // MAINMENUEDLG_H
