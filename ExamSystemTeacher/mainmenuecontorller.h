#ifndef CMAINMENUECONTORLLER_H
#define CMAINMENUECONTORLLER_H

#include "mainmenuemodel.h"
#include<vector>
#include<string>
class CMainMenueContorller  //主菜单页面的控制层
{
public:
    CMainMenueContorller();
    ~CMainMenueContorller();
public :
    bool initTeacherInfoTable();
    std::vector<std::vector<std::string>> showTeacherInfo(QString acount);
    std::vector<std::vector<std::string>> showTeacherAcountInfo(QString acount);
    void changeGender(bool isMan,QString pAcount);
    void changeHeadPicture(QString LocalFilePath,QString acount);
    bool initSingleChoiceTable();//初始化单选表
    bool initMultiChoiceTable();//初始化多选表
    bool initJudgeTable(); //初始化判断表
    bool initShortAnswerTable(); //初始化简答题表
    bool initTestPaperTable();
    bool addSignalChoiceInfo(QString grade,QString question,QString sessionA,
                             QString sessionB,QString sessionC,QString sessionD,
                             QString correctOptions,int order);
    bool addMultiChoiceInfo(QString grade,QString question,QString sessionA,
                            QString sessionB,QString sessionC,QString sessionD,
                            QString sessionE,QString sessionF,QString correctOpetions,int order);
    bool addJudgeInfo(QString grade,QString question,QString sessionTrue,QString sessionFalse,
                      QString correctAnswer,int order);
    bool addShortAnswerInfo(QString grade,QString question,QString referenceAnswer,int order);
    QString getTablePageCount(QString acount);
    std::vector<std::vector<std::string>> showCurPageIndexTable(int curPageIndex,QString acount);
    std::vector<std::vector<std::string>> getCurPageIndexTableDataPubulished(int curPageIndex,
                                                                             QString acount,
                                                                             QString status);
    int getTablePageCountPublished(QString acount,QString status);
    std::vector<std::vector<std::string>> getCurPageIndexTableDataNotPubulished(int curPageIndex,
                                                                                QString acount,
                                                                                QString status);
    int getTablePageCountNotPublished(QString acount,QString status);
    std::vector<std::vector<std::string>> getTableDataByFindTestName(int curPageIndex,
                                                                     QString acount,
                                                                     QString testPaperName);

    int  getTableDataByFindTestNameCount(QString acount,QString testPaperName);
    bool deleteClickBtn(QString acount,QString createTime);

    bool deleteFromSignalChoise(QString acount,QString createTime);
    static unsigned WINAPI threadDeleteFromSignalChoise(LPVOID arg);
    bool deleteFromMultiChoise(QString acount,QString createTime);
    static unsigned WINAPI threadDeleteFromMultiChoise(LPVOID arg);
    bool deleteFromJudge(QString acount,QString createTime);
    static unsigned WINAPI threadDeleteFromJudge(LPVOID arg);
    bool deleteFromShortAnswer(QString acount,QString createTime);
    static unsigned WINAPI threadDeleteFromShortAnswer(LPVOID arg);
    bool deleteMultiClickBtn(QString acount,QList<QString> createTimeLst);
    bool initClassTableDatabase();
 private:
    CMainMenueModel* m_mainMenueModel = nullptr;
};

#endif // CMAINMENUECONTORLLER_H
