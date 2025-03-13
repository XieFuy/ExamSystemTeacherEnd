#ifndef CMAINMENUEMODEL_H
#define CMAINMENUEMODEL_H

#include "DBHelper.h"
#include <string>
#include <QString>
#include <QDebug>
#include "clientsocket.h"
#include <stdlib.h>
#include <memory>
class CMainMenueModel //主菜单页面模型层
{
public:
    CMainMenueModel();
    ~CMainMenueModel();
public:
    bool initTeacherInfoTable();
    std::vector<std::vector<std::string>> showTeacherInfo(char* pAcount);
    std::vector<std::vector<std::string>> showTeacherAcountInfo(char* pAcount);
    void changeGender(bool isMan,char* pAcount);
    void changeHeadPicture(char* localFilePath,char* fileName,char* acount);
    bool initSingleChoiceTable();
    bool initMultiChoiceTable();
    bool initJudgeTable();
    bool initShortAnswerTable();
    bool initTestPaperTable();
    bool addSignalChoiceInfo(double grade,const char* question,const char* sessionA,
                             const char* sessionB,const char* sessionC,const char* sessionD,
                             const char* correctOptions,int order);
    bool addMultiChoiceInfo(double grade,const char* question,const char* sessionA,
                            const char* sessionB,const char* sessionC,const char* sessionD,
                            const char* sessionE,const char* sessionF,const char* correctOpetions,
                            int order);
    bool addJudgeInfo(double grade,const char* question,const char* sessionTrue,
                      const char* sessionFalse,
                      const char* correctAnswer,int order);
    bool addShortAnswerInfo(double grade,const char* question,const char* referenceAnswer,int order);
    QString getTablePageCount(char* acount);
    std::vector<std::vector<std::string>> showCurPageIndexTable(int curPageIndex,char* acount);
    std::vector<std::vector<std::string>> getCurPageIndexTableDataPubulished(int curPageIndex,
                                                                             const char* acount,
                                                                             const char* status);
    int getTablePageCountPublished(const char* acount,const char* status);
    std::vector<std::vector<std::string>> getCurPageIndexTableDataNotPubulished(int curPageIndex
                                                                                ,const char* acount
                                                                                ,const char* status);
    int getTablePageCountNotPublished(const char* acount,const char* status);
    std::vector<std::vector<std::string>> getTableDataByFindTestName(int curPageIndex,
                                                                     const char* acount,
                                                                     const char* testPaperName);
    int getTableDataByFindTestNameCount(const char* acount,const char* testPaperName);
    bool deleteClickBtn(const char* acount,const char* createTime);
    bool deleteFromSignalChoise(const char* acount,const char* createTime);
    bool deleteFromMultiChoise(const char* acount,const char* createTime);
    bool deleteFromJudge(const char* acount,const char* createTime);
    bool deleteFromShortAnswer(const char* acount,const char* createTime);
    bool initClassTableDatabase();
    std::vector<std::vector<std::string>> getClassTableData(const char* acount,int curPageIndex);
    int getClassTableCount(const char* acount);
    bool deleteClassInfoByDateTime(const char* acount,const char* createTime,const char* className);
    std::vector<std::vector<std::string>> showClassIconInStudentRequest(const char* acount,
                                                                        const char* className);
    bool initStudentRequestDataBaseTable();
    std::vector<std::vector<std::string>> getStudentRequestTableData(const char* className
                                                                     ,const char* acount,
                                                                     int curIndex);
    int getStudentRequestTableCount(const char* acount,const char* className,int curIndex);
    std::vector<std::vector<std::string>> getStudentRequestByStudentName(const char* acount
                                                                         ,const char* className
                                                                         ,int curIndex,const char* studentName);
    int getStudentRequestByStudentNameCount(const char* acount,const char* className,const char* studentName);
    std::vector<std::vector<std::string>> getStudentRequestByStudentId(const char* acount
                                                                       ,const char* className
                                                                       ,int curIndex,const char* studentId);
    int getStudentRequestByStudentIdCount(const char* acount,const char* className,const char* studentId);
    std::vector<std::vector<std::string>> getStudentRequestByRequestTime(const char* acount
                                                                         ,const char* className
                                                                         ,int curIndex,const char* requestTime);
    int getStudentRequestByRequestTimeCount(const char* acount
                                            ,const char* className
                                            ,const char* requestTime);
    bool agreeStudentRequestByStudentId(const char* acount
                                        ,const char* className
                                        ,const char* studentId);
    bool initJoinClassStudentManeageTable();
    bool degreeStudentRequestByStudentId(const char* acount
                                         ,const char* className
                                         ,const char* studentId);
    std::vector<std::vector<std::string>>  showClassIconInStudentManeger(const char* acount
                                                                         ,const char* className);
    int getStudentMenberCountData(const char* acount,const char* className);
    std::vector<std::vector<std::string>> getStudentManegerCurPageData(const char* acount
                                                                       ,const char* className
                                                                       ,int curIndex);
    int getStudentManegerTableCount(const char* acount,const char* className);
    bool deleteStudentManegerByStudentId(const char* acount
                                         ,const char* className
                                         ,const char* studentId);
    std::vector<std::vector<std::string>> getStudentManegerCurPageDataByStudentName(const char* acount
                                                                                    ,const char* className
                                                                                    ,const char* studentName
                                                                                    ,int curIndex);
    int getStudentManegerTableCountByStudentName(const char* acount
                                                 ,const char* className
                                                 ,const char* studentName);
     bool initDataBaseTestPaperReleaseTable();
     bool updateTestPaperStatus(const char* acount,const char* testPaperName);
     bool deleteTestPaperReleaseInfo(const char* acount,const char* testPaperName);
     bool initStudentAnswerSingaleTable();
     bool initStudentAnswerMultiTable();
     bool initStudentAnswerJudgeTable();
     bool initStudentAnswerShortAnswerTable();
     bool initCommitTestPaperTable();
     std::vector<std::vector<std::string>> getCurPageIndexCorrect(const char* teacherId,int curIndex);
     int  getCorrectTestPaperCount(const char* teacherId);
     std::vector<std::vector<std::string>> getCorrectTestPaperDataByName(const char* teacherId
                                                                         ,const char* testPaperName
                                                                         ,int& curIndex);
     int getCorrectTestPaperCountByName(const char* teacherId,const char* testPaperName);
     bool initCorrectShortAnswerTable();
     bool deleteSignalAnswer(const char* teacherId,const char* testPaperName);
     bool deleteMultiAnswer(const char* teacherId,const char* testPaperName);
     bool deleteJudgeAnswer(const char* teacherId,const char* testPaperName);
     bool  deleteShortAnswer(const char* teacherId,const char* testPaperName);
     bool  deleteCorrectShortAnswer(const char* teacherId,const char* testPaperName);
     bool  deleteTestPaperCommitInfo(const char* teacherId,const char* testPaperName);
     std::vector<std::vector<std::string>> getCurPageCorrectMember(const char* testPaperName,const char* teacherId
                                                                   ,int& classId,int& testPaperId,int& curIndex);
     int getCorrectMemberCount(const char* testPaperName,const char* teacherId
                               ,int& classId,int& testPaperId);
     bool deleteTestPaperCorrectInfo(const char* testPaperName
                                     ,const char* teacherId);
     bool initStudentScoreTable();
     bool insertStudentScore(const char* teacherId,const char* studetId
                             ,int& classId,int& testPaperId
                             ,double& keGuanScore,double& zhuGuanScore);
     bool updateStudentScore(const char* teacherId,const char* studetId,int& classId
                             ,int& testPaperId,double& keGuanScore
                             ,double& zhuGuanScore);
     bool deleteStudentScoreInfo(const char* teacherId,const char* testPaperName);
     std::vector<std::vector<std::string>> getSubjectTestPaperRelease(const char* teacherId);
     int getStudentScoreCount(const char* teacherId,int& testPaperId);
private:
      HANDLE m_mutex; //因为所有操作都是使用的一个CDBHelper对象，所以要给每一个执行sql的步骤进行上锁
};

#endif // CMAINMENUEMODEL_H
