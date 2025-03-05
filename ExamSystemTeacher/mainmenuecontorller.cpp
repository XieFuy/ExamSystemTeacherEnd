#include "mainmenuecontorller.h"

CMainMenueContorller::CMainMenueContorller()
{
 this->m_mainMenueModel = new CMainMenueModel();
}

int CMainMenueContorller::getCorrectMemberCount(QString& testPaperName,QString& teacherId
                          ,int& classId,int& testPaperId)
{
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();
    QByteArray teacherIdArr = teacherId.toLocal8Bit();

    const char* pTestPaperName = testPaperNameArr.data();
    const char* pTeacherId = teacherIdArr.data();
    return this->m_mainMenueModel->getCorrectMemberCount(pTestPaperName,pTeacherId,classId,testPaperId);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getCurPageCorrectMember(QString& testPaperName,QString& teacherId
                                                              ,int& classId,int& testPaperId,int& curIndex)
{
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();
    QByteArray teacherIdArr = teacherId.toLocal8Bit();

    const char* pTestPaperName = testPaperNameArr.data();
    const char* pTeacherId = teacherIdArr.data();
    return this->m_mainMenueModel->getCurPageCorrectMember(pTestPaperName,pTeacherId,classId,testPaperId,curIndex);
}

bool CMainMenueContorller::deleteTestPaperCommitInfo(QString& teacherId
                                                     ,QString& testPaperName)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pTeacher = teacherIdArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_mainMenueModel->deleteTestPaperCommitInfo(pTeacher,pTestPaperName);
}

bool CMainMenueContorller::deleteTestPaperCorrectInfo(QString& testPaperName
                                                      ,QString& teacherId)
{
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    const char* pTestPaperName = testPaperNameArr.data();
    const char* pTeacherId = teacherIdArr.data();
    return this->m_mainMenueModel->deleteTestPaperCorrectInfo(pTestPaperName
                                                              ,pTeacherId);
}

bool CMainMenueContorller::deleteCorrectShortAnswer(QString& teacherId,QString& testPaperName)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pTeacher = teacherIdArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_mainMenueModel->deleteCorrectShortAnswer(pTeacher,pTestPaperName);
}

bool CMainMenueContorller::deleteShortAnswer(QString& teacherId,QString& testPaperName)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pTeacher = teacherIdArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_mainMenueModel->deleteShortAnswer(pTeacher,pTestPaperName);
}

bool CMainMenueContorller::deleteJudgeAnswer(QString& teacherId,QString& testPaperName)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pTeacher = teacherIdArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_mainMenueModel->deleteJudgeAnswer(pTeacher,pTestPaperName);
}

bool CMainMenueContorller::deleteMultiAnswer(QString& teacherId,QString& testPaperName)
{
   QByteArray teacherIdArr = teacherId.toLocal8Bit();
   QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

   const char* pTeacher = teacherIdArr.data();
   const char* pTestPaperName = testPaperNameArr.data();
   return this->m_mainMenueModel->deleteMultiAnswer(pTeacher,pTestPaperName);
}

bool CMainMenueContorller::deleteSignalAnswer(QString& teacherId,QString& testPaperName)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();
    const char* pTeacherId = teacherIdArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_mainMenueModel->deleteSignalAnswer(pTeacherId,pTestPaperName);
}


bool CMainMenueContorller::initCorrectShortAnswerTable()
{
    return this->m_mainMenueModel->initCorrectShortAnswerTable();
}

int CMainMenueContorller::getCorrectTestPaperCountByName(QString& teacherId,QString& testPaperName)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();
    const char* pTeacherId = teacherIdArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_mainMenueModel->getCorrectTestPaperCountByName(pTeacherId,pTestPaperName);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getCorrectTestPaperDataByName(QString& teacherId
                                                                    ,QString& testPaperName,int& curIndex)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pTeacherIdArr = teacherIdArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_mainMenueModel->getCorrectTestPaperDataByName(pTeacherIdArr,pTestPaperName,curIndex);
}

