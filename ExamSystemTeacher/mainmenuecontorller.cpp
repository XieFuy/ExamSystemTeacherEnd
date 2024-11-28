#include "mainmenuecontorller.h"

CMainMenueContorller::CMainMenueContorller()
{
 this->m_mainMenueModel = new CMainMenueModel();
}

typedef struct deleteFromSignalChoiseArg
{
    QString acount;
    QString createTime;
    CMainMenueContorller* thiz;
}DeleteFromSignalChoiseArg;


bool CMainMenueContorller::deleteMultiClickBtn(QString acount,QList<QString> createTimeLst)
{
    bool ret = false;
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount = acountArr.data();
    //打印一遍时间列表
    for(int i = 0 ; i < createTimeLst.size();i++)
    {
        QByteArray createTimeArr = createTimeLst.at(i).toLocal8Bit();
        const char* pCreateTime = createTimeArr.data();

        DeleteFromSignalChoiseArg* arg = new DeleteFromSignalChoiseArg();
        arg->thiz = this;
        arg->acount = acount;
        arg->createTime = createTimeLst.at(i);
        HANDLE thread1 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteFromSignalChoise,arg,0,nullptr);

        DeleteFromSignalChoiseArg* arg2 = new DeleteFromSignalChoiseArg();
        arg2->thiz = this;
        arg2->acount = acount;
        arg2->createTime = createTimeLst.at(i);
        HANDLE thread2 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteFromMultiChoise,arg2,0,nullptr);

        DeleteFromSignalChoiseArg* arg3 = new DeleteFromSignalChoiseArg();
        arg3->thiz = this;
        arg3->acount = acount;
        arg3->createTime = createTimeLst.at(i);
        HANDLE thread3 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteFromJudge,arg3,0,nullptr);

        DeleteFromSignalChoiseArg* arg4 = new DeleteFromSignalChoiseArg();
        arg4->thiz = this;
        arg4->acount = acount;
        arg4->createTime = createTimeLst.at(i);
        HANDLE thread4 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteFromShortAnswer,arg4,0,nullptr);

        //先从题库中删除属于该试卷的所有试题
        //ret = this->m_mainMenueModel->deleteFromSignalChoise(pAcount,pCreateTime);
//        ret = this->m_mainMenueModel->deleteFromMultiChoise(pAcount,pCreateTime);
//        ret = this->m_mainMenueModel->deleteFromJudge(pAcount,pCreateTime);
//        ret = this->m_mainMenueModel->deleteFromShortAnswer(pAcount,pCreateTime);
        //再进行删除题库中的试卷信息
        //等待四个线程结束时进行执行
        WaitForSingleObject(thread1,INFINITE);
        WaitForSingleObject(thread2,INFINITE);
        WaitForSingleObject(thread3,INFINITE);
        WaitForSingleObject(thread4,INFINITE);
        ret = this->m_mainMenueModel->deleteClickBtn(pAcount,pCreateTime);
    }
    return ret;
}

unsigned WINAPI CMainMenueContorller::threadDeleteFromShortAnswer(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->deleteFromShortAnswer(dInfo->acount,dInfo->createTime);
    delete dInfo;
    _endthreadex(0);
    return 0;
}

bool CMainMenueContorller::deleteFromShortAnswer(QString acount,QString createTime)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray createTimeArr = createTime.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pCreateTime = createTimeArr.data();
    return this->m_mainMenueModel->deleteFromShortAnswer(pAcount,pCreateTime);
}

unsigned WINAPI CMainMenueContorller::threadDeleteFromJudge(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->deleteFromJudge(dInfo->acount,dInfo->createTime);
    delete dInfo;
    _endthreadex(0);
    return 0;
}

bool CMainMenueContorller::deleteFromJudge(QString acount,QString createTime)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray createTimeArr = createTime.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pCreateTime = createTimeArr.data();
    return this->m_mainMenueModel->deleteFromJudge(pAcount,pCreateTime);
}

unsigned WINAPI CMainMenueContorller::threadDeleteFromMultiChoise(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->deleteFromMultiChoise(dInfo->acount,dInfo->createTime);
    delete dInfo;
    _endthreadex(0);
    return 0;
}

bool CMainMenueContorller::deleteFromMultiChoise(QString acount,QString createTime)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray createTimeArr = createTime.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pCreateTime = createTimeArr.data();
    return this->m_mainMenueModel->deleteFromMultiChoise(pAcount,pCreateTime);
}

unsigned WINAPI CMainMenueContorller::threadDeleteFromSignalChoise(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->deleteFromSignalChoise(dInfo->acount,dInfo->createTime);
    delete dInfo;
    _endthreadex(0);
    return 0;
}

bool CMainMenueContorller::deleteFromSignalChoise(QString acount,QString createTime)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray createTimeArr = createTime.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pCreateTime = createTimeArr.data();
    return this->m_mainMenueModel->deleteFromSignalChoise(pAcount,pCreateTime);
}

bool CMainMenueContorller::deleteClickBtn(QString acount,QString createTime)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray createTimeArr = createTime.toUtf8();
    const char* pAcount  = acountArr.data();
    const char* pCreateTime = createTimeArr.data();
    return this->m_mainMenueModel->deleteClickBtn(pAcount,pCreateTime);
}

int CMainMenueContorller::getTableDataByFindTestNameCount(QString acount,QString testPaperName)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_mainMenueModel->getTableDataByFindTestNameCount(pAcount,pTestPaperName);
}

