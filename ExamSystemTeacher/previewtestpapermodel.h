#ifndef CPREVIEWTESTPAPERMODEL_H
#define CPREVIEWTESTPAPERMODEL_H

#include "DBHelper.h"
#include <memory>

class CPreviewTestPaperModel  //试卷预览模型层
{
public:
    CPreviewTestPaperModel();
    ~CPreviewTestPaperModel();
    int getSignalChoiceCount(const char* acount,const char* testPaperName);
    std::vector<std::vector<std::string>> getCurIndexSignalChoice(const char* acount
                                                                  ,const char* testPaperName,int curIndex);
    int getMultiChoiceCount(const char* acount,const char* testPaperName);
    std::vector<std::vector<std::string>> getCurIndexMultiChoice(const char* acount
                                                                 ,const char* testPaperName
                                                                 ,int curIndex);
    int getJudgeChoiceCount(const char* acount,const char* testPaperName);
    std::vector<std::vector<std::string>> getCurIndexJudegChoice(const char* acount
                                                                 ,const char* testPaperName
                                                                 ,int curIndex);
    int getShortAnswerCount(const char* acount,const char* testPaperName);
    std::vector<std::vector<std::string>> getCurIndexShortAnswerChoice(const char* acount
                                                                       ,const char* testPaperName
                                                                       ,int curIndex);
};

#endif // CPREVIEWTESTPAPERMODEL_H
