#include "correctsubjectivequestionscontorler.h"

CCorrectSubjectiveQuestionsContorler::CCorrectSubjectiveQuestionsContorler()
{
   this->m_model  = std::make_shared<CCorrectSubjectiveQuestionsModel>();
}

int CCorrectSubjectiveQuestionsContorler::checkScoreExist(QString& teacherId,QString& studentId
                    ,int& classId,int& testPaperId)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pStudentId = studentIdArr.data();
    return this->m_model->checkScoreExist(pTeacherId,pStudentId,classId,testPaperId);
}

bool CCorrectSubjectiveQuestionsContorler::updateTestPaperCorrectStatus(QString& teacherId,QString& studentId
                                                                   ,int& classId,int& testPaperId)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pStudentId = studentIdArr.data();
    return this->m_model->updateTestPaperCorrectStatus(pTeacherId,pStudentId,classId,testPaperId);
}

std::vector<std::vector<std::string>> CCorrectSubjectiveQuestionsContorler::getCurShortAnswerScore(QString& teacherId,QString& studentId
                                                             ,int& classId,int& testPaperId,int& order)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pStudentId = studentIdArr.data();
    return this->m_model->getCurShortAnswerScore(pTeacherId,pStudentId,classId,testPaperId,order);
}

bool CCorrectSubjectiveQuestionsContorler::updateShortAnserScore(QString& studentId,QString& teacherId
                           ,int& classId,int& testPaperId,int& order,QString score)
{
    QByteArray studentIdArr = studentId.toLocal8Bit();
    QByteArray teacherIdArr = teacherId.toLocal8Bit();

    const char* pStudentId = studentIdArr.data();
    const char* pTeacherId = teacherIdArr.data();
    double dScore = score.toDouble();
    return this->m_model->updateShortAnserScore(pStudentId,pTeacherId,classId,testPaperId,order,dScore);
}

int CCorrectSubjectiveQuestionsContorler::getShortAnswerCount(int testPaperId)
{
    return this->m_model->getShoerAnswerCount(testPaperId);
}

std::vector<std::vector<std::string>> CCorrectSubjectiveQuestionsContorler::getCurOrderAnswer(QString teachreId
                                                        ,QString studentId
                                                        ,int classId,int testPaperId,int order)
{
    QByteArray teacherIdArr =  teachreId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();
    const char* pTeacherId = teacherIdArr.data();
    const char* pStudentId = studentIdArr.data();
    return this->m_model->getCurOrderAnswer(pTeacherId,pStudentId,classId,testPaperId,order);
}

std::vector<std::vector<std::string>> CCorrectSubjectiveQuestionsContorler::getCurOrderShortAnswer(int testPaperId
                                                             ,int order)
{
    return this->m_model->getCurOrderShortAnswer(testPaperId,order);
}

CCorrectSubjectiveQuestionsContorler::~CCorrectSubjectiveQuestionsContorler()
{
    qDebug()<<"correctSubject控制层销毁！";
}
