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
};

#endif // CPREVIEWTESTPAPERMODEL_H
