#include "mainmenuemodel.h"

CMainMenueModel::CMainMenueModel()
{
 this->m_mutex = CreateMutex(nullptr,FALSE,nullptr);
}

CMainMenueModel::~CMainMenueModel()
{

}

std::vector<std::vector<std::string>> CMainMenueModel::getStudentScoreInfo(const char* teacherId
                                                          ,int& testPaperId)
{
    if(teacherId == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"SELECT \n\
si.`name`,\n\
sc.`studentId`,\n\
c.`className`,\n\
sc.`keGuanScore`,\n\
sc.`shuGuanScore`,\n\
(IFNULL(sc.`keGuanScore`, 0) + IFNULL(sc.`shuGuanScore`, 0)) AS `totalScore`\n\
FROM \n\
`scoreCount` sc\n\
JOIN \n\
`StudentInfo` si ON sc.`studentId` = si.`studentId`\n\
JOIN \n\
`class` c ON sc.`classId` = c.`id` AND c.`teacherId` = sc.`teacherId`\n\
WHERE \n\
sc.`teacherId` = '%s' \n\
AND sc.`testPaperId` = %d;",teacherId,testPaperId);
    sql = sqlBuf.get();
    return dbHelper->sqlQuery(sql,"ExamSystem");
}

int CMainMenueModel::getStudentScoreCount(const char* teacherId,int& testPaperId)
{
    if(teacherId == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select count(*) from `scoreCount` \
where `teacherId` = '%s' and `testPaperId` = %d;",teacherId,testPaperId);
    sql = sqlBuf.get();
    return dbHelper->sqlQueryCount(sql,"ExamSystem");
}

std::vector<std::vector<std::string>> CMainMenueModel::getSubjectTestPaperRelease(const char* teacherId)
{
    if(teacherId == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"SELECT DISTINCT ctp.`testPaperName`,tpr.`testPaperId`\n\
FROM `commitTestPaper` ctp\n\
JOIN `testPaperRelease` tpr\n\
ON ctp.`classId` = tpr.`classId` AND ctp.`testPaperId` = tpr.`testPaperId`\n\
WHERE ctp.`teacherId` = '%s' AND tpr.`teacherId` = '%s' AND ctp.`correctStatus` = '1';"
            ,teacherId,teacherId);
    sql = sqlBuf.get();
    return dbHelper->sqlQuery(sql,"ExamSystem");
}

bool CMainMenueModel::deleteStudentScoreInfo(const char* teacherId,const char* testPaperName)
{
    if(teacherId == nullptr || testPaperName == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"delete from `scoreCount` \
where `teacherId` = '%s' and  `testPaperId` in (select `testPaperId` from `testPaperInfo` where `testPaperName` = '%s' and `teacherId` = '%s');"
            ,teacherId,testPaperName,teacherId);
    sql = sqlBuf.get();
    qDebug()<<sql.c_str();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::updateStudentScore(const char* teacherId,const char* studetId,int& classId
                        ,int& testPaperId,double& keGuanScore
                        ,double& zhuGuanScore)
{
    if(teacherId == nullptr || studetId == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"update `scoreCount`  set `keGuanScore` = %f, `shuGuanScore` = %f \
where `teacherId` = '%s' and `studentId` = '%s' and `classId`  = %d and `testPaperId` = %d;"
            ,keGuanScore,zhuGuanScore,teacherId,studetId,classId,testPaperId);
    sql = sqlBuf.get();
    qDebug()<< sql.c_str();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::insertStudentScore(const char* teacherId,const char* studetId
                        ,int& classId,int& testPaperId
                        ,double& keGuanScore,double& zhuGuanScore)
{
    if(teacherId == nullptr || studetId == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"insert into `scoreCount` (`teacherId`,`classId`,`testPaperId`,`studentId`,`keGuanScore`,`shuGuanScore`) \
values ('%s',%d,%d,'%s',%f,%f);",teacherId,classId,testPaperId,studetId,keGuanScore,zhuGuanScore);
    sql = sqlBuf.get();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::initStudentScoreTable()
{
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"create table if not exists `scoreCount`(\n\
`id` integer primary key auto_increment,\n\
`teacherId` varchar(20)  not null,\n\
foreign key(`teacherId`) references `Teacher`(`teacherId`),\n\
`classId` integer not null ,  \n\
foreign key(`classId`) references `class`(`id`),\n\
`testPaperId` integer not null,\n\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`),\n\
`studentId` varchar(20) not null,\n\
foreign key(`studentId`) references `Student`(`studentId`),\n\
`keGuanScore` double not null default 0.0,\n\
`shuGuanScore` double not null default 0.0\n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    sql = sqlBuf.get();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

std::vector<std::vector<std::string>> CMainMenueModel::getCurPageCorrectMember(const char* testPaperName
                                                              ,const char* teacherId
                                                              ,int& classId,int& testPaperId,int& curIndex)

{
    if(teacherId == nullptr || testPaperName == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    /*sprintf(sqlBuf.get(),"SELECT \n\
studentInfo.studentId,\n\
studentInfo.studentName,\n\
studentInfo.subjectName,\n\
IFNULL(objectiveScore.totalScore, 0) AS objectiveTotalScore,\n\
IFNULL(subjectiveScore.totalScore, 0) AS subjectiveTotalScore\n\
FROM \n\
(\n\
SELECT \n\
si.studentId AS studentId,\n\
si.name AS studentName,\n\
c.className AS subjectName\n\
FROM \n\
testPaperInfo tpi\n\
JOIN \n\
testPaperRelease tpr ON tpi.testPaperId = tpr.testPaperId\n\
JOIN \n\
class c ON tpr.classId = c.id\n\
JOIN \n\
joinClassStudentManeage jcsm ON c.className = jcsm.className\n\
JOIN \n\
StudentInfo si ON jcsm.studentId = si.studentId\n\
WHERE \n\
tpi.testPaperName = '%s'\n\
AND tpi.teacherId = '%s'\n\
AND c.teacherId = '%s'\n\
AND jcsm.teacherId = '%s'\n\
) AS studentInfo\n\
LEFT JOIN \n\
(\n\
SELECT \n\
studentId,\n\
SUM(score) AS totalScore\n\
FROM (\n\
SELECT \n\
sas.studentId,\n\
IF(sas.AnswerGiven = sc.correctOptions, sc.grade, 0) AS score\n\
FROM \n\
studentAnswerSingal sas\n\
JOIN \n\
singleChoice sc \n\
ON sas.testPaperId = sc.testPaperId \n\
AND sas.order = sc.order\n\
WHERE \n\
sas.testPaperId = %d\n\
AND sas.classId = %d\n\
AND sas.teacherId = '%s'\n\
UNION ALL\n\
SELECT \n\
sam.studentId,\n\
SUM(\n\
IF(\n\
FIND_IN_SET('A', sam.AnswerGiven) = FIND_IN_SET('A', mc.correctOptions)\n\
AND FIND_IN_SET('B', sam.AnswerGiven) = FIND_IN_SET('B', mc.correctOptions)\n\
AND FIND_IN_SET('C', sam.AnswerGiven) = FIND_IN_SET('C', mc.correctOptions)\n\
AND FIND_IN_SET('D', sam.AnswerGiven) = FIND_IN_SET('D', mc.correctOptions)\n\
AND FIND_IN_SET('E', sam.AnswerGiven) = FIND_IN_SET('E', mc.correctOptions)\n\
AND FIND_IN_SET('F', sam.AnswerGiven) = FIND_IN_SET('F', mc.correctOptions),\n\
mc.grade, 0\n\
)\n\
) AS score\n\
FROM \n\
studentAnswerMulti sam\n\
JOIN \n\
multiChoice mc \n\
ON sam.testPaperId = mc.testPaperId \n\
AND sam.order = mc.order\n\
WHERE \n\
sam.testPaperId = %d\n\
AND sam.classId = %d\n\
AND sam.teacherId = '%s'\n\
GROUP BY sam.studentId\n\
UNION ALL\n\
SELECT \n\
saj.studentId,\n\
IF(saj.AnswerGiven = j.correctAnswer, j.grade, 0) AS score\n\
FROM \n\
studentAnswerJudge saj\n\
JOIN \n\
judge j \n\
ON saj.testPaperId = j.testPaperId \n\
AND saj.order = j.order\n\
WHERE \n\
saj.testPaperId = %d\n\
AND saj.classId = %d\n\
AND saj.teacherId = '%s'\n\
) AS scoreTable\n\
GROUP BY studentId\n\
) AS objectiveScore\n\
ON studentInfo.studentId = objectiveScore.studentId\n\
LEFT JOIN \n\
(\n\
SELECT \n\
studentId,\n\
SUM(`score`) AS totalScore\n\
FROM \n\
`shortAnswerCorrect`\n\
WHERE \n\
`teacherId` = '%s'\n\
AND `classId` = %d\n\
AND `testPaperId` = %d\n\
GROUP BY studentId\n\
) AS subjectiveScore\n\
ON studentInfo.studentId = subjectiveScore.studentId \n\
WHERE objectiveTotalScore <> 0 \n\
LIMIT 8 OFFSET %d;"
            ,testPaperName,teacherId,teacherId,teacherId,testPaperId,classId,teacherId
            ,testPaperId,classId,teacherId,testPaperId,classId,teacherId,teacherId,classId,testPaperId,(curIndex - 1) * 8);*/

    sprintf(sqlBuf.get(),"SELECT *\n\
FROM (\n\
SELECT \n\
studentInfo.studentId,\n\
studentInfo.studentName,\n\
studentInfo.subjectName,\n\
IFNULL(objectiveScore.totalScore, 0) AS objectiveTotalScore,\n\
IFNULL(subjectiveScore.totalScore, 0) AS subjectiveTotalScore\n\
FROM \n\
(\n\
SELECT \n\
si.studentId AS studentId,\n\
si.name AS studentName,\n\
c.className AS subjectName\n\
FROM \n\
testPaperInfo tpi\n\
JOIN testPaperRelease tpr ON tpi.testPaperId = tpr.testPaperId\n\
JOIN class c ON tpr.classId = c.id\n\
JOIN joinClassStudentManeage jcsm ON c.className = jcsm.className\n\
JOIN StudentInfo si ON jcsm.studentId = si.studentId\n\
WHERE \n\
tpi.testPaperName = '%s'\n\
AND tpi.teacherId = '%s'\n\
AND c.teacherId = '%s'\n\
AND jcsm.teacherId = '%s'\n\
) AS studentInfo\n\
LEFT JOIN \n\
(\n\
SELECT \n\
studentId,\n\
SUM(score) AS totalScore\n\
FROM (\n\
SELECT \n\
sas.studentId,\n\
IF(sas.AnswerGiven = sc.correctOptions, sc.grade, 0) AS score\n\
FROM \n\
studentAnswerSingal sas\n\
JOIN singleChoice sc \n\
ON sas.testPaperId = sc.testPaperId \n\
AND sas.order = sc.order\n\
WHERE \n\
sas.testPaperId = %d\n\
AND sas.classId = %d\n\
AND sas.teacherId = '%s'\n\
UNION ALL\n\
SELECT \n\
sam.studentId,\n\
SUM(\n\
IF(\n\
FIND_IN_SET('A', sam.AnswerGiven) = FIND_IN_SET('A', mc.correctOptions)\n\
AND FIND_IN_SET('B', sam.AnswerGiven) = FIND_IN_SET('B', mc.correctOptions)\n\
AND FIND_IN_SET('C', sam.AnswerGiven) = FIND_IN_SET('C', mc.correctOptions)\n\
AND FIND_IN_SET('D', sam.AnswerGiven) = FIND_IN_SET('D', mc.correctOptions)\n\
AND FIND_IN_SET('E', sam.AnswerGiven) = FIND_IN_SET('E', mc.correctOptions)\n\
AND FIND_IN_SET('F', sam.AnswerGiven) = FIND_IN_SET('F', mc.correctOptions),\n\
mc.grade, 0\n\
)\n\
) AS score\n\
FROM \n\
studentAnswerMulti sam\n\
JOIN multiChoice mc \n\
ON sam.testPaperId = mc.testPaperId \n\
AND sam.order = mc.order\n\
WHERE \n\
sam.testPaperId = %d\n\
AND sam.classId = %d\n\
AND sam.teacherId = '%s'\n\
GROUP BY sam.studentId\n\
UNION ALL\n\
SELECT \n\
saj.studentId,\n\
IF(saj.AnswerGiven = j.correctAnswer, j.grade, 0) AS score\n\
FROM \n\
studentAnswerJudge saj\n\
JOIN judge j \n\
ON saj.testPaperId = j.testPaperId \n\
AND saj.order = j.order\n\
WHERE \n\
saj.testPaperId = %d\n\
AND saj.classId = %d\n\
AND saj.teacherId = '%s'\n\
) AS scoreTable\n\
GROUP BY studentId\n\
) AS objectiveScore\n\
ON studentInfo.studentId = objectiveScore.studentId\n\
LEFT JOIN \n\
(\n\
SELECT \n\
studentId,\n\
SUM(`score`) AS totalScore\n\
FROM \n\
`shortAnswerCorrect`\n\
WHERE \n\
`teacherId` = '%s'\n\
AND `classId` = %d\n\
AND `testPaperId` = %d\n\
GROUP BY studentId\n\
) AS subjectiveScore\n\
ON studentInfo.studentId = subjectiveScore.studentId\n\
) AS finalResult\n\
WHERE objectiveTotalScore <> 0\n\
LIMIT 8 OFFSET %d;"
                ,testPaperName,teacherId,teacherId,teacherId,testPaperId,classId,teacherId
                ,testPaperId,classId,teacherId,testPaperId,classId,teacherId,teacherId,classId,testPaperId,(curIndex - 1) * 8);
    sql = sqlBuf.get();
    return  dbHelper->sqlQuery(sql,"ExamSystem");
}

int CMainMenueModel::getCorrectMemberCount(const char* testPaperName,const char* teacherId
                          ,int& classId,int& testPaperId)
{
    if(testPaperName == nullptr || teacherId == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"SELECT \n\
COUNT(*) AS totalCount\n\
FROM \n\
(\n\
SELECT \n\
studentInfo.studentId,\n\
studentInfo.studentName,\n\
studentInfo.subjectName,\n\
IFNULL(objectiveScore.totalScore, 0) AS objectiveTotalScore,\n\
IFNULL(subjectiveScore.totalScore, 0) AS subjectiveTotalScore\n\
FROM \n\
(\n\
SELECT \n\
si.studentId AS studentId,\n\
si.name AS studentName,\n\
c.className AS subjectName\n\
FROM \n\
testPaperInfo tpi\n\
JOIN \n\
testPaperRelease tpr ON tpi.testPaperId = tpr.testPaperId\n\
JOIN \n\
class c ON tpr.classId = c.id\n\
JOIN \n\
joinClassStudentManeage jcsm ON c.className = jcsm.className\n\
JOIN \n\
StudentInfo si ON jcsm.studentId = si.studentId\n\
WHERE \n\
tpi.testPaperName = '%s'\n\
AND tpi.teacherId = '%s'\n\
AND c.teacherId = '%s'\n\
AND jcsm.teacherId = '%s'\n\
) AS studentInfo\n\
LEFT JOIN \n\
(\n\
SELECT \n\
studentId,\n\
SUM(score) AS totalScore\n\
FROM (\n\
SELECT \n\
sas.studentId,\n\
IF(sas.AnswerGiven = sc.correctOptions, sc.grade, 0) AS score\n\
FROM \n\
studentAnswerSingal sas\n\
JOIN \n\
singleChoice sc \n\
ON sas.testPaperId = sc.testPaperId \n\
AND sas.order = sc.order\n\
WHERE \n\
sas.testPaperId = %d\n\
AND sas.classId = %d\n\
AND sas.teacherId = '%s'\n\
UNION ALL\n\
SELECT \n\
sam.studentId,\n\
SUM(\n\
IF(\n\
FIND_IN_SET('A', sam.AnswerGiven) = FIND_IN_SET('A', mc.correctOptions)\n\
AND FIND_IN_SET('B', sam.AnswerGiven) = FIND_IN_SET('B', mc.correctOptions)\n\
AND FIND_IN_SET('C', sam.AnswerGiven) = FIND_IN_SET('C', mc.correctOptions)\n\
AND FIND_IN_SET('D', sam.AnswerGiven) = FIND_IN_SET('D', mc.correctOptions)\n\
AND FIND_IN_SET('E', sam.AnswerGiven) = FIND_IN_SET('E', mc.correctOptions)\n\
AND FIND_IN_SET('F', sam.AnswerGiven) = FIND_IN_SET('F', mc.correctOptions),\n\
mc.grade, 0\n\
)\n\
) AS score\n\
FROM\n\
studentAnswerMulti sam\n\
JOIN \n\
multiChoice mc \n\
ON sam.testPaperId = mc.testPaperId \n\
AND sam.order = mc.order\n\
WHERE \n\
sam.testPaperId = %d\n\
AND sam.classId = %d\n\
AND sam.teacherId = '%s'\n\
GROUP BY sam.studentId\n\
UNION ALL\n\
SELECT \n\
saj.studentId,\n\
IF(saj.AnswerGiven = j.correctAnswer, j.grade, 0) AS score\n\
FROM \n\
studentAnswerJudge saj\n\
JOIN \n\
judge j \n\
ON saj.testPaperId = j.testPaperId \n\
AND saj.order = j.order\n\
WHERE \n\
saj.testPaperId = %d\n\
AND saj.classId = %d\n\
AND saj.teacherId = '%s'\n\
) AS scoreTable\n\
GROUP BY studentId\n\
) AS objectiveScore\n\
ON studentInfo.studentId = objectiveScore.studentId\n\
LEFT JOIN \n\
(\n\
SELECT \n\
studentId,\n\
SUM(`score`) AS totalScore\n\
FROM \n\
`shortAnswerCorrect`\n\
WHERE \n\
`teacherId` = '%s'\n\
AND `classId` = %d\n\
AND `testPaperId` = %d\n\
GROUP BY studentId\n\
) AS subjectiveScore\n\
ON studentInfo.studentId = subjectiveScore.studentId\n\
) AS resultTable;"
            ,testPaperName,teacherId,teacherId,teacherId,testPaperId,classId,teacherId
            ,testPaperId,classId,teacherId,testPaperId,classId,teacherId,teacherId,classId,testPaperId);
    sql = sqlBuf.get();
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
        result += 1;
    }else
    {
        int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    return result;
}

bool CMainMenueModel::deleteTestPaperCommitInfo(const char* teacherId
                                                ,const char* testPaperName)
{
    if(teacherId == nullptr || testPaperName
             == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"DELETE FROM `commitTestPaper`\n\
 WHERE `teacherId` = '%s'\n\
 AND `testPaperId` IN (SELECT `testPaperId` FROM `testPaperInfo` WHERE `testPaperName` = '%s' AND `teacherId` = '%s');"
            ,teacherId,testPaperName,teacherId);
    sql = sqlBuf.get();
    qDebug()<<QString::fromLocal8Bit(sql.c_str());
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::deleteTestPaperCorrectInfo(const char* testPaperName
                                ,const char* teacherId)
{
    if(testPaperName == nullptr || teacherId == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"delete from `shortAnswerCorrect` \
where `teacherId` = '%s'  and  `testPaperId` in \
(SELECT `testPaperId` FROM `testPaperInfo` \
WHERE `testPaperName` = '%s' AND `teacherId` = '%s');"
            ,teacherId,testPaperName,teacherId);
    sql = sqlBuf.get();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::deleteCorrectShortAnswer(const char* teacherId,const char* testPaperName)
{
    if(teacherId == nullptr || testPaperName
             == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"DELETE FROM `shortAnswerCorrect`\n\
 WHERE `teacherId` = '%s'\n\
 AND `testPaperId` IN (SELECT `testPaperId` FROM `testPaperInfo` WHERE `testPaperName` = '%s' AND `teacherId` = '%s');"
            ,teacherId,testPaperName,teacherId);
    sql = sqlBuf.get();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::deleteShortAnswer(const char* teacherId,const char* testPaperName)
{
    if(teacherId == nullptr || testPaperName
             == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"DELETE FROM `studentAnswerShortAnswer`\n\
 WHERE `teacherId` = '%s'\n\
 AND `testPaperId` IN (SELECT `testPaperId` FROM `testPaperInfo` WHERE `testPaperName` = '%s' AND `teacherId` = '%s');"
            ,teacherId,testPaperName,teacherId);
    sql = sqlBuf.get();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::deleteJudgeAnswer(const char* teacherId,const char* testPaperName)
{
    if(teacherId == nullptr || testPaperName
             == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"DELETE FROM `studentAnswerJudge`\n\
 WHERE `teacherId` = '%s'\n\
 AND `testPaperId` IN (SELECT `testPaperId` FROM `testPaperInfo` WHERE `testPaperName` = '%s' AND `teacherId` = '%s');"
            ,teacherId,testPaperName,teacherId);
    sql = sqlBuf.get();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::deleteMultiAnswer(const char* teacherId,const char* testPaperName)
{
   if(teacherId == nullptr || testPaperName
            == nullptr)
   {
       return false;
   }
   std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
   std::unique_ptr<char[]> sqlBuf(new char[1024000]);
   std::string sql;
   memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
   sprintf(sqlBuf.get(),"DELETE FROM `studentAnswerMulti`\n\
WHERE `teacherId` = '%s'\n\
AND `testPaperId` IN (SELECT `testPaperId` FROM `testPaperInfo` WHERE `testPaperName` = '%s' AND `teacherId` = '%s');"
           ,teacherId,testPaperName,teacherId);
   sql = sqlBuf.get();
   return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::deleteSignalAnswer(const char* teacherId,const char* testPaperName)
{
    if(teacherId == nullptr || testPaperName == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"DELETE FROM `studentAnswerSingal`\n\
WHERE `teacherId` = '%s'\n\
AND `testPaperId` IN (SELECT `testPaperId` FROM `testPaperInfo` WHERE `testPaperName` = '%s' AND `teacherId` = '%s');"
            ,teacherId,testPaperName,teacherId);
    sql = sqlBuf.get();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel:: initCorrectShortAnswerTable()
{
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"create table if not exists `shortAnswerCorrect`(\n\
`id` integer primary key auto_increment,\n\
`teacherId` varchar(20)  not null,\n\
foreign key(`teacherId`) references `Teacher`(`teacherId`),\n\
`classId` integer not null ,  \n\
foreign key(`classId`) references `class`(`id`),\n\
`testPaperId` integer not null,\n\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`),\n\
`studentId` varchar(20) not null,\n\
foreign key(`studentId`) references `Student`(`studentId`),\n\
`order` integer not null,\n\
`score` double default 0.0 not null\n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    sql = sqlBuf.get();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

int CMainMenueModel::getCorrectTestPaperCountByName(const char* teacherId,const char* testPaperName)
{
    if(teacherId == nullptr || testPaperName == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf (new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"SELECT COUNT(DISTINCT testPaperId) AS uniqueTestPaperCount\n\
FROM commitTestPaper\n\
WHERE teacherId = '%s' AND testPaperName like '%%%s%%';",teacherId,testPaperName);
    sql = sqlBuf.get();
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
        result += 1;
    }else
    {
        int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    return result;
}

std::vector<std::vector<std::string>> CMainMenueModel::getCorrectTestPaperDataByName(const char* teacherId
                                                                    ,const char* testPaperName
                                                                    ,int& curIndex)
{
    if(teacherId == nullptr || testPaperName == nullptr || curIndex == -1)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"SELECT \n\
ctp.testPaperName,\n\
SUM(CASE WHEN ctp.correctStatus = '0' THEN 1 ELSE 0 END) AS pendingCount,\n\
SUM(CASE WHEN ctp.correctStatus != '0' THEN 1 ELSE 0 END) AS correctedCount,\n\
classId,\n\
testPaperId\n\
FROM \n\
commitTestPaper ctp\n\
WHERE\n\
ctp.teacherId = '%s' AND ctp.testPaperName like '%%%s%%'\n\
group by \n\
ctp.testPaperName,ctp.classId,ctp.testPaperId\n\
limit 8 offset %d;",teacherId,testPaperName,(curIndex - 1)*8);
    sql = sqlBuf.get();
    return  dbHelper->sqlQuery(sql,"ExamSystem");
}

int CMainMenueModel::getCorrectTestPaperCount(const char* teacherId)
{
    if(teacherId == nullptr)
    {
        return -1;
    }

    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf (new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"SELECT COUNT(DISTINCT testPaperId) AS uniqueTestPaperCount\n\
FROM commitTestPaper\n\
WHERE teacherId = '%s';",teacherId);
    sql = sqlBuf.get();
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
        result += 1;
    }else
    {
        int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    return result;
}

std::vector<std::vector<std::string>> CMainMenueModel::getCurPageIndexCorrect(const char* teacherId
                                                             ,int curIndex)
{
    if(teacherId == nullptr || curIndex <= 0)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"SELECT \n\
testPaperName,\n\
SUM(CASE WHEN correctStatus = '0' THEN 1 ELSE 0 END) AS pendingCount,\n\
SUM(CASE WHEN correctStatus != '0' THEN 1 ELSE 0 END) AS correctedCount,\n\
classId,\n\
testPaperId\n\
FROM \n\
commitTestPaper\n\
WHERE\n\
teacherId = '%s'\n\
GROUP BY \n\
testPaperName, classId, testPaperId\n\
LIMIT 8 OFFSET %d;",teacherId,(curIndex -1)*8);
    sql = sqlBuf.get();
    qDebug()<<sql.c_str();
    return dbHelper->sqlQuery(sql,"ExamSystem");
}

bool CMainMenueModel::initCommitTestPaperTable()
{
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"create table if not exists `commitTestPaper`(\n\
`id` integer primary key auto_increment,\n\
`teacherId` varchar(20)  not null,\n\
foreign key(`teacherId`) references `Teacher`(`teacherId`),\n\
`classId` integer not null ,  \n\
foreign key(`classId`) references `class`(`id`),\n\
`testPaperId` integer not null,\n\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`),\n\
`studentId` varchar(20) not null,\n\
foreign key(`studentId`) references `Student`(`studentId`),\n\
`testPaperName` varchar(100) not null,\n\
`correctStatus` varchar(5) not null default '0'\n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    sql = sqlBuf.get();
    qDebug()<<sql.c_str();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::initStudentAnswerShortAnswerTable()
{
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"create table if not exists `studentAnswerShortAnswer`(\n\
`id` integer primary key auto_increment,\n\
`teacherId` varchar(20)  not null,\n\
foreign key(`teacherId`) references `Teacher`(`teacherId`),\n\
`classId` integer not null ,  \n\
foreign key(`classId`) references `class`(`id`),\n\
`testPaperId` integer not null,\n\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`),\n\
`studentId` varchar(20) not null,\n\
foreign key(`studentId`) references `Student`(`studentId`),\n\
`AnswerGiven`  varchar(16383) not null default 'NULL',\n\
`order` integer not null\n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    sql = sqlBuf.get();
    qDebug()<<sql.c_str();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::initStudentAnswerJudgeTable()
{
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"create table if not exists `studentAnswerJudge`(\n\
`id` integer primary key auto_increment,\n\
`teacherId` varchar(20)  not null,\n\
foreign key(`teacherId`) references `Teacher`(`teacherId`),\n\
`classId` integer not null ,  \n\
foreign key(`classId`) references `class`(`id`),\n\
`testPaperId` integer not null,\n\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`),\n\
`studentId` varchar(20) not null,\n\
foreign key(`studentId`) references `Student`(`studentId`),\n\
`AnswerGiven` varchar(20) not null default 'NULL',\n\
`order` integer not null \n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    sql = sqlBuf.get();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::initStudentAnswerMultiTable()
{
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"create table if not exists `studentAnswerMulti`(\n\
`id` integer primary key auto_increment,\n\
`teacherId` varchar(20)  not null,\n\
foreign key(`teacherId`) references `Teacher`(`teacherId`),\n\
`classId` integer not null ,  \n\
foreign key(`classId`) references `class`(`id`),\n\
`testPaperId` integer not null,\n\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`),\n\
`studentId` varchar(20) not null,\n\
foreign key(`studentId`) references `Student`(`studentId`),\n\
`AnswerGiven` varchar(20) not null default 'NULL',\n\
`order` integer not null \n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    sql = sqlBuf.get();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::initStudentAnswerSingaleTable()
{
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"create table if not exists `studentAnswerSingal`(\n\
`id` integer primary key auto_increment,\n\
`teacherId` varchar(20)  not null,\n\
foreign key(`teacherId`) references `Teacher`(`teacherId`),\n\
`classId` integer not null,\n\
foreign key(`classId`) references `class`(`id`),\n\
`testPaperId` integer not null,\n\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`),\n\
`studentId` varchar(20) not null,\n\
foreign key(`studentId`) references `Student`(`studentId`),\n\
`AnswerGiven` varchar(20) not null default 'NULL',\n\
`order` integer not null \n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    sql = sqlBuf.get();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

bool CMainMenueModel::deleteTestPaperReleaseInfo(const char* acount,const char* testPaperName)
{
    if(acount == nullptr || testPaperName == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;  
    //进行删除单选题学生答案记录
   /*sprintf(sqlBuf,"delete from `studentAnswerSingal` where `teacherId` = '%s' and `testPaperId` in (SELECT DISTINCT `testPaperId` \n\
FROM `testPaperInfo` \n\
WHERE `teacherId` = '%s' AND `testPaperName` = '%s');",acount,acount,testPaperName);
   sql = sqlBuf;
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");

    //进行删除多选题的学生答案记录
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"delete from `studentAnswerMulti` where `teacherId` = '%s' and `testPaperId` in (SELECT DISTINCT `testPaperId` \n\
FROM `testPaperInfo` \n\
WHERE `teacherId` = '%s' AND `testPaperName` = '%s');",acount,acount,testPaperName);
    sql = sqlBuf;
    ret =  dbHelper->sqlExcute(sql,"ExamSystem");

    //进行删除判断题的学生答案记录
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"delete from `studentAnswerJudge` where `teacherId` = '%s' and `testPaperId` in (SELECT DISTINCT `testPaperId` \n\
FROM `testPaperInfo` \n\
WHERE `teacherId` = '%s' AND `testPaperName` = '%s');",acount,acount,testPaperName);
    sql = sqlBuf;
    ret =  dbHelper->sqlExcute(sql,"ExamSystem");

    //进行删除简答题的学生答案记录
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"delete from `studentAnswerShortAnswer` where `teacherId` = '%s' and `testPaperId` in (SELECT DISTINCT `testPaperId` \n\
FROM `testPaperInfo` \n\
WHERE `teacherId` = '%s' AND `testPaperName` = '%s');",acount,acount,testPaperName);
    sql = sqlBuf;
    ret =  dbHelper->sqlExcute(sql,"ExamSystem");*/

    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"delete from `testPaperRelease` where `teacherId` = '%s' and `testPaperId` in (SELECT DISTINCT `testPaperId` \n\
FROM `testPaperInfo` \n\
WHERE `teacherId` = '%s' AND `testPaperName` = '%s');",acount,acount,testPaperName);
    sql = sqlBuf;
    int ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

bool CMainMenueModel::updateTestPaperStatus(const char* acount,const char* testPaperName)
{
    if(acount == nullptr || testPaperName == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"update `testPaperInfo` set `publishStatus` = '1' \
where `teacherId` = '%s' and `testPaperName` = '%s';",acount,testPaperName);
    sql = sqlBuf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

bool CMainMenueModel::initDataBaseTestPaperReleaseTable()
{
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"create table if not exists `testPaperRelease`(\n\
`id` integer primary key auto_increment,\n\
`teacherId` varchar(20)  not null,\n\
foreign key(`teacherId`) references `Teacher`(`teacherId`),\n\
`classId` integer not null unique,\n\
foreign key(`classId`) references `class`(`id`),\n\
`testPaperId` integer unique,\n\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`),\n\
`examStartTime` datetime not null ,\n\
`examEndTime`  datetime not null,\n\
`examLongTimeMinute` integer not null,\n\
`limitSubmit` integer default 0,\n\
`limitEntry` integer default 0\n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    sql = sqlBuf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

int CMainMenueModel::getStudentManegerTableCountByStudentName(const char* acount
                                             ,const char* className
                                             ,const char* studentName)
{
    if(acount == nullptr || className == nullptr || studentName == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"SELECT \n\
COUNT(*) AS totalRowCount\n\
FROM \n\
`joinClassStudentManeage` jm\n\
JOIN \n\
`StudentInfo` si ON jm.studentId = si.studentId\n\
WHERE \n\
jm.teacherId = '%s'\n\
AND \n\
jm.className = '%s'\n\
AND  \n\
si.name like '%%%s%%';",acount,className,studentName);
    sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    delete[] sqlBuf;
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
        result += 1;
    }else
    {
        int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    return result;
}

std::vector<std::vector<std::string>> CMainMenueModel::getStudentManegerCurPageDataByStudentName(const char* acount
                                                                                ,const char* className
                                                                                ,const char* studentName
                                                                                ,int curIndex)
{
    if(acount == nullptr || className == nullptr || studentName == nullptr || curIndex == -1)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"SELECT \n\
si.profilePicture AS headIconPath,\n\
si.name,\n\
jm.studentId,\n\
si.phoneNumber AS phoneNumber,\n\
jm.joinTime \n\
FROM \n\
`joinClassStudentManeage` jm\n\
JOIN \n\
`StudentInfo` si ON jm.studentId = si.studentId\n\
WHERE \n\
jm.teacherId = '%s'\n\
AND \n\
jm.className = '%s'\n\
AND \n\
si.name like '%%%s%%'\n\
ORDER BY \n\
jm.id\n\
LIMIT 8 OFFSET %d;",acount,className,studentName,(curIndex -1) * 8);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

bool CMainMenueModel::deleteStudentManegerByStudentId(const char* acount
                                     ,const char* className
                                     ,const char* studentId)
{
    if(acount == nullptr || className == nullptr || studentId == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"delete from `joinClassStudentManeage` \
where `teacherId` = '%s' and `studentId` = '%s' and `className` = '%s';",acount,studentId,className);
    sql = sqlBuf;
    std::cout<<sql.c_str()<<std::endl;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

int  CMainMenueModel::getStudentManegerTableCount(const char* acount,const char* className)
{
    if(acount == nullptr || className == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"SELECT \n\
COUNT(*) AS totalRowCount\n\
FROM \n\
`joinClassStudentManeage` jm\n\
JOIN \n\
`StudentInfo` si ON jm.studentId = si.studentId\n\
WHERE \n\
jm.teacherId = '%s'\n\
AND jm.className = '%s';",acount,className);
    sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    delete[] sqlBuf;
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
        result += 1;
    }else
    {
        int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    return result;
}

std::vector<std::vector<std::string>> CMainMenueModel::getStudentManegerCurPageData(const char* acount
                                                                                    ,const char* className
                                                                                    ,int curIndex)
{
    if(acount == nullptr || className == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"SELECT \n\
si.profilePicture AS headIconPath,\n\
si.name,\n\
jm.studentId,\n\
si.phoneNumber AS phoneNumber,\n\
jm.joinTime \n\
FROM \n\
`joinClassStudentManeage` jm\n\
JOIN \n\
`StudentInfo` si ON jm.studentId = si.studentId\n\
WHERE \n\
jm.teacherId = '%s'\n\
AND \n\
jm.className = '%s'\n\
ORDER BY \n\
jm.id\n\
LIMIT 8 OFFSET %d;",acount,className,(curIndex -1) * 8);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

int CMainMenueModel::getStudentMenberCountData(const char* acount,const char* className)
{
    if(acount == nullptr || className == nullptr)
    {
        return -1;
    }
    CDBHelper* dbHelepr = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select count(*) from `joinClassStudentManeage` \
where  `teacherId` = '%s' and  `className`='%s';",acount,className);
    sql = sqlBuf;
    int ret = dbHelepr->sqlQueryCount(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelepr;
    return ret;
}

std::vector<std::vector<std::string>> CMainMenueModel::showClassIconInStudentManeger(const char* acount
                                                                     ,const char* className)
{
    if(acount == nullptr || className == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    CDBHelper* dbHelepr = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `classIconPath` from `class` \
where `className` = '%s' and `teacherId` = '%s';",className,acount);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret = dbHelepr->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelepr;
    return ret;
}

bool CMainMenueModel::degreeStudentRequestByStudentId(const char* acount
                                     ,const char* className
                                     ,const char* studentId)
{
    if(acount == nullptr || className == nullptr || studentId == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    //不同意直接从申请表中删除即可
    sprintf(sqlBuf,"delete from `requestJoinClass` \
where `studentId` = '%s' and `className` = '%s' and `teacherId` = '%s';",studentId
            ,className,acount);
    sql = sqlBuf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

bool CMainMenueModel::initJoinClassStudentManeageTable()
{
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"create table if not exists `joinClassStudentManeage`(\n\
            `id`  integer primary key auto_increment,\n\
            `studentId`  varchar(20) not null,\n\
            foreign key(`studentId`) references `Student`(`studentId`),\n\
            `joinTime` datetime not null,\n\
            `className` varchar(50) not null,\n\
            `teacherId` varchar(20)  not null,\n\
            foreign key(`teacherId`) references `Teacher`(`teacherId`)\n\
            )ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    sql = sqlBuf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

bool CMainMenueModel::agreeStudentRequestByStudentId(const char* acount
                                    ,const char* className
                                    ,const char* studentId)
{
    if(acount == nullptr || className == nullptr || studentId == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"delete from `requestJoinClass` \
where `studentId` = '%s' and `className` = '%s' and `teacherId` = '%s';"
            ,studentId,className,acount);
    sql = sqlBuf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");

    //进行添加成员信息到该教师的课程表中
    memset(sqlBuf,'\0',sizeof(char)*1024000);
    sprintf(sqlBuf,"insert into `joinClassStudentManeage` (`studentId`,`joinTime`,`className`,`teacherId`) values('%s',now(),'%s','%s');",studentId,className,acount);
    sql = sqlBuf;
    ret = dbHelper->sqlExcute(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

int CMainMenueModel::getStudentRequestByRequestTimeCount(const char* acount
                                        ,const char* className
                                        ,const char* requestTime)
{
    if(acount == nullptr || className == nullptr || requestTime == nullptr)
    {
        return -1;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select count(*) from `requestJoinClass` \
            where `teacherId` = '%s' and `className` = '%s' \
            and `requestTime` like '%%%s%%';",acount,className,requestTime);
            sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    delete[] sqlBuf;
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
        result += 1;
    }else
    {
        int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    delete dbHelper;
    return result;
}

std::vector<std::vector<std::string>> CMainMenueModel::getStudentRequestByRequestTime(const char* acount
                                                                                      ,const char* className
                                                                                      ,int curIndex,const char* requestTime)
{
    if(acount == nullptr || className == nullptr || requestTime == nullptr || curIndex == -1)
    {
        return std::vector<std::vector<std::string>>();
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `studentName`,`studentId`,`requestTime` from `requestJoinClass` \
where  `teacherId` = '%s' and  `className` = '%s' and `requestTime` like '%%%s%%' \
limit 8 offset %d;",acount,className,requestTime,(curIndex - 1) * 8);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    return ret;

}


int CMainMenueModel::getStudentRequestByStudentIdCount(const char* acount
                                                       ,const char* className
                                                       ,const char* studentId)
{
    if(acount == nullptr || className == nullptr || studentId == nullptr)
    {
        return -1;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select count(*) from `requestJoinClass` \
            where `teacherId` = '%s' and `className` = '%s' \
            and `studentId` like '%%%s%%';",acount,className,studentId);
            sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    delete[] sqlBuf;
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
        result += 1;
    }else
    {
        int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    delete dbHelper;
    return result;
}


std::vector<std::vector<std::string>> CMainMenueModel::getStudentRequestByStudentId(const char* acount
                                                                   ,const char* className
                                                                   ,int curIndex,const char* studentId)
{
    if(acount == nullptr || className == nullptr || studentId == nullptr || curIndex == -1)
    {
        return std::vector<std::vector<std::string>>();
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `studentName`,`studentId`,`requestTime` from `requestJoinClass` \
where  `teacherId` = '%s' and  `className` = '%s' and `studentId` like '%%%s%%' \
limit 8 offset %d;",acount,className,studentId,(curIndex - 1) * 8);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

int CMainMenueModel::getStudentRequestByStudentNameCount(const char* acount
                                        ,const char* className
                                        ,const char* studentName)
{
    if(acount == nullptr || className == nullptr || studentName == nullptr)
    {
        return -1;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select count(*) from `requestJoinClass` \
where `teacherId` = '%s' and `className` = '%s' \
and `studentName` like '%%%s%%';",acount,className,studentName);
    sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    delete[] sqlBuf;
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
         result += 1;
    }else
    {
       int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    delete dbHelper;
    return result;
}


std::vector<std::vector<std::string>> CMainMenueModel::getStudentRequestByStudentName(const char* acount
                                                                     ,const char* className
                                                                     ,int curIndex,const char* studentName)
{
    if(acount == nullptr || className == nullptr || studentName == nullptr || curIndex == -1)
    {
        return std::vector<std::vector<std::string>>();
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `studentName`,`studentId`,`requestTime` from `requestJoinClass` \
where  `teacherId` = '%s' and  `className` = '%s' and `studentName` like '%%%s%%' \
limit 8 offset %d;",acount,className,studentName,(curIndex - 1) * 8);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}


int CMainMenueModel::getStudentRequestTableCount(const char* acount,const char* className,int curIndex)
{
    if(acount == nullptr || className == nullptr)
    {
        return -1;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select count(*) from `requestJoinClass` \
where `teacherId` = '%s' and `className` = '%s';",acount,className);
    sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    delete[] sqlBuf;
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
         result += 1;
    }else
    {
       int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    delete dbHelper;
    return result;
}

std::vector<std::vector<std::string>> CMainMenueModel::getStudentRequestTableData(const char* className
                                                                 ,const char* acount
                                                                 ,int curIndex)
{
    if(className == nullptr || acount == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select  `studentName`,`studentId`,`requestTime` from `requestJoinClass`\
 where `teacherId` = '%s' and `className` = '%s' limit 8 offset %d;",acount,className,(curIndex - 1) * 8);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

 bool CMainMenueModel::initStudentRequestDataBaseTable()
 {
     //对于std::shared_ptr管理单个对象内存使用make::shared进行分配内存，并且相对于new效率更高
     //shared_ptr管理对象数组内存的时候就使用new的方式来进行管理内存，例如：std::shared_ptr<type[]> ptr (new type[1024000],std::default_delete<type[]>());
     //std::unique_ptr更适合用于管理对象数组，只不过是独占式，只有一个指针指向对象，并且不能进行拷贝，但是能进行移动 例：std::unique_ptr<char[]> ptr(new char[1024000]);
//      std::shared_ptr<CDBHelper> ptr = std::make_shared<CDBHelper>(); //std::shared_ptr用于管理单个对象的内存
      CDBHelper* dbHelper = new CDBHelper();
//      std::shared_ptr<char[]> sqlBuf(new char[1024000],std::default_delete<char[]>());
//      std::unique_ptr<char[]> sqlBuf(new char[1024000]);
      char* sqlBuf = new char[1024000];
      memset(sqlBuf,'\0',sizeof(char) * 1024000);
      std::string sql;
      sprintf(sqlBuf,"create table if not exists `requestJoinClass`(\n\
`id` integer primary key auto_increment,\n\
`studentName` varchar(20) not null,\n\
`studentId`  varchar(20) not null,\n\
foreign key(`studentId`) references `Student`(`studentId`),\n\
`requestTime` datetime not null,\n\
`className` varchar(50) not null,\n\
`teacherId` varchar(20)  not null,\n\
foreign key(`teacherId`) references `Teacher`(`teacherId`)\n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;");
//      sql = sqlBuf.get();
      sql = sqlBuf;
//      bool ret = ptr->sqlExcute(sql,"ExamSystem");
      bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
      delete dbHelper;
      delete[] sqlBuf;
      return ret;
}

std::vector<std::vector<std::string>> CMainMenueModel::showClassIconInStudentRequest(const char* acount,
                                                                    const char* className)
{
    if(acount == nullptr || className == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    CDBHelper* dbHelepr = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `classIconPath` from `class` \
where `className` = '%s' and `teacherId` = '%s';",className,acount);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret = dbHelepr->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelepr;
    return ret;
}

bool CMainMenueModel::deleteClassInfoByDateTime(const char* acount,const char* createTime,const char* className)
{
    if(acount == nullptr || createTime == nullptr || className == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];

    std::string sql;

    //先删除该课程相关的申请表的所有记录
    memset(sqlBuf,'\0',sizeof(char)*1024000);
    sprintf(sqlBuf,"delete from `requestJoinClass`  where `className` = '%s' and `teacherId` = '%s';",className,acount);
    sql = sqlBuf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");

    //删除该课程相关的学生管理记录
    memset(sqlBuf,'\0',sizeof(char)*1024000);
    sprintf(sqlBuf,"delete from `joinClassStudentManeage`  where `className` = '%s' and `teacherId` = '%s';",className,acount);
    sql = sqlBuf;
    ret =  dbHelper->sqlExcute(sql,"ExamSystem");

    memset(sqlBuf,'\0',sizeof(char)*1024000);
    sprintf(sqlBuf,"delete from `class`  where `createTime` = '%s' and `teacherId` = '%s';",createTime,acount);
    sql = sqlBuf;
    ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

int CMainMenueModel::getClassTableCount(const char* acount)
{
    if(acount == nullptr)
    {
        return -1;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select count(*) from  `class` where `teacherId` = '%s';",acount);
    sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
         result += 1;
    }else
    {
       int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    delete[] sqlBuf;
    delete dbHelper;
    return result;
}

std::vector<std::vector<std::string>> CMainMenueModel::getClassTableData(const char* acount,int curPageIndex)
{
    if(acount == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }

    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `classIconPath`,`className`,`createTime`,(select `name` from `TeacherInfo` where `teacherId` = '%s') AS name from `class` \
where `teacherId` = '%s' limit 8 offset %d;",acount,acount,(curPageIndex - 1) * 8);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

bool CMainMenueModel::initClassTableDatabase()
{
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"create table if not exists `class`(\n\
`id` integer  primary key auto_increment,\n\
`classIconPath` varchar(100) not null,\n\
`className` varchar(50) not null,\n\
`createTime` datetime not null,\n\
`teacherId` varchar(20)  not null,\n\
foreign key(`teacherId`) references `Teacher`(`teacherId`)\n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    sql = sqlBuf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

bool CMainMenueModel::deleteFromShortAnswer(const char* acount,const char* createTime)
{
    if(acount == nullptr || createTime == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;

    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"delete from `shortAnswer` where `testPaperId` in (select `testPaperId` from `testPaperInfo` where `saveTime` = '%s' and `teacherId` = '%s');",createTime,acount);
    sql = sqlBuf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");

    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}


bool CMainMenueModel::deleteFromJudge(const char* acount,const char* createTime)
{
    if(acount == nullptr || createTime == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;

    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"delete from `judge` where `testPaperId` in (select `testPaperId` from `testPaperInfo` where `saveTime` = '%s' and `teacherId` = '%s');",createTime,acount);
    sql = sqlBuf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");

    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

bool CMainMenueModel::deleteFromMultiChoise(const char* acount,const char* createTime)
{
    if(acount == nullptr || createTime == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;

    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"delete from `multiChoice`   where `testPaperId` in (select `testPaperId` from `testPaperInfo` where `saveTime` = '%s' and `teacherId` = '%s');",createTime,acount);
    sql = sqlBuf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");

    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

bool CMainMenueModel::deleteFromSignalChoise(const char* acount,const char* createTime)
{
    if(acount == nullptr || createTime == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;

    sprintf(sqlBuf,"delete from `singleChoice`  where  `testPaperId` in (select `testPaperId` from `testPaperInfo` where `saveTime` = '%s' and `teacherId` = '%s');",createTime,acount);
    sql = sqlBuf;
    qDebug()<<sql.c_str();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");

    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

bool CMainMenueModel::deleteClickBtn(const char* acount,const char* createTime)
{
    if(acount == nullptr || createTime == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;

    bool ret = false;
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf," delete from `testPaperInfo` where `saveTime` = '%s' and `teacherId` = '%s';",createTime,acount);
    sql = sqlBuf;
    ret =  dbHelper->sqlExcute(sql,"ExamSystem");

    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

int CMainMenueModel::getTableDataByFindTestNameCount(const char* acount,const char* testPaperName)
{
    if(acount == nullptr || testPaperName == nullptr)
    {
        return -1;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select count(*) from `testPaperInfo` \
where  `teacherId` = '%s' and `testPaperName` like '%%%s%%';",acount,testPaperName);
    sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
         result += 1;
    }else
    {
       int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    delete[] sqlBuf;
    delete dbHelper;
    return result;
}


std::vector<std::vector<std::string>> CMainMenueModel::getCurPageIndexTableDataNotPubulished(
                                                                             int curPageIndex
                                                                            ,const char* acount
                                                                            ,const char* status)
{
    if(acount == nullptr || status == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new  char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"SELECT \n\
tp.testPaperName,\n\
(\n\
COALESCE((SELECT COUNT(*) FROM singleChoice sc WHERE sc.testPaperId = tp.testPaperId), 0) +\n\
COALESCE((SELECT COUNT(*) FROM multiChoice mc WHERE mc.testPaperId = tp.testPaperId), 0) +\n\
COALESCE((SELECT COUNT(*) FROM judge j WHERE j.testPaperId = tp.testPaperId), 0) +\n\
COALESCE((SELECT COUNT(*) FROM shortAnswer sa WHERE sa.testPaperId = tp.testPaperId), 0)\n\
) AS totalQuestionCount,\n\
tp.saveTime,\n\
t.name AS teacherName,\n\
tp.publishStatus,\n\
tp.teacherId,\n\
tp.testPaperId\n\
FROM \n\
testPaperInfo tp\n\
JOIN \n\
TeacherInfo t ON tp.teacherId = t.teacherId\n\
WHERE \n\
tp.teacherId = '%s'\n\
AND \n\
tp.publishStatus = '%s' \n\
ORDER BY \n\
tp.testPaperId\n\
LIMIT 8 OFFSET %d;",acount,status,(curPageIndex - 1)* 8);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    for(int i = 0 ; i < ret.size();i++)
    {
        if(ret.at(i).at(4) == "0")
        {
            QString strTemp = "未发布";
            QByteArray tempArr = strTemp.toLocal8Bit();
            ret.at(i).at(4) = tempArr.data();
        }else if(ret.at(i).at(4) == "1")
        {
            QString strTemp = "以发布";
            QByteArray tempArr = strTemp.toLocal8Bit();
            ret.at(i).at(4) = tempArr.data();
        }
    }
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

int CMainMenueModel::getTablePageCountNotPublished(const char* acount,const char* status)
{
    if(acount == nullptr || status == nullptr)
    {
        return -1;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select count(*) from `testPaperInfo` \
where  `teacherId` = '%s' and `publishStatus` = '%s';",acount,status);
    sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
         result += 1;
    }else
    {
       int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    delete[] sqlBuf;
    delete dbHelper;
    return result;
}

std::vector<std::vector<std::string>> CMainMenueModel::getTableDataByFindTestName(int curPageIndex,
                                                                 const char* acount,
                                                                 const char* testPaperName)
{
    if(acount == nullptr || testPaperName == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"SELECT \n\
tp.testPaperName,\n\
(\n\
COALESCE((SELECT COUNT(*) FROM singleChoice sc WHERE sc.testPaperId = tp.testPaperId), 0) +\n\
COALESCE((SELECT COUNT(*) FROM multiChoice mc WHERE mc.testPaperId = tp.testPaperId), 0) +\n\
COALESCE((SELECT COUNT(*) FROM judge j WHERE j.testPaperId = tp.testPaperId), 0) +\n\
COALESCE((SELECT COUNT(*) FROM shortAnswer sa WHERE sa.testPaperId = tp.testPaperId), 0)\n\
) AS totalQuestionCount,\n\
tp.saveTime,\n\
t.name AS teacherName,\n\
tp.publishStatus,\n\
tp.teacherId,\n\
tp.testPaperId\n\
FROM \n\
testPaperInfo tp\n\
JOIN \n\
TeacherInfo t ON tp.teacherId = t.teacherId\n\
WHERE \n\
tp.teacherId = '%s'\n\
AND \n\
tp.testPaperName like  '%%%s%%'\n\
ORDER BY \n\
tp.testPaperId\n\
LIMIT 8 OFFSET %d;",acount,testPaperName,(curPageIndex -1)*8);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    for(int i = 0 ; i < ret.size();i++)
    {
        if(ret.at(i).at(4) == "0")
        {
            QString strTemp = "未发布";
            QByteArray tempArr = strTemp.toLocal8Bit();
            ret.at(i).at(4) = tempArr.data();
        }else if(ret.at(i).at(4) == "1")
        {
            QString strTemp = "以发布";
            QByteArray tempArr = strTemp.toLocal8Bit();
            ret.at(i).at(4) = tempArr.data();
        }
    }
    return ret;
}


int CMainMenueModel::getTablePageCountPublished(
        const char* acount,
        const char* status)
{
    if(acount == nullptr || status == nullptr)
    {
        return -1;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select count(*) from `testPaperInfo` \
where  `teacherId` = '%s' and `publishStatus` = '%s';",acount,status);
    sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
         result += 1;
    }else
    {
       int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    delete[] sqlBuf;
    delete dbHelper;
    return result;
}


std::vector<std::vector<std::string>> CMainMenueModel::getCurPageIndexTableDataPubulished(int curPageIndex,
                                                                         const char* acount,
                                                                         const char* status)
{
    if(acount == nullptr || status == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"SELECT \n\
tp.testPaperName,\n\
(\n\
COALESCE((SELECT COUNT(*) FROM singleChoice sc WHERE sc.testPaperId = tp.testPaperId), 0) +\n\
COALESCE((SELECT COUNT(*) FROM multiChoice mc WHERE mc.testPaperId = tp.testPaperId), 0) +\n\
COALESCE((SELECT COUNT(*) FROM judge j WHERE j.testPaperId = tp.testPaperId), 0) +\n\
COALESCE((SELECT COUNT(*) FROM shortAnswer sa WHERE sa.testPaperId = tp.testPaperId), 0)\n\
) AS totalQuestionCount,\n\
tp.saveTime,\n\
t.name AS teacherName,\n\
tp.publishStatus,\n\
tp.teacherId,\n\
tp.testPaperId\n\
FROM \n\
testPaperInfo tp\n\
JOIN \n\
TeacherInfo t ON tp.teacherId = t.teacherId\n\
WHERE \n\
tp.teacherId = '%s'\n\
AND \n\
tp.publishStatus = '%s' \n\
ORDER BY \n\
tp.testPaperId\n\
LIMIT 8 OFFSET %d;",acount,status,(curPageIndex - 1)* 8);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    //对容器中的最后一列进行处理(发布状态)
    for(int i = 0 ; i < ret.size();i++)
    {
        if(ret.at(i).at(4) == "0")
        {
            QString strTemp = "未发布";
            QByteArray tempArr = strTemp.toLocal8Bit();
            ret.at(i).at(4) = tempArr.data();
        }else if(ret.at(i).at(4) == "1")
        {
            QString strTemp = "以发布";
            QByteArray tempArr = strTemp.toLocal8Bit();
            ret.at(i).at(4) = tempArr.data();
        }
    }
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

//极大提升了查询单表的速度，优化方案就是减少对数据库的多次访问，尽量一个sql解决
std::vector<std::vector<std::string>> CMainMenueModel::showCurPageIndexTable(int curPageIndex,char* acount)
{
    if(curPageIndex == 0 || acount == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    // 返回的数据集是一个表
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    /*CDBHelper* dbHelper = new CDBHelper();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    std::string sql;
    //拿到试卷表的全部 试卷名称，创建时间，发布状态
    sprintf(sqlBuf,"select `testPaperName`,`saveTime`,`publishStatus` from `testPaperInfo`\
 where `teacherId` = '%s' order by `testPaperId` limit 8 offset %d;",acount,((curPageIndex -1) * 8));
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret = dbHelper->sqlQuery(sql,"ExamSystem");

    //拿到每一份试卷的题量和出题人

    //获取所有符合条件的记录的出题量
    //1、拿到所有属于这个用户的所有的试卷id
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"select `testPaperId` from `testPaperInfo` where `teacherId` = '%s' limit 8 offset %d;",acount,((curPageIndex -1) * 8));
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret2 = dbHelper->sqlQuery(sql,"ExamSystem");

    //2、根据每一个试卷id进行查询所有的类型的题库的试题总数，并且求和，放入容器中
    std::vector<std::vector<std::string>> ret3;
    for(int i = 0 ; i < ret2.size();i++) //忽略第一个 id为0 的
    {

        //查询单选题总数
        memset(sqlBuf,'\0',sizeof(char) * 1024);
        sprintf(sqlBuf,"select count(*) from `singleChoice` where `testPaperId` = %s;",ret2.at(i).at(0).c_str());
        sql = sqlBuf;
        int count1 =  dbHelper->sqlQueryCount(sql,"ExamSystem");

        //查询多选题总数
        memset(sqlBuf,'\0',sizeof(char) * 1024);
        sprintf(sqlBuf,"select count(*) from `multiChoice` where `testPaperId` = %s;",ret2.at(i).at(0).c_str());
        sql = sqlBuf;
        int count2 =  dbHelper->sqlQueryCount(sql,"ExamSystem");

        //查询判断题总数
        memset(sqlBuf,'\0',sizeof(char) * 1024);
        sprintf(sqlBuf,"select count(*) from `judge` where `testPaperId` = %s;",ret2.at(i).at(0).c_str());
        sql = sqlBuf;
        int count3 =  dbHelper->sqlQueryCount(sql,"ExamSystem");

        //查询简答题总数
        memset(sqlBuf,'\0',sizeof(char) * 1024);
        sprintf(sqlBuf,"select count(*) from `shortAnswer` where `testPaperId` = %s;",ret2.at(i).at(0).c_str());
        sql = sqlBuf;
        int count4 =  dbHelper->sqlQueryCount(sql,"ExamSystem");

        int allCount = count1 + count2 + count3 + count4;
        char buf[200];
        memset(buf,'\0',sizeof(char) * 200);
        itoa(allCount,buf,10);
        std::vector<std::string> temp;
        temp.push_back(buf);
        ret3.push_back(std::move(temp));
    }

    //获取每一份试卷，根据试卷的职工id进行查询职工姓名
    memset(sqlBuf,'\0',sizeof(char) * 1024);
    sprintf(sqlBuf,"select `name` from `TeacherInfo` where `teacherId` = '%s';",acount);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> name =  dbHelper->sqlQuery(sql,"ExamSystem");

    //进行重组，组成记录表，进行返回
    std::vector<std::vector<std::string>> result;
    qDebug()<<"ret.size: "<<ret.size()<<"ret2.size:"<<ret2.size()<<"ret3.size: "<<ret3.size();
    for(int i = 0 ; i < ret.size() ; i++) // 7列 8行
    {
          std::vector<std::string> temp;
          //插入试卷名称
          temp.push_back(ret.at(i).at(0));

          //插入题量
          temp.push_back(ret3.at(i).at(0));

          //插入创建时间
          temp.push_back(ret.at(i).at(1));

          //插入出卷人
          temp.push_back(name.at(0).at(0));

          QString strTemp;
          //插入发布状态
          if(ret.at(i).at(2) == "0")
          {
              strTemp = "未发布";
              QByteArray tempArr = strTemp.toLocal8Bit();
              temp.push_back(tempArr.data());
          }else if(ret.at(i).at(2) == "1")
          {
              strTemp = "以发布";
              QByteArray tempArr = strTemp.toLocal8Bit();
              temp.push_back(tempArr.data());
          }
          result.push_back(std::move(temp));
    }*/
    /*测试打印结果的值*/
   /* qDebug()<<"测试循环进入";
    for(int i = 1 ; i < result.size();i++)
    {
        for(int j = 0; j < result.at(i).size();j++)
        {
            std::cout<<result.at(i).at(j).c_str()<<" ";
        }
        std::cout<<std::endl;
    }*/
    //拿到的存储结果不访问第一行，第一行是测试行
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
        //拿到试卷表的全部 试卷名称，创建时间，发布状态
    sprintf(sqlBuf,"SELECT tp.testPaperName,(\n\
COALESCE((SELECT COUNT(*) FROM singleChoice sc WHERE sc.testPaperId = tp.testPaperId), 0) +\n\
COALESCE((SELECT COUNT(*) FROM multiChoice mc WHERE mc.testPaperId = tp.testPaperId), 0) +\n\
COALESCE((SELECT COUNT(*) FROM judge j WHERE j.testPaperId = tp.testPaperId), 0) +\n\
COALESCE((SELECT COUNT(*) FROM shortAnswer sa WHERE sa.testPaperId = tp.testPaperId), 0)\n\
) AS totalQuestionCount,\n\
tp.saveTime,\n\
t.name AS teacherName,\n\
tp.publishStatus,\n\
tp.teacherId,\n\
tp.testPaperId\n\
FROM \n\
testPaperInfo tp\n\
JOIN \n\
TeacherInfo t ON tp.teacherId = t.teacherId\n\
WHERE \n\
tp.teacherId = '%s'\n\
ORDER BY \n\
tp.testPaperId\n\
LIMIT 8 OFFSET %d;",acount,((curPageIndex -1) * 8)); //这里limite 9 的原因是因为第一行数据不是我们需要显示的
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret = dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    qDebug()<<sql.c_str();
    //对容器中的最后一列进行处理(发布状态)
    for(int i = 0 ; i < ret.size();i++)
    {
        if(ret.at(i).at(4) == "0")
        {
            QString strTemp = "未发布";
            QByteArray tempArr = strTemp.toLocal8Bit();
            ret.at(i).at(4) = tempArr.data();
        }else if(ret.at(i).at(4) == "1")
        {
            QString strTemp = "已发布";
            QByteArray tempArr = strTemp.toLocal8Bit();
            ret.at(i).at(4) = tempArr.data();
        }
    }
    delete dbHelper;
    return ret;
}

QString CMainMenueModel::getTablePageCount(char* acount)
{
    if(acount == nullptr)
    {
        return "";
    }
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select count(*) from `testPaperInfo` where `teacherId` = '%s';",acount);
    sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    delete[] sqlBuf;
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
         result += 1;
    }else
    {
       int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }    
    }
    delete dbHelper;
    return QString::number(result);
}

bool CMainMenueModel::addShortAnswerInfo(double grade,const char* question,
                                         const char* referenceAnswer,const char* teacherId,int order)
{
    if(question == nullptr || referenceAnswer == nullptr|| teacherId == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"insert into  `shortAnswer` (`grade`,`question`,`referenceAnswer`,`order`,`teacherId`)\
 values(%lf,'%s','%s',%d,'%s');",grade,question,referenceAnswer,order,teacherId);
 std::string sql = sqlBuf;
   delete[] sqlBuf;
   bool ret =   dbHelper->sqlExcute(sql,"ExamSystem");
   delete dbHelper;
   return ret;
}

bool CMainMenueModel::addJudgeInfo(double grade,const char* question,const char* sessionTrue,
                  const char* sessionFalse,
                  const char* correctAnswer,const char* teacherId,int order)
{
    if(question==nullptr || sessionFalse == nullptr
      ||sessionTrue == nullptr || correctAnswer == nullptr ||teacherId == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"insert into  `judge` (`grade`,`question`,`sessionTrue`,`sessionFalse`,`order`,`correctAnswer`,`teacherId`)\
values(%lf,'%s','%s','%s',%d,'%s','%s');",grade,question,sessionTrue,sessionFalse,order,correctAnswer,teacherId);
 std::string sql = sqlBuf;
    delete[] sqlBuf;
    bool ret =   dbHelper->sqlExcute(sql,"ExamSystem");
    delete dbHelper;
    return ret;
}

bool CMainMenueModel::addMultiChoiceInfo(double grade,const char* question,const char* sessionA,
                        const char* sessionB,const char* sessionC,const char* sessionD,
                        const char* sessionE,const char* sessionF,const char* correctOpetions,
                        const char* teacherId,int order)
{
    if(question == nullptr || sessionA == nullptr||
       sessionB == nullptr || sessionC == nullptr||
       sessionD == nullptr || sessionE == nullptr||
       sessionF == nullptr || teacherId == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"insert into  `multiChoice` (`grade`,`question`,`sessionA`,`sessionB`,\
`sessionC`,`sessionD`,`sessionE`,`sessionF`,`correctOptions`,`order`,`teacherId`)\
 values(%lf,'%s','%s','%s','%s','%s','%s','%s','%s',%d,'%s');",grade,question,sessionA,sessionB,
    sessionC,sessionD,
    sessionE,sessionF,correctOpetions,order,teacherId);
 std::string sql = sqlBuf;
 delete[] sqlBuf;
 bool ret =   dbHelper->sqlExcute(sql,"ExamSystem");
 delete dbHelper;
 return ret;
}

void CMainMenueModel::changeHeadPicture(char* localFilePath ,char* fileName,char* acount)
{
    if(localFilePath == nullptr || fileName == nullptr || acount == nullptr)
    {
        return ;
    }
    //先进行网络通信，将头像上传到服务器磁盘保存
    FILE* pFile = fopen(localFilePath,"rb+");
    if(pFile == nullptr)
    {
        fclose(pFile);
        return;
    }

    fseek(pFile,0,SEEK_END);
    long long fileSize =  _ftelli64(pFile);
    fseek(pFile,0,SEEK_SET);

    std::string headPath = "/root/picture/";
    headPath += fileName;
    qDebug()<<headPath.size();
    char* data = new char[2 + fileSize + headPath.size()]; //全是文件数据
    memset(data,'\0',sizeof(char) * (2 + fileSize + headPath.size()));
    WORD pathLenght = headPath.size();
    memcpy(data,&pathLenght,sizeof(WORD));
    long long size =  fread(data + 2,1,fileSize,pFile);
    fclose(pFile);
    memcpy(data + fileSize + 2,headPath.c_str(),headPath.size());
    //进行封包操作
//    CClientSocket* clientsocket = CClientSocket::getInstance();
    CClientSocket* clientsocket = new CClientSocket();
    clientsocket->initSocket();
    bool ret =  clientsocket->connectToServer();
    if(!ret)
    {
        return;
    }
    clientsocket->makePacket(data,fileSize + headPath.size() + 2,1);
    char* packet =  clientsocket->getPacket();
    clientsocket->Send(packet);
    delete[] data;
    clientsocket->closeSocket();
    delete clientsocket;
    //对数据库进行操作,更该当前用户的头像的存储路径
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(sqlBuf));

    sprintf(sqlBuf,"update  `TeacherInfo` set `profilePicture` = '%s' where `teacherId` = '%s'; ",headPath.c_str(),acount);
    std::string sql = sqlBuf;
    bool ret2 =   dbHelper->sqlExcute(sql,"ExamSystem");
    delete dbHelper;
    return;
}

void CMainMenueModel::changeGender(bool isMan,char* pAcount)
{
    std::string gender;
    if(isMan)
    {
        gender = "1";
    }else
    {
        gender = "0";
    }
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"update  `TeacherInfo` set `gender` = '%s' where `teacherId` = '%s'; ",gender.c_str(),pAcount);
    std::string sql  = sqlBuf;
    delete[] sqlBuf;
    bool ret =   dbHelper->sqlExcute(sql,"ExamSystem");
    delete dbHelper;
    return;
}

std::vector<std::vector<std::string>> CMainMenueModel::showTeacherAcountInfo(char* pAcount)
{
    if(pAcount == nullptr)
    {
        return std::vector<std::vector<std::string>>(); //返回一个空结果集
    }
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"select `name`,`teacherId`,`gender`,`phoneNumber` from `TeacherInfo` where `teacherId` = '%s';",pAcount);
    sql = sqlBuf;
    delete[] sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete dbHelper;
    return ret;
}

//显示主页头像和姓名
std::vector<std::vector<std::string>> CMainMenueModel::showTeacherInfo(char* pAcount)
{
    if(pAcount == nullptr)
    {
        return std::vector<std::vector<std::string>>(); //返回一个空结果集
    }
    //进行查询显示 姓名和头像
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    char sqlBuf[1024];
    memset(sqlBuf,0,sizeof(char)*1024);
    sprintf(sqlBuf,"select `name`,`profilePicture` from `TeacherInfo` where `teacherId` = '%s';",pAcount);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete dbHelper;
    return ret;
}

//进行建表操作
bool CMainMenueModel::initTeacherInfoTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    sql= "create table if not exists `TeacherInfo`\
(\
`id` integer primary key auto_increment,\
`teacherId` varchar(20)  not null,\
foreign key(`teacherId`) references `Teacher`(`teacherId`),\
`name` varchar(10) not null default '未设置',\
`gender`  varchar(2) not null  default '1',\
`phoneNumber` varchar(20) not null default '未设置',\
`profilePicture` varchar(100) not null default '/root/picture/defaultHead.png')\
ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
   std::cout<<"initTeacherInfoTable task end"<<std::endl;
   delete dbHelper;
   return ret;
}

bool CMainMenueModel::initSingleChoiceTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    //std::cout<<"initSingleChoiceTable task1 end"<<std::endl;
    sql= "create table  if not exists `singleChoice`(\
`id` integer primary key auto_increment,\
`grade` double default 0.0 not null,\
`question` varchar(1000)   not null default '',\
`sessionA` varchar(1000)  not null default '',\
`sessionB` varchar(1000)  not null default '',\
`sessionC` varchar(1000)  not null default '',\
`sessionD` varchar(1000) not null default '',\
`correctOptions` varchar(2) not null,\
`order` integer not null default  0,\
`teacherId` varchar(20) not null , \
`testPaperId` integer not null default 0,\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`)\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
   std::cout<<"initSingleChoiceTable task end"<<std::endl;
   delete dbHelper;
   return ret;
}

bool CMainMenueModel::initMultiChoiceTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    sql= "create table  if not exists `multiChoice`(\
`id` integer primary key auto_increment,\
`grade` double default 0.0 not null,\
`question` varchar(1000)   not null default '',\
`sessionA` varchar(1000)  not null default '',\
`sessionB` varchar(1000)  not null default '',\
`sessionC` varchar(1000)  not null default '',\
`sessionD` varchar(1000) not null default '',\
`sessionE` varchar(1000) not null default '',\
`sessionF` varchar(1000) not null default '',\
`correctOptions` varchar(20) not null,\
`order` integer not null default  0,\
`teacherId` varchar(20) not null ,\
`testPaperId` integer not null default 0,\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`)\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
   delete dbHelper;
   std::cout<<"initMultiChoiceTable task end"<<std::endl;
   return ret;
}

bool CMainMenueModel::initJudgeTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    sql= "create table  if not exists `judge`(\
`id` integer primary key auto_increment,\
`grade` double default 0.0 not null,\
`question` varchar(1000)   not null default '',\
`sessionTrue` varchar(1000)  not null default '',\
`sessionFalse` varchar(1000)  not null default '',\
`correctAnswer` varchar(2) not null,\
`order` integer not null default  0,\
`teacherId` varchar(20) not null ,\
`testPaperId` integer not null default 0,\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`)\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
   std::cout<<"initJudgeTable task end"<<std::endl;
   delete dbHelper;
   return ret;
}

bool CMainMenueModel::initShortAnswerTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    sql= "create table  if not exists `shortAnswer`(\
`id` integer primary key auto_increment,\
`grade` double default 0.0 not null,\
`question` varchar(1000)   not null default '',\
`referenceAnswer` varchar(2000) not null,\
`order` integer not null default  0,\
`teacherId` varchar(20) not null ,\
`testPaperId` integer not null default 0,\
foreign key(`testPaperId`) references `testPaperInfo`(`testPaperId`)\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
   std::cout<<"initShortAnswerTable task end"<<std::endl;
   delete dbHelper;
   return ret;
}

bool CMainMenueModel::initTestPaperTable()
{
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    sql = "use `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    sql= "create table if not exists `testPaperInfo`(\
`testPaperId` integer primary key auto_increment,\
`testPaperName` varchar(100) not null ,\
`saveTime` datetime not null,\
`publishStatus` varchar(2) not null default '0',\
`teacherId` varchar(20)  not null,\
foreign key(`teacherId`) references `Teacher`(`teacherId`)\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   sql =  dbHelper->multiMytesChange(sql);
   bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
   std::cout<<"initTestPaperTable task end"<<std::endl;
   delete dbHelper;
   return ret;
}

bool CMainMenueModel::addSignalChoiceInfo(double grade,const char* question,const char* sessionA,
                         const char* sessionB,const char* sessionC,const char* sessionD,
                         const char* correctOptions,const char* teacherId,int order)
{
    if(question == nullptr||question == nullptr || sessionA == nullptr||
            sessionB == nullptr || sessionC == nullptr
            ||sessionD == nullptr||correctOptions == nullptr|| teacherId == nullptr)
    {
        return false;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"insert into  `singleChoice` \
(`grade`,`question`,`sessionA`,`sessionB`,`sessionC`,`sessionD`,`correctOptions`,`order`,`teacherId`)\
 values('%lf','%s','%s','%s','%s','%s','%s','%d','%s');",grade,question,sessionA,
            sessionB,sessionC,sessionD,correctOptions,order,teacherId);
 std::string sql = sqlBuf;
 delete[] sqlBuf;
 bool ret =   dbHelper->sqlExcute(sql,"ExamSystem");
 delete dbHelper;
 return ret;
}
