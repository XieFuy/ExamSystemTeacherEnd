#include "previewtestpaperdlg.h"
#include "ui_previewtestpaperdlg.h"

CPreviewTestPaperDlg::CPreviewTestPaperDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPreviewTestPaperDlg)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icons/testPaperPreview.png"));
    this->setWindowTitle("试卷预览");
    this->m_contorller = new CPreviewTestPaperContorller();

    this->signalChoiceCurIndex = 1;
    this->multiChoiceCurIndex = 1;
    this->signalChoiceCount = 0;
    this->multiChoiceCount = 0;
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(0);
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");

    });

    QObject::connect(this->ui->pushButton_2,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(1);
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getMultiChoiceCount();
        this->getCurIndexMultiChoice();
    });

    QObject::connect(this->ui->pushButton_3,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(2);
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
    });

    QObject::connect(this->ui->pushButton_4,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(3);
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
    });

    //将Ui中的题号按钮都加入到容器中
    for(int i = 7 ; i <= 84 ; i++ )
    {
        QString strName = "pushButton_";
        strName += QString::number(i);
        QPushButton* btn =  this->findChild<QPushButton*>(strName);
        this->m_signalChoice.push_back(btn);  //这些按钮 不需要我们去释放，UI文件自动管理
    }

    //将Ui中的多选题题号按钮都加入到容器中
    for(int i = 89;i <= 166 ; i++)
    {
        QString strName = "pushButton_";
        strName += QString::number(i);
        QPushButton* btn =  this->findChild<QPushButton*>(strName);
       this->m_multiChoice.push_back(btn);  //这些按钮 不需要我们去释放，UI文件自动管理
    }

    int i = 1;
    //给每一个按钮进行设置样式
    for(QPushButton* btn: this->m_signalChoice)
    {
        btn->setText(QString::number(i++));
        btn->setFont(QFont("黑体",12));
        btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
    }

    //给多选题的每一个按钮进行设置样式
    i = 1;
    for(QPushButton* btn: this->m_multiChoice)
    {
        btn->setText(QString::number(i++));
        btn->setFont(QFont("黑体",12));
        btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
    }


    //进行绑定信号槽，实现单击只有一个题号是绿色
    for(QPushButton* btn : this->m_signalChoice)
    {
        QObject::connect(btn,&QPushButton::clicked,[=](){
            //被点击的按钮设置为绿色，其他的所有按钮恢复原来的状态
            btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;background-color:green;}");
            for(QPushButton* btn2 : this->m_signalChoice)
            {
                if(btn2 != btn)
                {
                    btn2->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
                }
            }
        });
    }

    //多选题题号进行信号槽绑定，实现单击只有一个题号是绿色
    for(QPushButton* btn : this->m_multiChoice)
    {
        QObject::connect(btn,&QPushButton::clicked,[=](){
            //被点击的按钮设置为绿色，其他的所有按钮恢复原来的状态
            btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;background-color:green;}");
            for(QPushButton* btn2 : this->m_multiChoice)
            {
                if(btn2 != btn)
                {
                    btn2->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
                }
            }
        });
    }


    //一开始将全部的按钮进行隐藏
    for(QPushButton* btn : this->m_signalChoice)
    {
       btn->setVisible(false);
    }

    //将多选题号按钮进行隐藏
    for(QPushButton* btn : this->m_multiChoice)
    {
       btn->setVisible(false);
    }

    QObject::connect(this,&CPreviewTestPaperDlg::startShowMenueBtn,this,&CPreviewTestPaperDlg::showMenueBtn);
   //一定要放到最后
    emit this->ui->pushButton->clicked();

    QObject::connect(this,&CPreviewTestPaperDlg::startShowSignalChoice,this,&CPreviewTestPaperDlg::showSignalChoice);

    QObject::connect(this->ui->pushButton_6,&QPushButton::clicked,this,&CPreviewTestPaperDlg::getNextSignalChoive);

    QObject::connect(this->ui->pushButton_5,&QPushButton::clicked,this,&CPreviewTestPaperDlg::getLastSignalChoice);

    QObject::connect(this,&CPreviewTestPaperDlg::startShowMultiMenueBtn,this,&CPreviewTestPaperDlg::showMultiMenueBtn);

    QObject::connect(this,&CPreviewTestPaperDlg::startShowMultiChoice,this,&CPreviewTestPaperDlg::showMultiChoice);
}

