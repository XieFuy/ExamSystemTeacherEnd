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
    static unsigned WINAPI threadDeleteTestPaperRelease(LPVOID arg);
    bool deleteMultiClickBtn(QString acount,QList<QString> createTimeLst,QList<QString>& testPaperIdLst);
    bool initClassTableDatabase();
    std::vector<std::vector<std::string>> getClassTableData(QString acount,int curPageIndex);
    int getClassTableCount(QString acount);
    bool deleteClassInfoByDateTime(QString acount,QString createTime,QString className);
    bool deleteMultiClassInfo(QString acount,QList<QString>& createTimeLst,QList<QString>& classNameLst);
    static unsigned WINAPI threadDeleteMultiClassInfo(LPVOID arg);
    std::vector<std::vector<std::string>> showClassIconInStudentRequest(QString acount,QString className);
    bool initStudentRequestDataBaseTable();
    std::vector<std::vector<std::string>> getStudentRequestTableData(QString className,QString acount,int curIndex);
    int getStudentRequestTableCount(QString acount,QString className,int curIndex);
    std::vector<std::vector<std::string>> getStudentRequestByStudentName(QString acount
                                                                         ,QString className
                                                                         ,int curIndex,QString studentName);
    int getStudentRequestByStudentNameCount(QString acount,QString className,QString studentName);
    std::vector<std::vector<std::string>> getStudentRequestByStudentId(QString acount
                                                                       ,QString className
                                                                       ,int curIndex,QString studentId);
   int getStudentRequestByStudentIdCount(QString acount,QString className,QString studentId);
   std::vector<std::vector<std::string>> getStudentRequestByRequestTime(QString acount
                                                                        ,QString className
                                                                        ,int curIndex,QString requestTime);
   int getStudentRequestByRequestTimeCount(QString acount,QString className,QString requestTime);
   bool agreeStudentRequestByStudentId(QString acount,QString className,QString studentId);
   bool initJoinClassStudentManeageTable();
   bool degreeStudentRequestByStudentId(QString acount,QString className,QString studentId);
   bool agreeMultiRequestByStudentId(QString acount,QString className,QList<QString>* studentIdLst);
   static unsigned WINAPI threadAgreeMultiRequestByStudentId(LPVOID arg);
   bool degreeMultiRequestByStudentId(QString acount,QString className,QList<QString>* studentIdLst);
   static unsigned WINAPI threadDegreeMultiRequestByStudentId(LPVOID arg);
   std::vector<std::vector<std::string>>  showClassIconInStudentManeger(QString acount
                                                                        ,QString className);
   int getStudentMenberCountData(QString acount,QString className);
   std::vector<std::vector<std::string>> getStudentManegerCurPageData(QString acount
                                                                      ,QString className
                                                                      ,int curIndex);
   int getStudentManegerTableCount(QString acount,QString className);
   bool deleteStudentManegerByStudentId(QString acount,QString className,QString studentId);
   bool deleteMultiManegerByStudentId(QString acount,QString className,QList<QString>* studentIdLst);
   static unsigned WINAPI threadDeleteMultiManegerByStudentId(LPVOID arg);
   std::vector<std::vector<std::string>> getStudentManegerCurPageDataByStudentName(QString acount
                                                                                   ,QString className
                                                                                   ,QString studentName
                                                                                   ,int curIndex);
   int getStudentManegerTableCountByStudentName(QString acount,QString className,QString studentName);
   bool initDataBaseTestPaperReleaseTable();
   bool updateTestPaperStatus(QString acount,QString testPaperName);
   bool deleteTestPaperReleaseInfo(QString acount,QString testPaperName);
   bool initStudentAnswerSingaleTable();
   bool initStudentAnswerMultiTable();
   bool initStudentAnswerJudgeTable();
   bool initStudentAnswerShortAnswerTable();
   bool initCommitTestPaperTable();
   std::vector<std::vector<std::string>> getCurPageIndexCorrect(QString teacherId,int curIndex);
   int  getCorrectTestPaperCount(QString& teacherId);
   std::vector<std::vector<std::string>> getCorrectTestPaperDataByName(QString& teacherId
                                                                       ,QString& testPaperName,int& curIndex);
   int getCorrectTestPaperCountByName(QString& teacherId,QString& testPaperName);
   bool initCorrectShortAnswerTable();
   bool deleteSignalAnswer(QString& teacherId,QString& testPaperName);
   bool deleteMultiAnswer(QString& teacherId,QString& testPaperName);
   bool deleteJudgeAnswer(QString& teacherId,QString& testPaperName);
   bool deleteShortAnswer(QString& teacherId,QString& testPaperName);
   bool  deleteCorrectShortAnswer(QString& teacherId,QString& testPaperName);
   bool deleteTestPaperCommitInfo(QString& teacherId,QString& testPaperName);
   std::vector<std::vector<std::string>> getCurPageCorrectMember(QString& testPaperName,QString& teacherId
                                                                 ,int& classId,int& testPaperId,int& curIndex);
   int getCorrectMemberCount(QString& testPaperName,QString& teacherId
                             ,int& classId,int& testPaperId);
 private:
    CMainMenueModel* m_mainMenueModel = nullptr;
};

#endif // CMAINMENUECONTORLLER_H
