#ifndef PREVIEWTESTPAPERDLG_H
#define PREVIEWTESTPAPERDLG_H

#include <QDialog>
#include <QIcon>
#include <QList>
#include <QPushButton>
#include <windows.h>
#include "previewtestpapercontorller.h"

namespace Ui {
class CPreviewTestPaperDlg;
}

class CPreviewTestPaperDlg : public QDialog //试卷预览对话框
{
    Q_OBJECT

public:
    explicit CPreviewTestPaperDlg(QWidget *parent = nullptr);
    ~CPreviewTestPaperDlg();
    void SetAcount(QString acount);
    void SetTestPaperName(QString testPaperName);
signals:
    void startShowMenueBtn(int Count);
    void startShowMultiMenueBtn(int Count);
    void startShowSignalChoice(QVector<QVector<QString>>* ret); //进行
    void startShowMultiChoice(QVector<QVector<QString>>* ret);
private:
    QList<QPushButton*> m_signalChoice; //单选题题号按钮
    QList<QPushButton*> m_multiChoice; //多选题题号按钮
    CPreviewTestPaperContorller* m_contorller = nullptr;
    QString acount;
    QString testPaperName;
    int signalChoiceCurIndex; //当前单选题题号
    int multiChoiceCurIndex; //当前多选题题号
    int signalChoiceCount;
    int multiChoiceCount;
private:
    //获取该份试卷的单选题的总数量  根据试卷名和职工号确定
    void getSignalChoiceCount();
    static unsigned WINAPI threadGetSignalChoiceCount(LPVOID arg);

    //获取该份试卷的多选题的总数量
    void getMultiChoiceCount();
    static unsigned WINAPI threadGetMultiChoiceCount(LPVOID arg);


    void showMenueBtn(int Count);
    void showMultiMenueBtn(int Count);

    void showSignalChoice(QVector<QVector<QString>>* ret);
    void showMultiChoice(QVector<QVector<QString>>* ret);

    //获取当前题号的单选题的内容
    void getCurIndexSignalChoice();
    static unsigned WINAPI  threadGetCurIndexSignalChoice(LPVOID arg);

    //获取当前多选题的内容
    void getCurIndexMultiChoice();
    static unsigned WINAPI threadGetCurIndexMultiChoice(LPVOID arg);


    //点击下一题，进行显示下一题的单选题目
    void getNextSignalChoive();

    //点击上一题，进行显示上一题的单选题目
    void getLastSignalChoice();




private:
    Ui::CPreviewTestPaperDlg *ui;
};

#endif // PREVIEWTESTPAPERDLG_H
