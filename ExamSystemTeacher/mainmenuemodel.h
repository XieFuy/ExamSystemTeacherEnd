#ifndef CMAINMENUEMODEL_H
#define CMAINMENUEMODEL_H

#include "DBHelper.h"
#include <string>
#include <QString>
#include <QDebug>
#include "clientsocket.h"
#include <stdlib.h>
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
    bool deleteClassInfoByDateTime(const char* acount,const char* createTime);
    std::vector<std::vector<std::string>> showClassIconInStudentRequest(const char* acount,
                                                                        const char* className);
private:
      HANDLE m_mutex; //因为所有操作都是使用的一个CDBHelper对象，所以要给每一个执行sql的步骤进行上锁
};

#endif // CMAINMENUEMODEL_H
