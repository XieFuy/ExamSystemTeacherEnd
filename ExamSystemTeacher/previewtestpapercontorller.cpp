#include "previewtestpapercontorller.h"

CPreviewTestPaperContorller::CPreviewTestPaperContorller()
{
   this->m_model = new CPreviewTestPaperModel();
}

std::vector<std::vector<std::string>> CPreviewTestPaperContorller::getCurIndexMultiChoice(QString acount
                                                             ,QString testPaperName
                                                             ,int curIndex)
{
    QByteArray acountArr = acount.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pAcount = acountArr.data();
    const char* pTestPaperName = testPaperNameArr.data();

    return this->m_model->getCurIndexMultiChoice(pAcount,pTestPaperName,curIndex);
}

int CPreviewTestPaperContorller::getMultiChoiceCount(QString acount,QString testPaperName)
{
    QByteArray acountArr = acount.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pAcount = acountArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_model->getMultiChoiceCount(pAcount,pTestPaperName);
}

CPreviewTestPaperContorller::~CPreviewTestPaperContorller()
{
    if(this->m_model != nullptr)
    {
       delete this->m_model;
       this->m_model = nullptr;
    }
}

std::vector<std::vector<std::string>> CPreviewTestPaperContorller::getCurIndexSignalChoice(QString acount
                                                              ,QString testPaperName
                                                              ,int curIndex)
{
    QByteArray acountArr = acount.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pAcount = acountArr.data();
    const char* pTestPaperName = testPaperNameArr.data();

    return this->m_model->getCurIndexSignalChoice(pAcount,pTestPaperName,curIndex);
}


int CPreviewTestPaperContorller::getSignalChoiceCount(QString acount,QString testPaperName)
{
    QByteArray acountArr = acount.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pAcount = acountArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_model->getSignalChoiceCount(pAcount,pTestPaperName);
}
