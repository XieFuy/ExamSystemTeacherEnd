#ifndef CCORRECTSUBJECTIVEQUESTIONSMODEL_H
#define CCORRECTSUBJECTIVEQUESTIONSMODEL_H

#include "DBHelper.h"
#include <QDebug>
#include <memory>

class CCorrectSubjectiveQuestionsModel
{
public:
    CCorrectSubjectiveQuestionsModel();
    ~CCorrectSubjectiveQuestionsModel();
    std::vector<std::vector<std::string>> getCurOrderShortAnswer(int testPaperId
                                                                 ,int order);
    std::vector<std::vector<std::string>> getCurOrderAnswer(const char* teachreId
                                                            ,const char* studentId,int classId
                                                            ,int testPaperId,int order);
    int getShoerAnswerCount(int testPaperId);
};

#endif // CCORRECTSUBJECTIVEQUESTIONSMODEL_H
