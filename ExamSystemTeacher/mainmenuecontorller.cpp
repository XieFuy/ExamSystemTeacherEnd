#include "mainmenuecontorller.h"

CMainMenueContorller::CMainMenueContorller()
{
 this->m_mainMenueModel = new CMainMenueModel();
}

CMainMenueContorller::~CMainMenueContorller()
{
 if(this->m_mainMenueModel != nullptr)
 {
     delete this->m_mainMenueModel;
     this->m_mainMenueModel = nullptr;
 }
}

void CMainMenueContorller::changeHeadPicture(QString LocalFilePath,QString acount)
{
    QString tempFileName;
    for(int i = LocalFilePath.size() - 1 ; i >= 0 ; i--)
    {
        if(LocalFilePath.at(i) == '/')
        {
            break;
        }
        tempFileName.push_back(LocalFilePath.at(i));
    }

    QString fileName;
    for(QString::reverse_iterator pos = tempFileName.rbegin(); pos != tempFileName.rend(); pos++)
    {
         fileName.push_back(*pos);
    }

    QByteArray localFilePathArr = LocalFilePath.toLocal8Bit();
    QByteArray acountArr = acount.toUtf8();
    QByteArray fileNameArr = fileName.toLocal8Bit();
    const char* pLocalFilePath = localFilePathArr.data();
    const char* pAcount = acountArr.data();
    const char* pFileName = fileNameArr.data();
    return  this->m_mainMenueModel->changeHeadPicture(const_cast<char*>(pLocalFilePath),const_cast<char*>( pFileName),const_cast<char*>(pAcount));
}

bool CMainMenueContorller::addSignalChoiceInfo(QString grade,QString question,QString sessionA,
                         QString sessionB,QString sessionC,QString sessionD,
                         QString correctOptions,int order)
{
    double dGrade = grade.toDouble();
    QByteArray questionArr = question.toLocal8Bit();
    QByteArray sessionAArr = sessionA.toLocal8Bit();
    QByteArray sessionBArr = sessionB.toLocal8Bit();
    QByteArray sessionCArr = sessionC.toLocal8Bit();
    QByteArray sessionDArr = sessionD.toLocal8Bit();
    QByteArray correctOptionsArr = correctOptions.toUtf8();
    const char* pQuestion = questionArr.data();
    const char* pSessionA = sessionAArr.data();
    const char* pSessionB = sessionBArr.data();
    const char* pSessionC = sessionCArr.data();
    const char* pSessionD = sessionDArr.data();
    const char* pCorrectOption = correctOptionsArr.data();
    return this->m_mainMenueModel->addSignalChoiceInfo(dGrade,pQuestion,pSessionA,pSessionB,
                                                       pSessionC,pSessionD,pCorrectOption,order);
}

bool CMainMenueContorller::initTestPaperTable()
{
    return this->m_mainMenueModel->initTestPaperTable();
}

bool CMainMenueContorller::initSingleChoiceTable()
{
    return  this->m_mainMenueModel->initSingleChoiceTable();
}

bool CMainMenueContorller::initMultiChoiceTable()
{
    return this->m_mainMenueModel->initMultiChoiceTable();
}

bool CMainMenueContorller::initJudgeTable()
{
    return this->m_mainMenueModel->initJudgeTable();
}

bool  CMainMenueContorller::initShortAnswerTable()
{
    return this->m_mainMenueModel->initShortAnswerTable();
}


bool CMainMenueContorller::initTeacherInfoTable()
{
    return  this->m_mainMenueModel->initTeacherInfoTable();
}

std::vector<std::vector<std::string>> CMainMenueContorller::showTeacherInfo(QString acount)
{
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount = acountArr.data();
    return  this->m_mainMenueModel->showTeacherInfo(const_cast<char*>(pAcount));
}

std::vector<std::vector<std::string>> CMainMenueContorller::showTeacherAcountInfo(QString acount)
{
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount = acountArr.data();
    return this->m_mainMenueModel->showTeacherAcountInfo(const_cast<char*>(pAcount));
}

void CMainMenueContorller::changeGender(bool isMan,QString pAcount)
{
    QByteArray acountArr = pAcount.toUtf8();
    const char* acount = acountArr.data();
    this->m_mainMenueModel->changeGender(isMan,const_cast<char*>(acount));
}
