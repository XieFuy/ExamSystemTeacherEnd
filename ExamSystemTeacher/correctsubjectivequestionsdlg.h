#ifndef CORRECTSUBJECTIVEQUESTIONSDLG_H
#define CORRECTSUBJECTIVEQUESTIONSDLG_H

#include <QDialog>
#include <QDebug>
#include <windows.h>
#include <memory>
#include "correctsubjectivequestionscontorler.h"

namespace Ui {
class CCorrectSubjectiveQuestionsDlg;
}

//主观题批改页对话框
class CCorrectSubjectiveQuestionsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CCorrectSubjectiveQuestionsDlg(QWidget *parent = nullptr);
    ~CCorrectSubjectiveQuestionsDlg();
signals:
    void startShowDlg();
    void startShowShortAnswer(QVector<QVector<QString>>* ret);
    void startShowAnswer(QVector<QVector<QString>>* ret);
    void startShowShortAnswerBtn(int count);
private:
    void getCurOrderShortAnswer(); //获取当前题的
    static unsigned WINAPI threadGetCurOrderShortAnswer(LPVOID arg);

    void showShortAnswerUI(QVector<QVector<QString>>* ret);

    void getCurOrderAnswer();//获取当期题的学生答案
    static unsigned WINAPI threadGetCurOrderAnswer(LPVOID arg);

    void showAnswerUI(QVector<QVector<QString>>* ret);

    //获取当前这份题的题的总数
    void getShoerAnswerCount();
    static unsigned WINAPI threadGetShoerAnswerCount(LPVOID arg);

    void showSHortAnswerBtn(int Count);

    //上一题获取题干、答案
    void getLastShortAnswerChoice();
    //下一题
    void getNextShortAnswerChoice();

private:
    QVector<QPushButton*> m_shortAnswerChoice;
    int order;
    std::shared_ptr<CCorrectSubjectiveQuestionsContorler> m_contorler;
    int count;
public:
    QString testPaperName;
    QString studentName;
    QString subject;

    QString studentId;
    QString teacherId;
    int classId;
    int testPaperId;
private:
    Ui::CCorrectSubjectiveQuestionsDlg *ui;
};

#endif // CORRECTSUBJECTIVEQUESTIONSDLG_H
