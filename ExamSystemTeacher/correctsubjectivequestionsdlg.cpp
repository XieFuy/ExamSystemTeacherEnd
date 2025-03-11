#include "correctsubjectivequestionsdlg.h"
#include "ui_correctsubjectivequestionsdlg.h"

CCorrectSubjectiveQuestionsDlg::CCorrectSubjectiveQuestionsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCorrectSubjectiveQuestionsDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("主观题批改对话框");
    this->setWindowIcon(QIcon(":/icons/judge.png"));
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->testPaperName = "";
    this->studentName = "";
    this->subject = "";
    this->order = 1;
    this->m_contorler = std::make_shared<CCorrectSubjectiveQuestionsContorler>();
    this->isExist = false;

    QObject::connect(this,&CCorrectSubjectiveQuestionsDlg::startShowDlg,[=](){
        this->ui->label_84->setText(this->testPaperName);
        this->ui->label_87->setText(this->subject);
        this->ui->label_86->setText(this->studentName);

        //进行更新试卷批改状态
        this->updateTestPaperCorrectStatus();
    });

    QObject::connect(this->ui->pushButton_26,&QPushButton::clicked,[=](){
        //进行存储该学生的成绩
        this->checkScoreExist();
        emit this->rejected();
    });

    //将Ui中的简答题题号按钮加入到容器中
    for(int i = 251;i <= 328 ; i++)
    {
        QString strName = "pushButton_";
        strName += QString::number(i);
        QPushButton* btn =  this->findChild<QPushButton*>(strName);
        this->m_shortAnswerChoice.push_back(btn);
    }

    //给简答题的每一个按钮进行设置样式
    int i = 1;
    for(QPushButton* btn: this->m_shortAnswerChoice)
    {
        btn->setText(QString::number(i++));
        btn->setFont(QFont("黑体",12));
        btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
    }

    //简答题题号进行信号槽绑定，实现单击只有一个题号是绿色
    for(QPushButton* btn : this->m_shortAnswerChoice)
    {
        QObject::connect(btn,&QPushButton::clicked,[=](){
            //被点击的按钮设置为绿色，其他的所有按钮恢复原来的状态
            btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;background-color:green;}");
            for(QPushButton* btn2 : this->m_shortAnswerChoice)
            {
                if(btn2 != btn)
                {
                    btn2->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
                }
            }
            //拿到被点击的按钮的题号数
            QString str = btn->text().trimmed();
            int num = str.toInt();
            //设置题号
            this->order = num;
//            //更新当前题的下标
//            this->shortAnswerCurIndex = num;
            //获取当先题的题干，学生答案,参考答案
            this->getCurOrderShortAnswer();
            this->getCurOrderAnswer();
            this->getCurShortAnswerScore();
        });
    }

    //将简答题题号按钮进行隐藏
    for(QPushButton* btn : this->m_shortAnswerChoice)
    {
        btn->setVisible(false);
    }

    QObject::connect(this,&CCorrectSubjectiveQuestionsDlg::startShowShortAnswer,this,&CCorrectSubjectiveQuestionsDlg::showShortAnswerUI);
    QObject::connect(this,&CCorrectSubjectiveQuestionsDlg::startShowAnswer,this,&CCorrectSubjectiveQuestionsDlg::showAnswerUI);
    QObject::connect(this,&CCorrectSubjectiveQuestionsDlg::startShowShortAnswerBtn,this,&CCorrectSubjectiveQuestionsDlg::showSHortAnswerBtn);
    QObject::connect(this->ui->pushButton_249,&QPushButton::clicked,this,&CCorrectSubjectiveQuestionsDlg::getLastShortAnswerChoice);
    QObject::connect(this->ui->pushButton_250,&QPushButton::clicked,this,&CCorrectSubjectiveQuestionsDlg::getNextShortAnswerChoice);
    QObject::connect(this,&CCorrectSubjectiveQuestionsDlg::startShowInfo,this,&CCorrectSubjectiveQuestionsDlg::showInfo);
    QObject::connect(this->ui->pushButton_27,&QPushButton::clicked,[=](){
        this->updateShortAnserScore(this->ui->lineEdit->text().trimmed());
    });
    QObject::connect(this,&CCorrectSubjectiveQuestionsDlg::startShowScore,this,&CCorrectSubjectiveQuestionsDlg::showScore);
    this->getShoerAnswerCount();
    //进行回显第一题
    emit this->ui->pushButton_251->clicked();
}

void CCorrectSubjectiveQuestionsDlg::checkScoreExist()
{
   HANDLE thread =(HANDLE)_beginthreadex(nullptr,0,&CCorrectSubjectiveQuestionsDlg::threadCheckScoreExist,this,0,nullptr);
   WaitForSingleObject(thread,INFINITE);
}

