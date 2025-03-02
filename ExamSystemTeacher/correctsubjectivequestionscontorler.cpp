#include "correctsubjectivequestionscontorler.h"

CCorrectSubjectiveQuestionsContorler::CCorrectSubjectiveQuestionsContorler()
{
   this->m_model  = std::make_shared<CCorrectSubjectiveQuestionsModel>();
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