typedef struct getCurIndexMultiChoiceArg{
    CPreviewTestPaperDlg* thiz;
    QString acount;
    QString testPaperName;
    int curIndex;
}GetCurIndexMultiChoiceArg;

void CPreviewTestPaperDlg::getCurIndexMultiChoice()
{
    GetCurIndexMultiChoiceArg* arg = new GetCurIndexMultiChoiceArg();
    arg->acount = this->acount;
    arg->testPaperName = this->testPaperName;
    arg->curIndex = this->multiChoiceCurIndex;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CPreviewTestPaperDlg::threadGetCurIndexMultiChoice,arg,0,nullptr);
}

unsigned WINAPI CPreviewTestPaperDlg::threadGetCurIndexMultiChoice(LPVOID arg)
{
    GetCurIndexMultiChoiceArg* gInfo = (GetCurIndexMultiChoiceArg*)arg;
    std::vector<std::vector<std::string>> ret =  gInfo->thiz->m_contorller->getCurIndexMultiChoice(gInfo->acount
                                                                                                   ,gInfo->testPaperName
                                                                                                   ,gInfo->curIndex);

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

    emit gInfo->thiz->startShowMultiChoice(result);
    delete gInfo;
    _endthreadex(0);
    return 0;

}

void CPreviewTestPaperDlg::showMultiMenueBtn(int Count)
{
    for(int i = 0 ; i < Count;i++)
    {
        this->m_multiChoice.at(i)->setVisible(true);
    }
}

typedef struct getMultiChoiceCountArg{
    QString acount;
    QString testPaperName;
    CPreviewTestPaperDlg* thiz;
}GetMultiChoiceCountArg;

void CPreviewTestPaperDlg::getMultiChoiceCount()
{
    //确保对象的属性已经赋值
    GetMultiChoiceCountArg* arg = new GetMultiChoiceCountArg();
    arg->acount = this->acount;
    arg->testPaperName = this->testPaperName;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CPreviewTestPaperDlg::threadGetMultiChoiceCount,arg,0,nullptr);
}

unsigned WINAPI CPreviewTestPaperDlg::threadGetMultiChoiceCount(LPVOID arg)
{
    GetMultiChoiceCountArg* gInfo = ( GetMultiChoiceCountArg*)arg;
    gInfo->thiz->m_contorller->getMultiChoiceCount(gInfo->acount,gInfo->testPaperName);
    int multiCount =  gInfo->thiz->m_contorller->getMultiChoiceCount(gInfo->acount,gInfo->testPaperName);
    gInfo->thiz->multiChoiceCount = multiCount;
    //    //显示对应的按钮数量
    emit gInfo->thiz->startShowMultiMenueBtn(multiCount);
    delete gInfo;
    _endthreadex(0);
    return 0;
}

void CPreviewTestPaperDlg::getLastSignalChoice()
{
    if(this->signalChoiceCurIndex > 1)
    {
        this->signalChoiceCurIndex -= 1;

        //重新显示题目
        this->getCurIndexSignalChoice();

        //更改题号
        this->ui->pushButton_85->setText(QString::number(this->signalChoiceCurIndex));
        //重新显示题号高光
        emit this->m_signalChoice.at(this->signalChoiceCurIndex - 1)->clicked();
    }
}

void CPreviewTestPaperDlg::showMultiChoice(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    //显示题干

    this->ui->label_11->setText(ret->at(0).at(0));

    //显示A选项
    this->ui->checkBox->setText(ret->at(0).at(1));

    //显示B选项
    this->ui->checkBox_2->setText(ret->at(0).at(2));

    //显示C选项
    this->ui->checkBox_3->setText(ret->at(0).at(3));

    //显示D选项
    this->ui->checkBox_4->setText(ret->at(0).at(4));

    //显示E选项
    this->ui->checkBox_5->setText(ret->at(0).at(5));

    //显示F选项
    this->ui->checkBox_6->setText(ret->at(0).at(6));

    //显示正确答案
    this->ui->label_19->setText(ret->at(0).at(7));
    delete ret;
}