unsigned WINAPI CCorrectSubjectiveQuestionsDlg::threadCheckScoreExist(LPVOID arg)
{
    CCorrectSubjectiveQuestionsDlg* thiz = (CCorrectSubjectiveQuestionsDlg*)arg;
    int ret =  thiz->m_contorler->checkScoreExist(thiz->teacherId,thiz->studentId
                                       ,thiz->classId,thiz->testPaperId);
    //根据结果处理发送不同的信号
    if(ret == 0)
    {
       thiz->isExist = false;
    }else if(ret > 0)
    {
       thiz->isExist = true;
    }
    return 0;
}

void CCorrectSubjectiveQuestionsDlg::updateTestPaperCorrectStatus()
{
    _beginthreadex(nullptr,0,&CCorrectSubjectiveQuestionsDlg::CCorrectSubjectiveQuestionsDlg::threadUpdateTestPaperCorrectStatus,this,0,nullptr);
}

unsigned WINAPI CCorrectSubjectiveQuestionsDlg::threadUpdateTestPaperCorrectStatus(LPVOID arg)
{
    CCorrectSubjectiveQuestionsDlg* thiz = (CCorrectSubjectiveQuestionsDlg*)arg;
    thiz->m_contorler->updateTestPaperCorrectStatus(thiz->teacherId,thiz->studentId
                                                    ,thiz->classId,thiz->testPaperId);
    return 0;
}

void CCorrectSubjectiveQuestionsDlg::showScore(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    for(int i = 0 ; i < ret->size();i++)
    {
        //显示已经进行的评分
        QString str = ret->at(i).at(0);
        qDebug()<<"score:"<<str;
        if(str == "0") //默认是未赋分对控件进行清空
        {
            this->ui->lineEdit->clear();
        }else
        {
            this->ui->lineEdit->setText(str);
        }
    }
    delete ret;
}

typedef struct updateShortAnserScoreArg{
    QString score;
    CCorrectSubjectiveQuestionsDlg* thiz;
}UpdateShortAnserScoreArg;

void CCorrectSubjectiveQuestionsDlg::updateShortAnserScore(QString score)
{
    std::shared_ptr<UpdateShortAnserScoreArg> arg = std::make_shared<UpdateShortAnserScoreArg>();
    arg->thiz = this;
    arg->score = score;
    std::shared_ptr<UpdateShortAnserScoreArg>* p = new std::shared_ptr<UpdateShortAnserScoreArg>(arg);
    _beginthreadex(nullptr,0,&CCorrectSubjectiveQuestionsDlg::threadUpdateShortAnserScore,p,0,nullptr);
}

unsigned WINAPI CCorrectSubjectiveQuestionsDlg::threadUpdateShortAnserScore(LPVOID arg)
{
    std::shared_ptr<UpdateShortAnserScoreArg>* p = (std::shared_ptr<UpdateShortAnserScoreArg>*)arg;
    std::shared_ptr<UpdateShortAnserScoreArg> uInfo = *p;
    uInfo->thiz->m_contorler->updateShortAnserScore(uInfo->thiz->studentId,
                                                    uInfo->thiz->teacherId,uInfo->thiz->classId,
                                                    uInfo->thiz->testPaperId,uInfo->thiz->order,uInfo->score);
    //进行显示提示
    emit uInfo->thiz->startShowInfo();
    delete p;
    return 0;
}

void CCorrectSubjectiveQuestionsDlg::showInfo()
{
    std::shared_ptr<QMessageBox> box = std::make_shared<QMessageBox>(QMessageBox::Information,"提示","赋分成功!",QMessageBox::Ok);
    box->exec();
}

void CCorrectSubjectiveQuestionsDlg::getShoerAnswerCount()
{
    _beginthreadex(nullptr,0,&CCorrectSubjectiveQuestionsDlg::threadGetShoerAnswerCount,this,0,nullptr);
}

void CCorrectSubjectiveQuestionsDlg::getLastShortAnswerChoice()
{
    if(this->order > 1)
    {
        this->order -= 1;
        //重新显示题号高光
        emit this->m_shortAnswerChoice.at(this->order - 1)->clicked();
    }
}

void CCorrectSubjectiveQuestionsDlg::getCurShortAnswerScore()
{
    _beginthreadex(nullptr,0,&CCorrectSubjectiveQuestionsDlg::threadGetCurShortAnswerScore,this,0,nullptr);
}

unsigned WINAPI CCorrectSubjectiveQuestionsDlg::threadGetCurShortAnswerScore(LPVOID arg)
{
    CCorrectSubjectiveQuestionsDlg* thiz = (CCorrectSubjectiveQuestionsDlg*)arg;
    std::vector<std::vector<std::string>> ret = thiz->m_contorler->getCurShortAnswerScore(thiz->teacherId,thiz->studentId
                                              ,thiz->classId,thiz->testPaperId,thiz->order);

    QVector<QVector<QString>>* result = new QVector<QVector<QString>>();
    for(int i = 0 ; i < ret.size();i++)
    {
        QVector<QString> temp;
        for(int j = 0 ; j < ret.at(i).size();j++)
        {
            QString str = QString::fromLocal8Bit(ret.at(i).at(j).c_str());
            temp.push_back(str);
        }
        result->push_back(temp);
    }
    emit thiz->startShowScore(result);
    return 0;
}