int CMainMenueContorller::getCorrectTestPaperCount(QString& teacherId)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    const char* pTeacherId = teacherIdArr.data();
    return this->m_mainMenueModel->getCorrectTestPaperCount(pTeacherId);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getCurPageIndexCorrect(QString teacherId,int curIndex)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    const char* pTeacherId = teacherIdArr.data();
    return this->m_mainMenueModel->getCurPageIndexCorrect(pTeacherId,curIndex);
}

bool CMainMenueContorller::initStudentAnswerSingaleTable()
{
    return this->m_mainMenueModel->initStudentAnswerSingaleTable();
}

bool CMainMenueContorller::initCommitTestPaperTable()
{
    return this->m_mainMenueModel->initCommitTestPaperTable();
}

bool CMainMenueContorller::deleteTestPaperReleaseInfo(QString acount,QString testPaperName)
{
    QByteArray acountArr = acount.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pAcount = acountArr.data();
    const char* pTestPaperName = testPaperNameArr.data();

    return this->m_mainMenueModel->deleteTestPaperReleaseInfo(pAcount,pTestPaperName);
}

bool CMainMenueContorller::initDataBaseTestPaperReleaseTable()
{
    return this->m_mainMenueModel->initDataBaseTestPaperReleaseTable();
}

bool CMainMenueContorller::updateTestPaperStatus(QString acount,QString testPaperName)
{
    QByteArray acountArr = acount.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pAcount  = acountArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_mainMenueModel->updateTestPaperStatus(pAcount,pTestPaperName);
}

int CMainMenueContorller::getStudentManegerTableCountByStudentName(QString acount
                                                                   ,QString className
                                                                   ,QString studentName)
{
    QByteArray acountArr = acount.toLocal8Bit();
    QByteArray classNameArr = className.toLocal8Bit();
    QByteArray studentNameArr = studentName.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    const char* pStudentName = studentNameArr.data();
    return this->m_mainMenueModel->getStudentManegerTableCountByStudentName(pAcount,pClassName,pStudentName);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getStudentManegerCurPageDataByStudentName(QString acount
                                                                                ,QString className
                                                                                ,QString studentName
                                                                                ,int curIndex)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    QByteArray studentNameArr = studentName.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    const char* pStudentName = studentNameArr.data();
    return this->m_mainMenueModel->getStudentManegerCurPageDataByStudentName(pAcount,pClassName,pStudentName,curIndex);
}

typedef struct deleteMultiManegerByStudentIdArg{
    CMainMenueContorller* thiz;
    const char* acount;
    const char* className;
    const char* studentId;
}DeleteMultiManegerByStudentIdArg;

bool CMainMenueContorller::deleteMultiManegerByStudentId(QString acount,QString className,QList<QString>* studentIdLst)
{
    if(studentIdLst == nullptr)
    {
        return false;
    }
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();

    HANDLE handleArr[studentIdLst->size()];
    QByteArray studentIdArr[studentIdLst->size()];
    for(int i = 0 ; i < studentIdLst->size();i++)
    {
        studentIdArr[i] = studentIdLst->at(i).toLocal8Bit();
        const char* pStudentId = studentIdArr[i].data();
        DeleteMultiManegerByStudentIdArg* arg = new DeleteMultiManegerByStudentIdArg();
        arg->acount = pAcount;
        arg->className = pClassName;
        arg->studentId = pStudentId;
        arg->thiz = this;
        handleArr[i] = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteMultiManegerByStudentId,arg,0,nullptr);
    }
    WaitForMultipleObjects(studentIdLst->size(),handleArr,TRUE,INFINITE);
    return true;
}

unsigned WINAPI CMainMenueContorller::threadDeleteMultiManegerByStudentId(LPVOID arg)
{
    DeleteMultiManegerByStudentIdArg* aInfo = (DeleteMultiManegerByStudentIdArg*)arg;
    aInfo->thiz->m_mainMenueModel->deleteStudentManegerByStudentId(aInfo->acount,aInfo->className,aInfo->studentId);
    delete aInfo;
    //_endthreadex(0);
    return 0;
}

