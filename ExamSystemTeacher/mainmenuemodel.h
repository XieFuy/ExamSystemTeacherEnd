#ifndef CMAINMENUEMODEL_H
#define CMAINMENUEMODEL_H

#include "DBHelper.h"
#include <string>
#include <QString>
#include <QDebug>
#include "clientsocket.h"
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
};

#endif // CMAINMENUEMODEL_H