void CPreviewTestPaperDlg::showSignalChoice(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    //显示题干

    this->ui->label->setText(ret->at(0).at(0));

    //显示A选项
    this->ui->radioButton->setText(ret->at(0).at(1));

    //显示B选项
    this->ui->radioButton_2->setText(ret->at(0).at(2));

    //显示C选项
    this->ui->radioButton_3->setText(ret->at(0).at(3));

    //显示D选项
    this->ui->radioButton_4->setText(ret->at(0).at(4));

    //显示正确答案
    this->ui->label_6->setText(ret->at(0).at(5));
    delete ret;
}

typedef struct getCurIndexSignalChoiceArg{
    CPreviewTestPaperDlg* thiz;
    QString acount;
    QString testPaperName;
    int curIndex;
}GetCurIndexSignalChoiceArg;

void CPreviewTestPaperDlg::getCurIndexSignalChoice()
{
    GetCurIndexSignalChoiceArg* arg = new GetCurIndexSignalChoiceArg();
    arg->acount = this->acount;
    arg->testPaperName = this->testPaperName;
    arg->curIndex = this->signalChoiceCurIndex;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CPreviewTestPaperDlg::threadGetCurIndexSignalChoice,arg,0,nullptr);
}

unsigned WINAPI CPreviewTestPaperDlg::threadGetCurIndexSignalChoice(LPVOID arg)
{
    GetCurIndexSignalChoiceArg* gInfo = (GetCurIndexSignalChoiceArg*)arg;
    std::vector<std::vector<std::string>> ret =  gInfo->thiz->m_contorller->getCurIndexSignalChoice(gInfo->acount,gInfo->testPaperName,gInfo->curIndex);

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
    emit gInfo->thiz->startShowSignalChoice(result);
    delete gInfo;
    _endthreadex(0);
    return 0;
}

typedef struct getSignalChoiceCountArg{
    CPreviewTestPaperDlg* thiz;
    QString acount;
    QString testPaperName;
}GetSignalChoiceCountArg;

void CPreviewTestPaperDlg::getSignalChoiceCount()
{
    //确保对象的属性已经赋值
    GetSignalChoiceCountArg* arg = new GetSignalChoiceCountArg();
    arg->acount = this->acount;
    arg->testPaperName = this->testPaperName;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CPreviewTestPaperDlg::threadGetSignalChoiceCount,arg,0,nullptr);
}

unsigned WINAPI CPreviewTestPaperDlg::threadGetSignalChoiceCount(LPVOID arg)
{
    GetSignalChoiceCountArg* gInfo = (GetSignalChoiceCountArg*)arg;
    int signalCount =  gInfo->thiz->m_contorller->getSignalChoiceCount(gInfo->acount,gInfo->testPaperName);
    gInfo->thiz->signalChoiceCount = signalCount;
    //显示对应的按钮数量
    emit gInfo->thiz->startShowMenueBtn(signalCount);
    delete gInfo;
    _endthreadex(0);
    return 0;
}

void CPreviewTestPaperDlg::getNextSignalChoive()
{
    if(this->signalChoiceCurIndex < this->signalChoiceCount)
    {
        this->signalChoiceCurIndex += 1;

        //重新显示题目
        this->getCurIndexSignalChoice();

        //更改题号
        this->ui->pushButton_85->setText(QString::number(this->signalChoiceCurIndex));
        //重新显示题号高光
        emit this->m_signalChoice.at(this->signalChoiceCurIndex - 1)->clicked();
    }
}

void CPreviewTestPaperDlg::showMenueBtn(int Count)
{
    for(int i = 0 ; i < Count;i++)
    {
        this->m_signalChoice.at(i)->setVisible(true);
    }
}

void CPreviewTestPaperDlg::SetAcount(QString acount)
{
    this->acount = acount;
}

void CPreviewTestPaperDlg::SetTestPaperName(QString testPaperName)
{
    this->testPaperName = testPaperName;

    //这里进行赋值完成
    this->getSignalChoiceCount();

    this->getCurIndexSignalChoice();
}

CPreviewTestPaperDlg::~CPreviewTestPaperDlg()
{
    if(this->m_contorller != nullptr)
    {
        delete this->m_contorller;
        this->m_contorller = nullptr;
    }
    this->m_signalChoice.clear();
    this->m_multiChoice.clear();
    delete ui;
}
