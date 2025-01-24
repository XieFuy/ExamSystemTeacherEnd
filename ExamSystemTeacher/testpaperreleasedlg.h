#ifndef TESTPAPERRELEASEDLG_H
#define TESTPAPERRELEASEDLG_H

#include <QDialog>
#include "windows.h"
#include "DBHelper.h"
#include <memory>
#include <string>
#include <vector>
#include <QDebug>
#include "datetimeselectdlg.h"

namespace Ui {
class CTestPaperReleaseDlg;
}

class CTestPaperReleaseDlg : public QDialog  //考试试卷发布对话框
{
    Q_OBJECT

public:
    explicit CTestPaperReleaseDlg(QWidget *parent = nullptr);
    ~CTestPaperReleaseDlg();
signals:
    void startShowTestPaperName(QString testPaperName);
    void startShowSubject(QVector<QVector<QString>>* ret);
public:
    void SetTestPaperName(QString testPaperName);
    void SetAcount(QString acount);
    void SetClassName(QString className);
private:
    void getClassNameByAcount(); //根据职工账号查询所有加入人数大于0的课程名称
    static unsigned WINAPI threadGetClassNameByAcount(LPVOID arg);
    void showSubject(QVector<QVector<QString>>* ret);
    void addTestPaperReleaseInfo();
    static unsigned WINAPI threadAddTestPaperReleaseInfo(LPVOID arg);

    static unsigned WINAPI threadAddStudentAnswerSignalInfo(LPVOID arg); //进行添加一条学生的单选答题记录
    static unsigned WINAPI threadAddStudentAnswerMultiInfo(LPVOID arg);
    static unsigned WINAPI threadAddStudentAnswerJudgeInfo(LPVOID arg);
    static unsigned WINAPI threadAddStudentAnswerShortAnswerInfo(LPVOID arg);

    static unsigned WINAPI threadGetClassIdEntry(LPVOID arg);
    static unsigned WINAPI threadGetTestPaperIdEntry(LPVOID arg);
    static unsigned WINAPI threadGetStudentIdVectorEntry(LPVOID arg); //获取学生id集合

    static unsigned WINAPI threadGetTestPaperSignalOrderEntry(LPVOID arg);//进行获取某一份试卷的单选题的题号
    static unsigned WINAPI threadGetTestPaperMultiOrderEntry(LPVOID arg);
    static unsigned WINAPI threadGetTestPaperJudgeOrderEntry(LPVOID arg);
    static unsigned WINAPI threadGetTestPaperShortAnswerEntry(LPVOID arg);

private:
    QString acount;
    QString testPaperName;
    CDateTimeSelectDlg* m_dateTimeWid = nullptr;
    QString className;
private:
    Ui::CTestPaperReleaseDlg *ui;
};

#endif // TESTPAPERRELEASEDLG_H
