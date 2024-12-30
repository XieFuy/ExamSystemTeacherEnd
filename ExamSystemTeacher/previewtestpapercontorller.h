#ifndef CPREVIEWTESTPAPERCONTORLLER_H
#define CPREVIEWTESTPAPERCONTORLLER_H

#include "previewtestpapermodel.h"
#include <QString>
#include <QByteArray>

class CPreviewTestPaperContorller  //试卷预览模型层
{
public:
    CPreviewTestPaperContorller();
    ~CPreviewTestPaperContorller();
    int getSignalChoiceCount(QString acount,QString testPaperName);
    std::vector<std::vector<std::string>> getCurIndexSignalChoice(QString acount
                                                                  ,QString testPaperName
                                                                  ,int curIndex);
    int getMultiChoiceCount(QString acount,QString testPaperName);
    std::vector<std::vector<std::string>> getCurIndexMultiChoice(QString acount
                                                                 ,QString testPaperName
                                                                 ,int curIndex);
private:
     CPreviewTestPaperModel* m_model = nullptr;
};

#endif // CPREVIEWTESTPAPERCONTORLLER_H