bool CMainMenueContorller::deleteStudentManegerByStudentId(QString acount
                                                           ,QString className
                                                           ,QString studentId)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    const char* pStudentId = studentIdArr.data();
    return this->m_mainMenueModel->deleteStudentManegerByStudentId(pAcount,pClassName,pStudentId);
}

int CMainMenueContorller::getStudentManegerTableCount(QString acount,QString className)
{
    QByteArray acountArr = acount.toLocal8Bit();
    QByteArray classNameArr = className.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    return this->m_mainMenueModel->getStudentManegerTableCount(pAcount,pClassName);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getStudentManegerCurPageData(QString acount
                                                                                         ,QString className
                                                                                         ,int curIndex)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    return this->m_mainMenueModel->getStudentManegerCurPageData(pAcount,pClassName,curIndex);
}

int CMainMenueContorller::getStudentMenberCountData(QString acount,QString className)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    return this->m_mainMenueModel->getStudentMenberCountData(pAcount,pClassName);
}


std::vector<std::vector<std::string>> CMainMenueContorller::showClassIconInStudentManeger(QString acount
                                                                                          ,QString className)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    return this->m_mainMenueModel->showClassIconInStudentManeger(pAcount,pClassName);
}

typedef  struct degreeMultiRequestByStudentIdArg{
    const char* acount;
    const char* className;
    const char* studentId;
    CMainMenueContorller* thiz;
}DegreeMultiRequestByStudentIdArg;

bool CMainMenueContorller::degreeMultiRequestByStudentId(QString acount
                                                         ,QString className
                                                         ,QList<QString>* studentIdLst)
{
    if(studentIdLst == nullptr)
    {
        return false;
    }
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();

    HANDLE handleArr[studentIdLst->size()];
    QByteArray studentIdArr[studentIdLst->size()];
    for(int i = 0 ; i < studentIdLst->size();i++)
    {
        studentIdArr[i] = studentIdLst->at(i).toLocal8Bit();
        const char* pStudentId = studentIdArr[i].data();
        DegreeMultiRequestByStudentIdArg* arg = new DegreeMultiRequestByStudentIdArg();
        arg->acount = pAcount;
        arg->className = pClassName;
        arg->studentId = pStudentId;
        arg->thiz = this;
        handleArr[i] = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDegreeMultiRequestByStudentId,arg,0,nullptr);
    }
    WaitForMultipleObjects(studentIdLst->size(),handleArr,TRUE,INFINITE);
    return true;
}

unsigned WINAPI CMainMenueContorller::threadDegreeMultiRequestByStudentId(LPVOID arg)
{
    DegreeMultiRequestByStudentIdArg* aInfo = (DegreeMultiRequestByStudentIdArg*)arg;
    aInfo->thiz->m_mainMenueModel->degreeStudentRequestByStudentId(aInfo->acount,aInfo->className,aInfo->studentId);
    delete aInfo;
    //_endthreadex(0);
    return 0;
}

typedef  struct agreeMultiRequestByStudentIdArg{
    const char* acount;
    const char* className;
    const char* studentId;
    CMainMenueContorller* thiz;
}AgreeMultiRequestByStudentIdArg;

bool CMainMenueContorller::agreeMultiRequestByStudentId(QString acount,QString className,QList<QString>* studentIdLst)
{
    if(studentIdLst == nullptr)
    {
        return false;
    }
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();

    HANDLE handleArr[studentIdLst->size()];
    QByteArray studentIdArr[studentIdLst->size()];
    for(int i = 0 ; i < studentIdLst->size();i++)
    {
        studentIdArr[i] = studentIdLst->at(i).toLocal8Bit();
        const char* pStudentId = studentIdArr[i].data();
        AgreeMultiRequestByStudentIdArg* arg = new AgreeMultiRequestByStudentIdArg();
        arg->acount = pAcount;
        arg->className = pClassName;
        arg->studentId = pStudentId;
        arg->thiz = this;
        handleArr[i] = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadAgreeMultiRequestByStudentId,arg,0,nullptr);
    }
    WaitForMultipleObjects(studentIdLst->size(),handleArr,TRUE,INFINITE);
    return true;
}

