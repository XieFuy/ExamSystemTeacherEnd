#include "correctsubjectivequestionsmodel.h"

CCorrectSubjectiveQuestionsModel::CCorrectSubjectiveQuestionsModel()
{

}

std::vector<std::vector<std::string>> CCorrectSubjectiveQuestionsModel::getCurShortAnswerScore(const char* teacherId,const char* studentId
                                                             ,int& classId,int& testPaperId,int& order)
{
    if(teacherId == nullptr || studentId == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `score` from `shortAnswerCorrect` \
where `teacherId` = '%s' and `studentId` = '%s' \
and `classId` = %d and `testPaperId` = %d and `order` = %d;"
            ,teacherId,studentId,classId,testPaperId,order);
    sql = sqlBuf.get();
    return dbHelper->sqlQuery(sql,"ExamSystem");
}

//TODO:明天继续
bool CCorrectSubjectiveQuestionsModel::updateShortAnserScore(const char* studentId,const char* teacherId
                           ,int& classId,int& testPaperId,int& order,double score)
{
    if(studentId == nullptr || teacherId == nullptr)
    {
          return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * sizeof(1024000));
    sprintf(sqlBuf.get(),"update `shortAnswerCorrect` set `score` = %f \
where `teacherId` = '%s' and `classId` = %d  and `testPaperId` = %d \
and `studentId` = '%s' and `order` = %d;",score,teacherId,classId,testPaperId,studentId,order);
    sql = sqlBuf.get();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

int CCorrectSubjectiveQuestionsModel::getShoerAnswerCount(int testPaperId)
{
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"SELECT COUNT(*) FROM `shortAnswer` \
WHERE `testPaperId` = %d;",testPaperId);
    sql = sqlBuf.get();
    return dbHelper->sqlQueryCount(sql,"ExamSystem");
}

std::vector<std::vector<std::string>> CCorrectSubjectiveQuestionsModel::getCurOrderAnswer(const char* teachreId
                                                        ,const char* studentId,int classId
                                                        ,int testPaperId,int order)
{
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `AnswerGiven` from `studentAnswerShortAnswer` \
where `teacherId` = '%s' and `classId` = %d and `testPaperId` = %d and `studentId` = '%s' and `order` = %d;"
            ,teachreId,classId,testPaperId,studentId,order);
    sql = sqlBuf.get();
    return dbHelper->sqlQuery(sql,"ExamSystem");
}

std::vector<std::vector<std::string>> CCorrectSubjectiveQuestionsModel::getCurOrderShortAnswer(int testPaperId
                                                             ,int order)
{
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `grade`,`question`,`referenceAnswer` from `shortAnswer` where \
`testPaperId` = %d order by `order` limit 1 offset %d;",testPaperId,(order - 1));
    sql = sqlBuf.get();
    return dbHelper->sqlQuery(sql,"ExamSystem");
}

CCorrectSubjectiveQuestionsModel::~CCorrectSubjectiveQuestionsModel()
{
    qDebug()<<"correctSubject模型层销毁！";
}
