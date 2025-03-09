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
    bool updateShortAnserScore(const char* studentId,const char* teacherId
                               ,int& classId,int& testPaperId,int& order,double score);
    std::vector<std::vector<std::string>> getCurShortAnswerScore(const char* teacherId,const char* studentId
                                                                 ,int& classId,int& testPaperId,int& order);
    bool updateTestPaperCorrectStatus(const char* teacherId,const char* studentId
                                                                       ,int& classId,int& testPaperId);
};

#endif // CCORRECTSUBJECTIVEQUESTIONSMODEL_H