unsigned WINAPI CMainMenueContorller::threadAgreeMultiRequestByStudentId(LPVOID arg)
{
    AgreeMultiRequestByStudentIdArg* aInfo = (AgreeMultiRequestByStudentIdArg*)arg;
    aInfo->thiz->m_mainMenueModel->agreeStudentRequestByStudentId(aInfo->acount,aInfo->className,aInfo->studentId);
    delete aInfo;
    //_endthreadex(0);
    return 0;
}

bool CMainMenueContorller::degreeStudentRequestByStudentId(QString acount,QString className,QString studentId)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    const char* pStudentId = studentIdArr.data();
    return this->m_mainMenueModel->degreeStudentRequestByStudentId(pAcount,pClassName,pStudentId);
}

bool CMainMenueContorller::initJoinClassStudentManeageTable()
{
    return this->m_mainMenueModel->initJoinClassStudentManeageTable();
}

bool CMainMenueContorller::agreeStudentRequestByStudentId(QString acount
                                                          ,QString className
                                                          ,QString studentId)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    const char* pStudentId  = studentIdArr.data();
    return this->m_mainMenueModel->agreeStudentRequestByStudentId(pAcount,pClassName,pStudentId);
}


int CMainMenueContorller::getStudentRequestByRequestTimeCount(QString acount
                                        ,QString className
                                        ,QString requestTime)
{
    QByteArray acountArr = acount.toLocal8Bit();
    QByteArray classNameArr = className.toLocal8Bit();
    QByteArray studentNameArr = requestTime.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    const char* pStudentName = studentNameArr.data();
    return this->m_mainMenueModel->getStudentRequestByRequestTimeCount(pAcount,pClassName,pStudentName);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getStudentRequestByRequestTime(QString acount
                                                                     ,QString className
                                                                     ,int curIndex
                                                                     ,QString requestTime)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    QByteArray studentNameArr = requestTime.toLocal8Bit();

    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    const char* pStudentName = studentNameArr.data();
    return this->m_mainMenueModel->getStudentRequestByRequestTime(pAcount,pClassName,curIndex,pStudentName);

}

int CMainMenueContorller::getStudentRequestByStudentIdCount(QString acount
                                                            ,QString className
                                                            ,QString studentId)
{
    QByteArray acountArr = acount.toLocal8Bit();
    QByteArray classNameArr = className.toLocal8Bit();
    QByteArray studentNameArr = studentId.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    const char* pStudentName = studentNameArr.data();
    return this->m_mainMenueModel->getStudentRequestByStudentIdCount(pAcount,pClassName,pStudentName);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getStudentRequestByStudentId(QString acount
                                                                   ,QString className
                                                                   ,int curIndex,QString studentId)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    QByteArray studentNameArr = studentId.toLocal8Bit();

    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    const char* pStudentName = studentNameArr.data();
    return this->m_mainMenueModel->getStudentRequestByStudentId(pAcount,pClassName,curIndex,pStudentName);
}