int CMainMenueContorller::getTablePageCountNotPublished(QString acount,QString status)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray statusArr = status.toUtf8();
    const char* pAcount = acountArr.data();
    const char* pStatus = statusArr.data();
    return this->m_mainMenueModel->getTablePageCountNotPublished(pAcount,pStatus);
}

std::vector<std::vector<std::string>> CMainMenueContorller:: getCurPageIndexTableDataNotPubulished(
                                                                            int curPageIndex,
                                                                            QString acount,
                                                                            QString status)
{
   QByteArray acountArr = acount.toUtf8();
   QByteArray statusArr = status.toUtf8();
   const char* pAcount = acountArr.data();
   const char* pStatus = statusArr.data();
   return this->m_mainMenueModel->getCurPageIndexTableDataNotPubulished(curPageIndex,pAcount,pStatus);
}

CMainMenueContorller::~CMainMenueContorller()
{
 if(this->m_mainMenueModel != nullptr)
 {
     delete this->m_mainMenueModel;
     this->m_mainMenueModel = nullptr;
 }
}

QString CMainMenueContorller::getTablePageCount(QString acount)
{
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount = acountArr.data();
    return this->m_mainMenueModel->getTablePageCount(const_cast<char*>(pAcount));
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

int CMainMenueContorller::getTablePageCountPublished(QString acount,
                                                     QString status)
{
   QByteArray acountArr = acount.toUtf8();
   QByteArray statusArr = status.toUtf8();
   const char* pAcount = acountArr.data();
   const char* pStatus = statusArr.data();
   return this->m_mainMenueModel->getTablePageCountPublished(pAcount,pStatus);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getTableDataByFindTestName(int curPageIndex,
                                                                 QString acount,
                                                                 QString testPaperName)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_mainMenueModel->getTableDataByFindTestName(curPageIndex,pAcount,pTestPaperName);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getCurPageIndexTableDataPubulished(
        int curPageIndex,QString acount,QString status)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray statusArr = status.toUtf8();
    const char* pAcount = acountArr.data();
    const char* pStatus = statusArr.data();
    return this->m_mainMenueModel->getCurPageIndexTableDataPubulished(curPageIndex,pAcount,pStatus);
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

bool CMainMenueContorller::addMultiChoiceInfo(QString grade,QString question,QString sessionA,
                        QString sessionB,QString sessionC,QString sessionD,
                        QString sessionE,QString sessionF,QString correctOpetions,int order)
{
    double dGrade = grade.toDouble();
    QByteArray questionArr = question.toLocal8Bit();
    QByteArray sessionAArr = sessionA.toLocal8Bit();
    QByteArray sessionBArr = sessionB.toLocal8Bit();
    QByteArray sessionCArr = sessionC.toLocal8Bit();
    QByteArray sessionDArr = sessionD.toLocal8Bit();
    QByteArray sessionEArr = sessionE.toLocal8Bit();
    QByteArray sessionFArr = sessionF.toLocal8Bit();
    QByteArray correctOpetionsArr = correctOpetions.toUtf8();

    const char* pQuestion = questionArr.data();
    const char* pSessionA = sessionAArr.data();
    const char* pSessionB = sessionBArr.data();
    const char* pSessionC = sessionCArr.data();
    const char* pSessionD = sessionDArr.data();
    const char* pSessionE = sessionEArr.data();
    const char* pSessionF = sessionFArr.data();
    const char* pCorrectOpetions = correctOpetionsArr.data();
    return  this->m_mainMenueModel->addMultiChoiceInfo(dGrade,pQuestion,pSessionA,pSessionB,pSessionC,pSessionD,pSessionE,pSessionF,pCorrectOpetions,order);
}

bool CMainMenueContorller::addJudgeInfo(QString grade,QString question,QString sessionTrue,QString sessionFalse,
                  QString correctAnswer,int order)
{
   double dGrade = grade.toDouble();
   QByteArray questionArr = question.toLocal8Bit();
   QByteArray sessionTrueArr = sessionTrue.toLocal8Bit();
   QByteArray sessionFalseArr = sessionFalse.toLocal8Bit();
   QByteArray correctAnswerArr = correctAnswer.toLocal8Bit();

   const char* pQuestion = questionArr.data();
   const char* pSessionTrue = sessionTrueArr.data();
   const char* pSessionFalse = sessionFalseArr.data();
   const char* pcorrectAnswer = correctAnswerArr.data();
   return this->m_mainMenueModel->addJudgeInfo(dGrade,pQuestion,pSessionTrue,pSessionFalse,pcorrectAnswer,order);
}

bool CMainMenueContorller::addShortAnswerInfo(QString grade,QString question,QString referenceAnswer,int order)
{
    double dGrade = grade.toDouble();
    QByteArray questionArr = question.toLocal8Bit();
    QByteArray referenceAnswerArr = referenceAnswer.toLocal8Bit();
    const char* pQuestion = questionArr.data();
    const char* pReferenceAnswer = referenceAnswerArr.data();
    return this->m_mainMenueModel->addShortAnswerInfo(dGrade,pQuestion,pReferenceAnswer,order);
}

 std::vector<std::vector<std::string>> CMainMenueContorller::showCurPageIndexTable(int curPageIndex,QString acount)
 {
      QByteArray acountArr = acount.toUtf8();
      const char* pAcount = acountArr.data();
      return this->m_mainMenueModel->showCurPageIndexTable(curPageIndex,const_cast<char*>(pAcount));
 }
