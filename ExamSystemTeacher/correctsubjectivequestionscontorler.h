#ifndef CCORRECTSUBJECTIVEQUESTIONSCONTORLER_H
#define CCORRECTSUBJECTIVEQUESTIONSCONTORLER_H

#include<QDebug>
#include "correctsubjectivequestionsmodel.h"
#include <memory>

class CCorrectSubjectiveQuestionsContorler
{
public:
    CCorrectSubjectiveQuestionsContorler();
    ~CCorrectSubjectiveQuestionsContorler();
    std::vector<std::vector<std::string>> getCurOrderShortAnswer(int testPaperId,int order);
    std::vector<std::vector<std::string>> getCurOrderAnswer(QString teachreId
                                                            ,QString studentId,int classId
                                                            ,int testPaperId,int order);
    int getShortAnswerCount(int testPaperId);
    bool updateShortAnserScore(QString& studentId,QString& teacherId
                               ,int& classId,int& testPaperId,int& order,QString score);
    std::vector<std::vector<std::string>> getCurShortAnswerScore(QString& teacherId,QString& studentId
                                                                 ,int& classId,int& testPaperId,int& order);
private:
    std::shared_ptr<CCorrectSubjectiveQuestionsModel> m_model;
};

#endif // CCORRECTSUBJECTIVEQUESTIONSCONTORLER_H