int CMainMenueContorller::getStudentRequestByStudentNameCount(QString acount,QString className,QString studentName)
{
    QByteArray acountArr = acount.toLocal8Bit();
    QByteArray classNameArr = className.toLocal8Bit();
    QByteArray studentNameArr = studentName.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    const char* pStudentName = studentNameArr.data();
    return this->m_mainMenueModel->getStudentRequestByStudentNameCount(pAcount,pClassName,pStudentName);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getStudentRequestByStudentName(QString acount
                                                                     ,QString className
                                                                     ,int curIndex,QString studentName)
{
   QByteArray acountArr = acount.toUtf8();
   QByteArray classNameArr = className.toLocal8Bit();
   QByteArray studentNameArr = studentName.toLocal8Bit();

   const char* pAcount = acountArr.data();
   const char* pClassName = classNameArr.data();
   const char* pStudentName = studentNameArr.data();
   return this->m_mainMenueModel->getStudentRequestByStudentName(pAcount,pClassName,curIndex,pStudentName);
}

int CMainMenueContorller::getStudentRequestTableCount(QString acount,QString className,int curIndex)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    return this->m_mainMenueModel->getStudentRequestTableCount(pAcount,pClassName,curIndex);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getStudentRequestTableData(QString className
                                                                                       ,QString acount
                                                                                       ,int curIndex)
{
    QByteArray classNameArr = className.toLocal8Bit();
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    return this->m_mainMenueModel->getStudentRequestTableData(pClassName,pAcount,curIndex);
}

bool CMainMenueContorller::initStudentRequestDataBaseTable()
{
    return this->m_mainMenueModel->initStudentRequestDataBaseTable();
}

std::vector<std::vector<std::string>> CMainMenueContorller::showClassIconInStudentRequest(
                                                                    QString acount,
                                                                    QString className)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray classNameArr = className.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pClassName = classNameArr.data();
    return this->m_mainMenueModel->showClassIconInStudentRequest(pAcount,pClassName);
}


typedef struct deleteMultiClassInfoArg
{
    CMainMenueContorller*thiz;
    const char* acount;
    const char* createTime;
    const char* className;
}DeleteMultiClassInfoArg;

bool CMainMenueContorller::deleteMultiClassInfo(QString acount,QList<QString>& createTimeLst,QList<QString>& classNameLst)
{
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount = acountArr.data();
    for(int i = 0 ; i < createTimeLst.size();i++)
    {
        QByteArray createTimeArr = createTimeLst.at(i).toLocal8Bit();
        const char* pCreateTime = createTimeArr.data();
        QByteArray classNameArr = classNameLst.at(i).toLocal8Bit();
        const char* pClassName = classNameArr.data();

        DeleteMultiClassInfoArg* arg = new DeleteMultiClassInfoArg();
        arg->thiz = this;
        arg->acount = pAcount;
        arg->createTime = pCreateTime;
        arg->className = pClassName;
        HANDLE thread = (HANDLE) _beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteMultiClassInfo,arg,0,nullptr);
        WaitForSingleObject(thread,INFINITE);
    }
    return true;
}

unsigned WINAPI CMainMenueContorller::threadDeleteMultiClassInfo(LPVOID arg)
{
    DeleteMultiClassInfoArg* dInfo = (DeleteMultiClassInfoArg*)arg;
    dInfo->thiz->m_mainMenueModel->deleteClassInfoByDateTime(dInfo->acount,dInfo->createTime,dInfo->className);
    delete dInfo;
    //_endthreadex(0);
    return 0;
}

bool CMainMenueContorller::deleteClassInfoByDateTime(QString acount,QString createTime,QString className)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray createTimeArr = createTime.toLocal8Bit();
    QByteArray classNameArr = className.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pCreateTime = createTimeArr.data();
    const char* pClassName = classNameArr.data();
    return this->m_mainMenueModel->deleteClassInfoByDateTime(pAcount,pCreateTime,pClassName);
}