void CCorrectSubjectiveQuestionsDlg::getNextShortAnswerChoice()
{
    if(this->order < this->count)
    {
        this->order += 1;
        //重新显示题号高光
        emit this->m_shortAnswerChoice.at(this->order - 1)->clicked();
    }
}

void CCorrectSubjectiveQuestionsDlg::showSHortAnswerBtn(int Count)
{
    for(int i = 0 ; i < Count;i++)
    {
        this->m_shortAnswerChoice.at(i)->setVisible(true);
    }
}

unsigned WINAPI CCorrectSubjectiveQuestionsDlg::threadGetShoerAnswerCount(LPVOID arg)
{
    CCorrectSubjectiveQuestionsDlg* thiz = (CCorrectSubjectiveQuestionsDlg*)arg;
    int ret = thiz->m_contorler->getShortAnswerCount(thiz->testPaperId);
    thiz->count = ret;
    emit thiz->startShowShortAnswerBtn(ret);
    return 0;
}

void CCorrectSubjectiveQuestionsDlg::getCurOrderShortAnswer()
{
    _beginthreadex(nullptr,0,&CCorrectSubjectiveQuestionsDlg::threadGetCurOrderShortAnswer,this,0,nullptr);
}

unsigned WINAPI CCorrectSubjectiveQuestionsDlg::threadGetCurOrderShortAnswer(LPVOID arg)
{
    CCorrectSubjectiveQuestionsDlg* thiz = (CCorrectSubjectiveQuestionsDlg*)arg;
    std::vector<std::vector<std::string>> ret =  thiz->m_contorler->getCurOrderShortAnswer(thiz->testPaperId
                                                                                           ,thiz->order);
    QVector<QVector<QString>>* result = new QVector<QVector<QString>>();
    for(int i = 0 ; i < ret.size();i++)
    {
        QVector<QString> temp;
        for(int j = 0 ; j < ret.at(i).size();j++)
        {
            QString str = QString::fromLocal8Bit(ret.at(i).at(j).c_str());
            temp.push_back(str);
        }
        result->push_back(temp);
    }
    //进行数据回显发送
    emit thiz->startShowShortAnswer(result);
    return 0;
}

void CCorrectSubjectiveQuestionsDlg::showShortAnswerUI(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return;
    }

    for(int i = 0 ; i < ret->size();i++)
    {
        //显示分数
        QString grade = "总分：(";
        grade += ret->at(i).at(0);
        grade += ")分";
        this->ui->label_4->setText(grade);

        //显示题干
        QString str = ret->at(i).at(1);
        this->ui->textEdit->setText(str);

        //显示标准答案
        str = ret->at(i).at(2);
        this->ui->textEdit_3->setText(str);
    }
    delete ret;
}

void CCorrectSubjectiveQuestionsDlg::getCurOrderAnswer()
{
    _beginthreadex(nullptr,0,&CCorrectSubjectiveQuestionsDlg::threadGetCurOrderAnswer,this,0,nullptr);
}

unsigned WINAPI CCorrectSubjectiveQuestionsDlg::threadGetCurOrderAnswer(LPVOID arg)
{
    CCorrectSubjectiveQuestionsDlg* thiz = (CCorrectSubjectiveQuestionsDlg*)arg;
    std::vector<std::vector<std::string>> ret =  thiz->m_contorler->getCurOrderAnswer(thiz->teacherId,thiz->studentId
                                         ,thiz->classId,thiz->testPaperId,thiz->order);
    QVector<QVector<QString>>* result = new QVector<QVector<QString>>();
    for(int i = 0 ; i < ret.size();i++)
    {
        QVector<QString> temp;
        for(int j = 0 ; j < ret.at(i).size();j++)
        {
            QString str = QString::fromLocal8Bit(ret.at(i).at(j).c_str());
            temp.push_back(str);
        }
        result->push_back(temp);
    }
    emit thiz->startShowAnswer(result);
    return 0;
}

void CCorrectSubjectiveQuestionsDlg::showAnswerUI(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return;
    }

    for(int i = 0 ; i < ret->size();i++)
    {
        //显示标准答案
        QString str = ret->at(i).at(0);
        this->ui->textEdit_2->setText(str);
    }
    delete ret;
}

CCorrectSubjectiveQuestionsDlg::~CCorrectSubjectiveQuestionsDlg()
{
    qDebug()<<"主观题批改界面被释放！";
    this->m_shortAnswerChoice.clear();
    delete ui;
}
