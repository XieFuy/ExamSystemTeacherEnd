#include "previewtestpapermodel.h"

CPreviewTestPaperModel::CPreviewTestPaperModel()
{

}

CPreviewTestPaperModel::~CPreviewTestPaperModel()
{

}

std::vector<std::vector<std::string>> CPreviewTestPaperModel::getCurIndexJudegChoice(const char* acount
                                                             ,const char* testPaperName
                                                             ,int curIndex)
{
    if(acount == nullptr || testPaperName == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `question`,`sessionTrue`,`sessionFalse`,`correctAnswer` from `judge`\n\
where `testPaperId` in( SELECT DISTINCT `testPaperId` \n\
FROM `testPaperInfo` \n\
WHERE `teacherId` = '%s' AND `testPaperName` = '%s') order by `order` limit 1 offset %d;",acount,testPaperName,(curIndex - 1));
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

int CPreviewTestPaperModel::getJudgeChoiceCount(const char* acount,const char* testPaperName)
{
    if(acount == nullptr || testPaperName == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"SELECT COUNT(*) \n\
FROM `judge` \n\
WHERE `testPaperId` IN (\n\
SELECT DISTINCT `testPaperId` \n\
FROM `testPaperInfo` \n\
WHERE `teacherId` = '%s' AND `testPaperName` = '%s');",acount,testPaperName);
    sql = sqlBuf;
    int ret =  dbHelper->sqlQueryCount(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

std::vector<std::vector<std::string>> CPreviewTestPaperModel::getCurIndexMultiChoice(const char* acount
                                                             ,const char* testPaperName
                                                             ,int curIndex)
{
    if(acount == nullptr || testPaperName == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `question`,`sessionA`,`sessionB`,`sessionC`,`sessionD`,`sessionE`,`sessionF`,`correctOptions` from `multiChoice`\n\
where `testPaperId` in( SELECT DISTINCT `testPaperId` \n\
FROM `testPaperInfo` \n\
WHERE `teacherId` = '%s' AND `testPaperName` = '%s') order by `order` limit 1 offset %d;",acount,testPaperName,(curIndex - 1));
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

int CPreviewTestPaperModel::getMultiChoiceCount(const char* acount,const char* testPaperName)
{
    if(acount == nullptr || testPaperName == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"SELECT COUNT(*) \n\
FROM `multiChoice` \n\
WHERE `testPaperId` IN (\n\
SELECT DISTINCT `testPaperId` \n\
FROM `testPaperInfo` \n\
WHERE `teacherId` = '%s' AND `testPaperName` = '%s');",acount,testPaperName);
    sql = sqlBuf;
    int ret =  dbHelper->sqlQueryCount(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

std::vector<std::vector<std::string>> CPreviewTestPaperModel::getCurIndexSignalChoice(const char* acount
                                                              ,const char* testPaperName,int curIndex)
{
    if(acount == nullptr || testPaperName == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `question`,`sessionA`,`sessionB`,`sessionC`,`sessionD`,`correctOptions` from `singleChoice`\n\
where `testPaperId` in( SELECT DISTINCT `testPaperId` \n\
FROM `testPaperInfo` \n\
WHERE `teacherId` = '%s' AND `testPaperName` = '%s') order by `order` limit 1 offset %d;",acount,testPaperName,(curIndex - 1));
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

int CPreviewTestPaperModel::getSignalChoiceCount(const char* acount,const char* testPaperName)
{
    if(acount == nullptr || testPaperName == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"SELECT COUNT(*) \n\
FROM `singleChoice` \n\
WHERE `testPaperId` IN (\n\
SELECT DISTINCT `testPaperId` \n\
FROM `testPaperInfo` \n\
WHERE `teacherId` = '%s' AND `testPaperName` = '%s');",acount,testPaperName);
    sql = sqlBuf;
    int ret =  dbHelper->sqlQueryCount(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}