int CMainMenueContorller::getClassTableCount(QString acount)
{
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount =  acountArr.data();
    return this->m_mainMenueModel->getClassTableCount(pAcount);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getClassTableData(QString acount,int curPageIndex)
{
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount = acountArr.data();
    return this->m_mainMenueModel->getClassTableData(pAcount,curPageIndex);
}

bool CMainMenueContorller::initClassTableDatabase()
{
  return this->m_mainMenueModel->initClassTableDatabase();
}

typedef struct deleteFromSignalChoiseArg
{
    QString acount;
    QString createTime;
    CMainMenueContorller* thiz;
}DeleteFromSignalChoiseArg;


bool CMainMenueContorller::deleteMultiClickBtn(QString acount,QList<QString> createTimeLst,QList<QString>& testPaperIdLst)
{
    bool ret = false;
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount = acountArr.data();
    //打印一遍时间列表
    for(int i = 0 ; i < createTimeLst.size();i++)
    {
        QByteArray createTimeArr = createTimeLst.at(i).toLocal8Bit();
        const char* pCreateTime = createTimeArr.data();

        //删除单选题题库
        DeleteFromSignalChoiseArg* arg = new DeleteFromSignalChoiseArg();
        arg->thiz = this;
        arg->acount = acount;
        arg->createTime = createTimeLst.at(i);
        HANDLE thread1 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteFromSignalChoise,arg,0,nullptr);

        //删除多选题题库
        DeleteFromSignalChoiseArg* arg2 = new DeleteFromSignalChoiseArg();
        arg2->thiz = this;
        arg2->acount = acount;
        arg2->createTime = createTimeLst.at(i);
        HANDLE thread2 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteFromMultiChoise,arg2,0,nullptr);

        //删除判断题题库
        DeleteFromSignalChoiseArg* arg3 = new DeleteFromSignalChoiseArg();
        arg3->thiz = this;
        arg3->acount = acount;
        arg3->createTime = createTimeLst.at(i);
        HANDLE thread3 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteFromJudge,arg3,0,nullptr);

        //删除简答题题库
        DeleteFromSignalChoiseArg* arg4 = new DeleteFromSignalChoiseArg();
        arg4->thiz = this;
        arg4->acount = acount;
        arg4->createTime = createTimeLst.at(i);
        HANDLE thread4 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteFromShortAnswer,arg4,0,nullptr);

        //进行删除单选题答题记录
        DeleteFromSignalChoiseArg* arg6 = new DeleteFromSignalChoiseArg();
        arg6->thiz = this;
        arg6->acount = acount;
        arg6->createTime = testPaperIdLst.at(i);
        HANDLE thread6 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteSignalAnswer,arg6,0,nullptr);

        //进行删除多选题的答题记录
        DeleteFromSignalChoiseArg* arg7 = new DeleteFromSignalChoiseArg();
        arg7->thiz = this;
        arg7->acount = acount;
        arg7->createTime = testPaperIdLst.at(i);
        HANDLE thread7 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteMultiAnswer,arg7,0,nullptr);

        //进行删除判断题的答题记录
        DeleteFromSignalChoiseArg* arg8 = new DeleteFromSignalChoiseArg();
        arg8->thiz = this;
        arg8->acount = acount;
        arg8->createTime = testPaperIdLst.at(i);
        HANDLE thread8 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteJudgeAnswer,arg8,0,nullptr);

        //进行删除简答题的答题记录
        DeleteFromSignalChoiseArg* arg9 = new DeleteFromSignalChoiseArg();
        arg9->thiz = this;
        arg9->acount = acount;
        arg9->createTime = testPaperIdLst.at(i);
        HANDLE thread9 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteShortAnswer,arg9,0,nullptr);

        //进行删除该试卷的所有的简答题评分记录
        DeleteFromSignalChoiseArg* arg10 = new DeleteFromSignalChoiseArg();
        arg10->thiz = this;
        arg10->acount = acount;
        arg10->createTime = testPaperIdLst.at(i);
        HANDLE thread10 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteShortAnswer,arg10,0,nullptr);

        //进行删除该试卷的提交记录
        DeleteFromSignalChoiseArg* arg11 = new DeleteFromSignalChoiseArg();
        arg11->thiz = this;
        arg11->acount = acount;
        arg11->createTime = testPaperIdLst.at(i);
        HANDLE thread11 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteTestPaperCommitInfo,arg11,0,nullptr);

        //进行删除简答题批改表记录
        DeleteFromSignalChoiseArg* arg12 = new DeleteFromSignalChoiseArg();
        arg12->thiz = this;
        arg12->acount = acount;
        arg12->createTime = testPaperIdLst.at(i);
        HANDLE thread12 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteTestPaperCorrectInfo,arg12,0,nullptr);

        //需要等待上面的任务都执行完毕才能进行删除试卷表的信息
        WaitForSingleObject(thread1,INFINITE);
        WaitForSingleObject(thread2,INFINITE);
        WaitForSingleObject(thread3,INFINITE);
        WaitForSingleObject(thread4,INFINITE);
        WaitForSingleObject(thread6,INFINITE);
        WaitForSingleObject(thread7,INFINITE);
        WaitForSingleObject(thread8,INFINITE);
        WaitForSingleObject(thread9,INFINITE);
        WaitForSingleObject(thread10,INFINITE);
        WaitForSingleObject(thread11,INFINITE);
        WaitForSingleObject(thread12,INFINITE);

        //开启线程进行删除该试卷的发布信息
        DeleteFromSignalChoiseArg* arg5 = new DeleteFromSignalChoiseArg();
        arg5->thiz = this;
        arg5->acount = acount;
        arg5->createTime = testPaperIdLst.at(i);  //这里要传的是试卷名称不是试卷id ，懒得该变量名 包括函数参数也是
        HANDLE thread5 = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteTestPaperRelease,arg5,0,nullptr);
        WaitForSingleObject(thread5,INFINITE);

        ret = this->m_mainMenueModel->deleteClickBtn(pAcount,pCreateTime);
    }
    return ret;
}

unsigned WINAPI CMainMenueContorller::threadDeleteMultiAnswer(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->deleteMultiAnswer(dInfo->acount,dInfo->createTime);
    delete dInfo;
    //_endthreadex(0);
    return 0;
}

unsigned WINAPI CMainMenueContorller::threadDeleteJudgeAnswer(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->deleteJudgeAnswer(dInfo->acount,dInfo->createTime);
    delete dInfo;
    //_endthreadex(0);
    return 0;
}

unsigned WINAPI CMainMenueContorller::threadDeleteShortAnswer(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->deleteShortAnswer(dInfo->acount,dInfo->createTime);
    delete dInfo;
    //_endthreadex(0);
    return 0;
}

unsigned WINAPI CMainMenueContorller::threadDeleteTestPaperCorrectInfo(LPVOID arg)
{
     DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
     dInfo->thiz->deleteTestPaperCorrectInfo(dInfo->createTime,dInfo->acount);
     delete dInfo;
     return 0;
}

unsigned WINAPI CMainMenueContorller::threadDeleteTestPaperCommitInfo(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->deleteTestPaperCommitInfo(dInfo->acount,dInfo->createTime);
    delete dInfo;
    //_endthreadex(0);
    return 0;
}



unsigned WINAPI CMainMenueContorller::threadDeleteTestPaperRelease(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->deleteTestPaperReleaseInfo(dInfo->acount,dInfo->createTime);
    delete dInfo;
    //_endthreadex(0);
    return 0;
}

unsigned WINAPI CMainMenueContorller::threadDeleteFromShortAnswer(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->deleteFromShortAnswer(dInfo->acount,dInfo->createTime);
    delete dInfo;
    //_endthreadex(0);
    return 0;
}
unsigned CMainMenueContorller::WINAPI threadDeleteSignalAnswer(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->deleteSignalAnswer(dInfo->acount,dInfo->createTime);
    delete dInfo;
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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

 bool CMainMenueContorller::initStudentAnswerMultiTable()
 {
     return this->m_mainMenueModel->initStudentAnswerMultiTable();
 }

 bool CMainMenueContorller::initStudentAnswerJudgeTable()
 {
     return this->m_mainMenueModel->initStudentAnswerJudgeTable();
 }

 bool CMainMenueContorller::initStudentAnswerShortAnswerTable()
 {
     return this->m_mainMenueModel->initStudentAnswerShortAnswerTable();
 }
