#include "mainmenuedlg.h"
#include "ui_mainmenuedlg.h"

CMainMenueDlg::CMainMenueDlg(QWidget *parent) : //主菜单界面类
    QDialog(parent),
    ui(new Ui::CMainMenueDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("在线考试系统-教师端");
    this->setWindowIcon(QIcon(":/icons/winIcon.png"));

    this->m_curStudentRequestIndex = 1;
    this->m_classCurPageIndex = 1;
    this->m_Event = CreateEvent(nullptr,FALSE,FALSE,nullptr);
    this->m_Event_2 = CreateEvent(nullptr,FALSE,FALSE,nullptr);
    this->m_sortNumStudentRequest = 0;
    this->sortNumberClass = 0;
    this->sortNUmber = 0;
    this->signalCount = 0;
    this->multiCount = 0;
    this->judgeCount = 0;
    this->shortAnswerCount = 0;
    this->m_multiCorrectOptions = "";
    this->m_testPaperStatusChoise = 0;

    this->m_studentRequestCount = "";
    this->m_judgeAnswer = "";
    this->ui->comboBox->addItem("全部",0);
    this->ui->comboBox->addItem("已发布",1);
    this->ui->comboBox->addItem("未发布",2);

    this->ui->comboBox_3->addItem("按姓名查询",0);
    this->ui->comboBox_3->addItem("按学号查询",1);
    this->ui->comboBox_3->addItem("按申请时间查询",2);

    this->m_pageCount = "";
    this->curPageIndex = 1;
    this->initTableWidgetHeader();

    //生成控制层
    this->m_mainMenueContorller = new CMainMenueContorller();
    //设置标题栏头像为圆形
    this->ui->label_head->setMask(QRegion(ui->label_head->rect(),QRegion::RegionType::Ellipse));
    this->ui->label_head2->setMask(QRegion(ui->label_head2->rect(),QRegion::RegionType::Ellipse));
    //鼠标进入人物姓名的时候需要实现对话框的动态效果
    this->m_exitLoginDlg = new CExitLoginDlg(this);
    this->m_exitLoginDlg->move(this->ui->label_name->x(),this->ui->label->height()+1);
    this->m_exitLoginDlg->hide();
    this->ui->label_name->installEventFilter(this);
    this->m_exitLoginDlg->installEventFilter(this);

    this->m_acount = "";

    this->initClassTable();
    this->initClassTableControl();
    this->initStudentRequestTable();
    this->initStudentRequestTableControl();
    //界面初始化的默认选中项
    this->ui->pushButton_3->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
    this->ui->pushButton_8->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
    this->ui->stackedWidget->setCurrentIndex(0);
    this->ui->stackedWidget_2->setCurrentIndex(0);

    QObject::connect(this,&CMainMenueDlg::startInitTeacherInfoTable,this,&CMainMenueDlg::initTeacherInfoTable);
    emit this->startInitTeacherInfoTable();

    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(5);
    });

    QObject::connect(this->ui->pushButton_3,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(0);
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_4,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(1);
        this->getTablePageCount();
        this->getCurPageIndexTableData();
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_5,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(2);
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_6,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(3);
        this->m_classCurPageIndex = 1;
        emit this->startGetClassTableInfo();
        emit this->startGetClassTableIndex();
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_7,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(4);
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    this->m_signalOperator = new QTreeWidgetItem(QStringList()<<"1、单选题");
    this->m_multiOerator = new QTreeWidgetItem(QStringList()<<"2、多选题");
    this->m_judge = new QTreeWidgetItem(QStringList()<<"3、判断题");
    this->m_ShortAnswer = new QTreeWidgetItem(QStringList()<<"4、简答题");
    this->ui->treeWidget->addTopLevelItem(this->m_signalOperator);
    this->ui->treeWidget->addTopLevelItem(this->m_multiOerator);
    this->ui->treeWidget->addTopLevelItem(this->m_judge);
    this->ui->treeWidget->addTopLevelItem(this->m_ShortAnswer);

    QObject::connect(this->ui->radioButton,&QRadioButton::toggled,[=](bool checked){
        if(checked)
        {
            this->m_signalCorrectOptions = this->ui->radioButton->text().trimmed();
        }else
        {
            this->m_signalCorrectOptions = "";
        }
    });

    QObject::connect(this->ui->radioButton_2,&QRadioButton::toggled,[=](bool checked){
        if(checked)
        {
            this->m_signalCorrectOptions = this->ui->radioButton_2->text().trimmed();
        }else
        {
            this->m_signalCorrectOptions = "";
        }
    });

    QObject::connect(this->ui->radioButton_3,&QRadioButton::toggled,[=](bool checked){
        if(checked)
        {
            this->m_signalCorrectOptions = this->ui->radioButton_3->text().trimmed();
        }else
        {
            this->m_signalCorrectOptions = "";
        }
    });

    QObject::connect(this->ui->radioButton_4,&QRadioButton::toggled,[=](bool checked){
        if(checked)
        {
            this->m_signalCorrectOptions = this->ui->radioButton_4->text().trimmed();
        }else
        {
            this->m_signalCorrectOptions = "";
        }
    });


    QObject::connect(this->ui->pushButton_14,&QPushButton::clicked,this,&CMainMenueDlg::clearSignalOption);


    QObject::connect(this->ui->pushButton_13,&QPushButton::clicked,[=](){
        QString str = "(";
        QString num = QString::number(++this->signalCount);
        str += num;
        str +=")";
        QTreeWidgetItem* signalItem = new QTreeWidgetItem(QStringList()<<str);
        this->m_signalOperator->addChild(signalItem);
        this->m_signalOperatorLst.push_back(signalItem);
        this->m_signalMap.insert(str,this->signalCount);
        qDebug()<<"正确选项: "<<this->m_signalCorrectOptions;
        QMap<QString,int>::iterator pos = this->m_signalMap.find(str);
        if(pos == this->m_signalMap.end())
        {
            return;
        }
        int order = pos.value();
        //将数据存储到数据库中
         this->addSignalChoiceInfo(this->ui->lineEdit->text().trimmed(),
                                   this->ui->textEdit->toPlainText().trimmed(),
                                   this->ui->textEdit_2->toPlainText().trimmed(),
                                   this->ui->textEdit_3->toPlainText().trimmed(),
                                   this->ui->textEdit_4->toPlainText().trimmed(),
                                   this->ui->textEdit_5->toPlainText().trimmed(),
                                   this->m_signalCorrectOptions.trimmed(),order);
        //将UI的题进行清空
        emit this->ui->pushButton_14->clicked();
    });

    QObject::connect(this->ui->pushButton_8,&QPushButton::clicked,[=](){
        this->ui->stackedWidget_2->setCurrentIndex(0);
        this->ui->pushButton_8->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_9->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_10->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_11->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_16,&QPushButton::clicked,this,&CMainMenueDlg::clearMultiOption);

    QObject::connect(this->ui->pushButton_15,&QPushButton::clicked,[=](){
        QString str = "(";
        QString num = QString::number(++this->multiCount);
        str += num;
        str +=")";
        QTreeWidgetItem* multiItem = new QTreeWidgetItem(QStringList()<<str);
        this->m_multiOerator->addChild(multiItem);
        this->m_multiOeratorLst.push_back(multiItem);
        this->m_multiMap.insert(str,this->multiCount);

        this->m_multiCorrectOptions = "";
        //拿到被选项
        if(this->ui->checkBox->isChecked() == true)
        {
            this->m_multiCorrectOptions +=  this->ui->checkBox->text().trimmed();
            this->m_multiCorrectOptions += ',';
        }
        if(this->ui->checkBox_2->isChecked() == true)
        {
            this->m_multiCorrectOptions +=  this->ui->checkBox_2->text().trimmed();
            this->m_multiCorrectOptions += ',';
        }
        if(this->ui->checkBox_3->isChecked() == true)
        {
            this->m_multiCorrectOptions +=  this->ui->checkBox_3->text().trimmed();
            this->m_multiCorrectOptions += ',';
        }
        if(this->ui->checkBox_4->isChecked() == true)
        {
            this->m_multiCorrectOptions +=  this->ui->checkBox_4->text().trimmed();
            this->m_multiCorrectOptions += ',';
        }
        if(this->ui->checkBox_5->isChecked() == true)
        {
            this->m_multiCorrectOptions +=  this->ui->checkBox_5->text().trimmed();
            this->m_multiCorrectOptions += ',';
        }
        if(this->ui->checkBox_6->isChecked() == true)
        {
            this->m_multiCorrectOptions +=  this->ui->checkBox_6->text().trimmed();
            this->m_multiCorrectOptions += ',';
        }
        qDebug()<<"多选选中的选项："<<this->m_multiCorrectOptions;

         QMap<QString,int>::iterator ret = this->m_multiMap.find(str);
         int order = ret.value();
        //将数据存储到数据库中
        this->addMultiChoiceInfo(this->ui->lineEdit_2->text().trimmed(),
                                 this->ui->textEdit_6->toPlainText().trimmed(),
                                 this->ui->textEdit_12->toPlainText().trimmed(),
                                 this->ui->textEdit_7->toPlainText().trimmed(),
                                 this->ui->textEdit_8->toPlainText().trimmed(),
                                 this->ui->textEdit_9->toPlainText().trimmed(),
                                 this->ui->textEdit_10->toPlainText().trimmed(),
                                 this->ui->textEdit_11->toPlainText().trimmed(),
                                 this->m_multiCorrectOptions,order);
        //将UI的题进行清空
         emit this->ui->pushButton_16->clicked();
    });

    QObject::connect(this->ui->pushButton_9,&QPushButton::clicked,[=](){
        this->ui->stackedWidget_2->setCurrentIndex(1);
        this->ui->pushButton_9->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_8->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_10->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_11->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->radioButton_5,&QRadioButton::toggled,[=](bool isChecked){
        if(isChecked)
        {
            this->m_judgeAnswer = "1";
        }else
        {
            this->m_judgeAnswer = "0";
        }
    });

    QObject::connect(this->ui->radioButton_6,&QRadioButton::toggled,[=](bool isChecked){
        if(isChecked)
        {
            this->m_judgeAnswer = "0";
        }else
        {
            this->m_judgeAnswer = "1";
        }
    });

    QObject::connect(this->ui->pushButton_18,&QPushButton::clicked,this,&CMainMenueDlg::clearJudge);

    QObject::connect(this->ui->pushButton_17,&QPushButton::clicked,[=](){
        QString str = "(";
        QString num = QString::number(++this->judgeCount);
        str += num;
        str +=")";
        QTreeWidgetItem* judgeItem = new QTreeWidgetItem(QStringList()<<str);
        this->m_judge->addChild(judgeItem);
        this->m_judgeLst.push_back(judgeItem);
        this->m_judgeMap.insert(str,this->judgeCount);

        QMap<QString,int>::iterator ret = this->m_judgeMap.find(str);
        int order = ret.value();

        qDebug()<<"正确："<<this->m_judgeAnswer;
        //将数据存储到数据库中,判断题
        this->addJudgeInfo(this->ui->lineEdit_3->text().trimmed(),
                           this->ui->textEdit_13->toPlainText().trimmed(),
                           this->ui->textEdit_14->toPlainText().trimmed(),
                           this->ui->textEdit_15->toPlainText().trimmed(),
                           this->m_judgeAnswer,order);
        //将UI的题进行清空
       emit this->ui->pushButton_18->clicked();
    });

    QObject::connect(this->ui->pushButton_10,&QPushButton::clicked,[=](){       
        this->ui->stackedWidget_2->setCurrentIndex(2);
        this->ui->pushButton_10->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_8->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_9->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_11->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_20,&QPushButton::clicked,this,&CMainMenueDlg::clearShortAnswer);

    QObject::connect(this->ui->pushButton_19,&QPushButton::clicked,[=](){
        QString str = "(";
        QString num = QString::number(++this->shortAnswerCount);
        str += num;
        str +=")";
        QTreeWidgetItem* shortAnswerItem = new QTreeWidgetItem(QStringList()<<str);
        this->m_ShortAnswer->addChild(shortAnswerItem);
        this->m_ShortAnswerLst.push_back(shortAnswerItem);
        this->m_shortAnswerMap.insert(str,this->shortAnswerCount);

        QMap<QString,int>::iterator ret = this->m_shortAnswerMap.find(str);
        int order = ret.value();
        //将数据存储到数据库中
        this->addShortAnswerInfo(this->ui->lineEdit_4->text().trimmed(),
                                 this->ui->textEdit_16->toPlainText().trimmed(),
                                 this->ui->textEdit_17->toPlainText().trimmed(),
                                 order);
        //将UI的题进行清空
        emit this->ui->pushButton_20->clicked();
    });

    QObject::connect(this->ui->pushButton_11,&QPushButton::clicked,[=](){
        this->ui->stackedWidget_2->setCurrentIndex(3);
        this->ui->pushButton_11->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_8->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_9->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_10->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    //进行员工职员姓名和头像回显
    QObject::connect(this,&CMainMenueDlg::startShowTeacherInfo,this,&CMainMenueDlg::showTeacherInfo);
    //监听头像UI更新信号
    QObject::connect(this,&CMainMenueDlg::startShowHeadImage,this,&CMainMenueDlg::showHeadImageUI);
    //显示职工账号管理信息
    //QObject::connect(this->ui->pushButton,&QPushButton::clicked,this,&CMainMenueDlg::showTeacherAcountInfo);
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,this,&CMainMenueDlg::getTeacherAcountInfoData);

    QObject::connect(this->ui->pushButton_22,&QPushButton::clicked,[=](){
        if(this->m_nameChangeDlg == nullptr)
        {
            this->m_nameChangeDlg = new CNameChangeDlg();
            this->m_nameChangeDlg->m_acount = this->m_acount;
            this->m_nameChangeDlg->move((this->width() - this->m_nameChangeDlg->width()) / 2,(this->height() - this->m_nameChangeDlg->height()) / 2);
            this->m_nameChangeDlg->show();
            //监听返回信号
            QObject::connect(this->m_nameChangeDlg,&CNameChangeDlg::rejected,[=](){
                if(this->m_nameChangeDlg != nullptr)
                {
                    delete this->m_nameChangeDlg;
                    this->m_nameChangeDlg = nullptr;
                }
                emit this->startShowTeacherInfo(this->m_acount);
                emit this->ui->pushButton->clicked();
            });
        }
    });
    QObject::connect(this->ui->pushButton_24,&QPushButton::clicked,[=](){
        if(this->m_phoneNumChangeDlg == nullptr)
        {
            this->m_phoneNumChangeDlg = new CPhoneNumberChangeDlg();
            this->m_phoneNumChangeDlg->m_acount = this->m_acount;
            this->m_phoneNumChangeDlg->move((this->width() - this->m_phoneNumChangeDlg->width()) / 2,(this->height() - this->m_phoneNumChangeDlg->height()) / 2);
            this->m_phoneNumChangeDlg->show();
            //监听返回信号
            QObject::connect(this->m_phoneNumChangeDlg,&CNameChangeDlg::rejected,[=](){
                if(this->m_phoneNumChangeDlg != nullptr)
                {
                    delete this->m_phoneNumChangeDlg;
                    this->m_phoneNumChangeDlg = nullptr;
                }
                emit this->ui->pushButton->clicked();
            });
        }
    });
    //如果选的不是男就设置为女
    QObject::connect(this->ui->radioButton_7,&QRadioButton::toggled,this,&CMainMenueDlg::changeGender);
    QObject::connect(this->ui->pushButton_2,&QPushButton::clicked,this,&CMainMenueDlg::headPictureChange);

    QObject::connect(this,&CMainMenueDlg::startInitTestPaperTable,this,&CMainMenueDlg::initTestPaperTable);
    QObject::connect(this,&CMainMenueDlg::startInitSingleChoiceTable,this,&CMainMenueDlg::initSingleChoiceTable);
    QObject::connect(this,&CMainMenueDlg::startInitMultiChoiceTable,this,&CMainMenueDlg::initMultiChoiceTable);
    QObject::connect(this,&CMainMenueDlg::startInitJudgeTable,this,&CMainMenueDlg::initJudgeTable);
    QObject::connect(this,&CMainMenueDlg::startInitShortAnswerTable,this,&CMainMenueDlg::initShortAnswerTable);
    emit this->startInitTestPaperTable();
    emit this->startInitSingleChoiceTable();
    emit this->startInitMultiChoiceTable();
    emit this->startInitJudgeTable();
    emit this->startInitShortAnswerTable();

    QObject::connect(this->ui->pushButton_12,&QPushButton::clicked,[=](){
        if(this->m_testPaperSaveDlg == nullptr)
        {
            this->m_testPaperSaveDlg = new CTestPaperSaveDlg();
            //给对话框的属性进行赋值
            this->m_testPaperSaveDlg->m_acount = this->m_acount;
            this->m_testPaperSaveDlg->move((this->width() - this->m_testPaperSaveDlg->width()) / 2,
                                           (this->height() - this->m_testPaperSaveDlg->height()) / 2);
            this->m_testPaperSaveDlg->show();
            //监听返回信号
            QObject::connect(this->m_testPaperSaveDlg,&CTestPaperSaveDlg::rejected,[=](){
                if(this->m_testPaperSaveDlg != nullptr)
                {
                    delete this->m_testPaperSaveDlg;
                    this->m_testPaperSaveDlg = nullptr;
                }
                //清除所有的项
                this->clearTreeItemSignal();
                this->clearTreeItemMulti();
                this->clearTreeItemJudge();
                this->clearTreeItemShortAnswer();
            });
        }
    });

    QObject::connect(this,&CMainMenueDlg::startInitTestPaperTableContorl,this,&CMainMenueDlg::initTestPaperTableContorl);
    emit this->startInitTestPaperTableContorl();

    QObject::connect(this,&CMainMenueDlg::startShowPageIndex,this,&CMainMenueDlg::showPageIndex);

    QObject::connect(this,&CMainMenueDlg::startShowCurPageIndexTable,this,&CMainMenueDlg::showCurPageIndexTable);
    QObject::connect(this,&CMainMenueDlg::startShowTeacherAcountInfo,this,&CMainMenueDlg::showTeacherAcountInfo);
    QObject::connect(this->ui->pushButton_28,&QPushButton::clicked,this,&CMainMenueDlg::showNextPageIndexTable);
    QObject::connect(this->ui->pushButton_27,&QPushButton::clicked,this,&CMainMenueDlg::showLastPageIndexTable);

    QObject::connect(this->ui->comboBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),[=](int index){
        int value = this->ui->comboBox->itemData(index).toInt();
        this->curPageIndex = 1;
        this->m_testPaperStatusChoise = value;
        if(value == 0) // 查询全部
        {
           this->getCurPageIndexTableData();
             //重新显示符合条件的总页数
            this->getTablePageCount();
        }else if(value == 1) //查询已发布
        {
           this->getCurPageIndexTableDataPubulished();
               //重新显示符合条件的总页数
           this->getTablePageCountPublished();
        }else if(value == 2) //查询未发布
        {
           this->getCurPageIndexTableDataNotPubulished();
           this->getTablePageCountNotPublished();
        }
    });
    QObject::connect(this->ui->pushButton_23,&QPushButton::clicked,this,&CMainMenueDlg::getTableDataByFindTestName);
    QObject::connect(this->ui->checkBox_7,&QCheckBox::toggled,this,&CMainMenueDlg::changeCurPageCheckBoxStatus);
    QObject::connect(this->ui->pushButton_25,&QPushButton::clicked,this,&CMainMenueDlg::deleteMultiClickBtn);
    QObject::connect(this,&CMainMenueDlg::startInitClassTable,this,&CMainMenueDlg::initClassTableDatabase);
    emit this->startInitClassTable();
    QObject::connect(this->ui->pushButton_29,&QPushButton::clicked,[=](){
        if(this->m_classSaveDlg == nullptr)
        {
            this->m_classSaveDlg = new CClassSaveDlg();
            this->m_classSaveDlg->acount = this->m_acount;
            this->m_classSaveDlg->move((this->width() - this->m_classSaveDlg->width()) / 2,
                                       (this->height() - this->m_classSaveDlg->height()) / 2);
            this->m_classSaveDlg->show();
            this->ui->pushButton_29->setEnabled(false);
            QObject::connect(this->m_classSaveDlg,&CClassSaveDlg::rejected,[=](){
                if(this->m_classSaveDlg != nullptr)
                {
                    delete this->m_classSaveDlg;
                    this->m_classSaveDlg = nullptr;
                }
                this->ui->pushButton_29->setEnabled(true);
                this->m_classCurPageIndex = 1;
                emit this->startGetClassTableInfo();
                emit this->startGetClassTableIndex();
            });
        }
    });
    QObject::connect(this,&CMainMenueDlg::startGetClassTableInfo,this,&CMainMenueDlg::getClassTableData);
    QObject::connect(this,&CMainMenueDlg::startShowClassTable,this,&CMainMenueDlg::showClassTableInfo);
    QObject::connect(this,&CMainMenueDlg::startShowClassIcon,this,&CMainMenueDlg::showClassIconUI);
    QObject::connect(this,&CMainMenueDlg::startShowClassTableIndex,&CMainMenueDlg::showClassTableIndex);
    QObject::connect(this,&CMainMenueDlg::startGetClassTableIndex,this,&CMainMenueDlg::getClassTableCount);

    //课程表下一页点击
    QObject::connect(this->ui->pushButton_31,&QPushButton::clicked,this,&CMainMenueDlg::showClassTableNextPage);

    //课程表上一页点击
    QObject::connect(this->ui->pushButton_30,&QPushButton::clicked,this,&CMainMenueDlg::showClassTableLastPage);

    QObject::connect(this->ui->checkBox_8,&QCheckBox::toggled,this,&CMainMenueDlg::changeClassCurPageCheckBoxStatus);

    QObject::connect(this->ui->pushButton_32,&QPushButton::clicked,this,&CMainMenueDlg::deleteMultiClassInfo);


    QObject::connect(this->ui->pushButton_37,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(3);
        this->ui->label_56->setPixmap(QPixmap()); //返回的时候 清空课程图标
        this->clearStudentRequestTableUI();
    });

    QObject::connect(this,&CMainMenueDlg::startShowClassIconInStudentRequest,this,&CMainMenueDlg::showClassIconInStudentRequestUI);

    QObject::connect(this,&CMainMenueDlg::startInitStudentRequestDataBaseTable,this,&CMainMenueDlg::initStudentRequestDataBaseTable);
    emit this->startInitStudentRequestDataBaseTable();
    QObject::connect(this,&CMainMenueDlg::startGetStudentRequestTableData,this,&CMainMenueDlg::getStudentRequestTableData);

    QObject::connect(this,&CMainMenueDlg::startShowStudentRequestTableUI,this,&CMainMenueDlg::showStudentRequestTableUI);

    QObject::connect(this,&CMainMenueDlg:: startShowStudentRequestIndexUI,this,&CMainMenueDlg::showStudentRequestIndexUI);

    QObject::connect(this,&CMainMenueDlg::startGetStudentRequestCount,this,&CMainMenueDlg::getStudentRequestTableCount);

    //学生申请表下一页   
    QObject::connect(this->ui->pushButton_34,&QPushButton::clicked,[=](){
        QString strCondition = this->ui->lineEdit_11->text().trimmed();
        int index = this->ui->comboBox_3->currentIndex();
        int value = this->ui->comboBox_3->itemData(index).toInt();

        if(strCondition == "")
        {
            //执行的是全部结果的下一页操作
            this->showStudentRequestNextPage();
        }else if(strCondition != "" && value == 0)
        {
            this->showStudentRequestByStudentNameNextPage(strCondition);
        }else if(strCondition != "" && value == 1)
        {
            this->showStudentRequestByStudentIdNextPage(strCondition);
        }
    });


    //学生申请表上一页
    QObject::connect(this->ui->pushButton_35,&QPushButton::clicked,[=](){
        QString strCondition = this->ui->lineEdit_11->text().trimmed();
        int index = this->ui->comboBox_3->currentIndex();
        int value = this->ui->comboBox_3->itemData(index).toInt();
        if(strCondition == "")
        {
            //执行的是全部结果的上一页操作
            this->showStudentRequestLastPage();
        }else if(strCondition != "" && value == 0) //按学生姓名
        {
            this->showStudentRequestByStudentNameLastPage(strCondition);
        }else if(strCondition != "" && value == 1) //按学生学号
        {
            this->showStudentRequestByStudentIdLastPage(strCondition);
        }
    });

    QObject::connect(this->ui->pushButton_68,&QPushButton::clicked,this,&CMainMenueDlg::getStudentRequestByCondition);
}

void CMainMenueDlg::showStudentRequestByStudentIdLastPage(QString studentId)
{
    if(this->m_studentRequestCount == "0")
    {
        return;
    }
    //防止恶意刷新
    if(this->m_curStudentRequestIndex <= 1)
    {
        return ;
    }
    //清除当前表中的记录
    this->clearStudentRequestTableUI();
    //给当前页递减，并且不能低于1
    if(this->m_curStudentRequestIndex > 1)
    {
       this->m_curStudentRequestIndex -= 1;
    }
    this->getStudentRequestByStudentId(studentId);
    this->getStudentRequestByStudentIdCount(studentId);
}

void CMainMenueDlg::showStudentRequestByStudentIdNextPage(QString studentId)
{
    if(this->m_studentRequestCount == "0") //如果查询的结果集为空则不进行操作
    {
        return;
    }

    if(QString::number(this->m_curStudentRequestIndex) == this->m_studentRequestCount)
    {
        return;
    }
    //清除当前表中的记录
    this->clearStudentRequestTableUI();

    //给当前页自增，并且不能超过总页
    if(QString::number(this->m_curStudentRequestIndex) != this->m_studentRequestCount)
    {
        this->m_curStudentRequestIndex += 1;
    }
    this->getStudentRequestByStudentId(studentId);
    this->getStudentRequestByStudentIdCount(studentId);
}


typedef struct getStudentRequestByStudentIdCountArg
{
    CMainMenueDlg* thiz;
    QString acount;
    QString className;
    QString studentId;
}GetStudentRequestByStudentIdCountArg;

void CMainMenueDlg::getStudentRequestByStudentIdCount(QString studentId)
{
    GetStudentRequestByStudentIdCountArg* arg = new GetStudentRequestByStudentIdCountArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->studentId = studentId;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentRequestByStudentIdCount,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentRequestByStudentIdCount(LPVOID arg)
{
     GetStudentRequestByStudentIdCountArg* gInfo = ( GetStudentRequestByStudentIdCountArg*)arg;
    int ret =  gInfo->thiz->m_mainMenueContorller->getStudentRequestByStudentIdCount(gInfo->acount
                                                                            ,gInfo->className
                                                                            ,gInfo->studentId);
    gInfo->thiz->m_studentRequestCount = QString::number(ret);
    emit gInfo->thiz->startShowStudentRequestIndexUI();
    delete gInfo;
    _endthreadex(0);
    return 0;
}

typedef struct getStudentRequestByStudentIdArg
{
    CMainMenueDlg* thiz;
    QString studentId;
    QString className;
    QString acount;
    int curIndex;
}GetStudentRequestByStudentIdArg;

void CMainMenueDlg::getStudentRequestByStudentId(QString studentId)
{
    GetStudentRequestByStudentIdArg* arg = new GetStudentRequestByStudentIdArg();
    arg->thiz = this;
    arg->studentId = studentId;
    arg->className =  this->m_classInfoSelected;
    arg->curIndex = this->m_curStudentRequestIndex;
    arg->acount = this->m_acount;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentRequestByStudentId,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentRequestByStudentId(LPVOID arg)
{
    GetStudentRequestByStudentIdArg* gInfo =(GetStudentRequestByStudentIdArg*)arg;
    std::vector<std::vector<std::string>> ret =  gInfo->thiz->m_mainMenueContorller->
            getStudentRequestByStudentId(gInfo->acount
                                           ,gInfo->className,
                                           gInfo->curIndex
                                           ,gInfo->studentId);
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
    //发送数据回显信号
    emit gInfo->thiz->startShowStudentRequestTableUI(result);
    delete gInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::showStudentRequestByStudentNameLastPage(QString studentName)
{
    if(this->m_studentRequestCount == "0")
    {
        return;
    }
    //防止恶意刷新
    if(this->m_curStudentRequestIndex <= 1)
    {
        return ;
    }
    //清除当前表中的记录
    this->clearStudentRequestTableUI();
    //给当前页递减，并且不能低于1
    if(this->m_curStudentRequestIndex > 1)
    {
       this->m_curStudentRequestIndex -= 1;
    }
    this->getStudentRequestByStudentName(studentName);
    this->getStudentRequestByStudentNameCount(studentName);
}


void CMainMenueDlg::showStudentRequestByStudentNameNextPage(QString studentName)
{
    if(this->m_studentRequestCount == "0") //如果查询的结果集为空则不进行操作
    {
        return;
    }

    if(QString::number(this->m_curStudentRequestIndex) == this->m_studentRequestCount)
    {
        return;
    }
    //清除当前表中的记录
    this->clearStudentRequestTableUI();

    //给当前页自增，并且不能超过总页
    if(QString::number(this->m_curStudentRequestIndex) != this->m_studentRequestCount)
    {
        this->m_curStudentRequestIndex += 1;
    }
    this->getStudentRequestByStudentName(studentName);
    this->getStudentRequestByStudentNameCount(studentName);
}



typedef struct getStudentRequestByStudentNameCountArg
{
    QString studentName;
    QString className;
    QString acount;
    CMainMenueDlg* thiz;
}GetStudentRequestByStudentNameCountArg;

void CMainMenueDlg::getStudentRequestByStudentNameCount(QString studentName)
{
    GetStudentRequestByStudentNameCountArg* arg = new GetStudentRequestByStudentNameCountArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->studentName = studentName;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentRequestByStudentNameCount,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentRequestByStudentNameCount(LPVOID arg)
{
    GetStudentRequestByStudentNameCountArg* gInfo = (GetStudentRequestByStudentNameCountArg*)arg;
    int ret =  gInfo->thiz->m_mainMenueContorller->getStudentRequestByStudentNameCount(gInfo->acount
                                                                            ,gInfo->className
                                                                            ,gInfo->studentName);
    gInfo->thiz->m_studentRequestCount = QString::number(ret);
    emit gInfo->thiz->startShowStudentRequestIndexUI();
    delete gInfo;
    _endthreadex(0);
    return 0;
}

typedef struct getStudentRequestByConditionArg
{
    CMainMenueDlg* thiz;
}GetStudentRequestByConditionArg;

void CMainMenueDlg::getStudentRequestByCondition()
{
    GetStudentRequestByConditionArg* arg = new GetStudentRequestByConditionArg();
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentRequestByCondition,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentRequestByCondition(LPVOID arg)
{
    GetStudentRequestByConditionArg* gInfo = (GetStudentRequestByConditionArg*)arg;
    //这里进行逻辑判断
    QString strCondition = gInfo->thiz->ui->lineEdit_11->text().trimmed();
    int index = gInfo->thiz->ui->comboBox_3->currentIndex();
    int value = gInfo->thiz->ui->comboBox_3->itemData(index).toInt();
    gInfo->thiz->m_curStudentRequestIndex = 1;
    //进行判断情况执行不同的控制层的接口
    if(strCondition == "") //查询全部的情况
    {
        emit gInfo->thiz->startGetStudentRequestTableData();
        emit gInfo->thiz->startGetStudentRequestCount();
        delete gInfo;
        _endthreadex(0);
        return 0;
    }else if(strCondition != "" && value == 0) //按学生姓名
    {
        gInfo->thiz->getStudentRequestByStudentName(strCondition);
        gInfo->thiz->getStudentRequestByStudentNameCount(strCondition);
        delete gInfo;
        _endthreadex(0);
        return 0;
    }else if(strCondition != "" && value == 1)//按学生学号
    {
        gInfo->thiz->getStudentRequestByStudentId(strCondition);
        gInfo->thiz->getStudentRequestByStudentIdCount(strCondition);
        delete gInfo;
        _endthreadex(0);
        return 0;
    }else if(strCondition != "" && value == 2)//按申请时间
    {

        delete gInfo;
        _endthreadex(0);
        return 0;
    }
    delete gInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::showStudentRequestIndexUI()
{
    QString first = QString::number(this->m_curStudentRequestIndex);
    first += "/";
    first += this->m_studentRequestCount;
    this->ui->label_65->setText(first);
}

typedef struct getStudentRequestTableCountArg{
    QString className;
    QString acount;
    int curIndex;
    CMainMenueDlg* thiz;
}GetStudentRequestTableCountArg;

void CMainMenueDlg::getStudentRequestTableCount()
{
    GetStudentRequestTableCountArg* arg = new GetStudentRequestTableCountArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->curIndex = this->m_curStudentRequestIndex;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentRequestTableCountEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentRequestTableCountEntry(LPVOID arg)
{
    GetStudentRequestTableCountArg* gInfo = (GetStudentRequestTableCountArg*)arg;
    int ret =  gInfo->thiz->m_mainMenueContorller->getStudentRequestTableCount(gInfo->acount,gInfo->className,gInfo->curIndex);
    gInfo->thiz->m_studentRequestCount = QString::number(ret);
    //发送显示当前页的信号
    emit gInfo->thiz->startShowStudentRequestIndexUI();
    delete gInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::showStudentRequestNextPage()
{
    if(this->m_studentRequestCount == "0") //如果查询的结果集为空则不进行操作
    {
        return;
    }

    if(QString::number(this->m_curStudentRequestIndex) == this->m_studentRequestCount)
    {
        return;
    }
    //清除当前表中的记录
    this->clearStudentRequestTableUI();

    //给当前页自增，并且不能超过总页
    if(QString::number(this->m_curStudentRequestIndex) != this->m_studentRequestCount)
    {
        this->m_curStudentRequestIndex += 1;
    }
    emit this->startGetStudentRequestTableData();
    emit this->startGetStudentRequestCount();
}

void CMainMenueDlg::showStudentRequestLastPage()
{
    if(this->m_studentRequestCount == "0")
    {
        return;
    }
    //防止恶意刷新
    if(this->m_curStudentRequestIndex <= 1)
    {
        return ;
    }
    //清除当前表中的记录
    this->clearStudentRequestTableUI();
    //给当前页递减，并且不能低于1
    if(this->m_curStudentRequestIndex > 1)
    {
       this->m_curStudentRequestIndex -= 1;
    }
    emit this->startGetStudentRequestTableData();
    emit this->startGetStudentRequestCount();
}

void CMainMenueDlg::clearStudentRequestTableUI()
{
    //隐藏序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QCheckBox*> buttons = this->m_studentRequestCheckVec.at(i)->findChildren<QCheckBox*>();
        for (QCheckBox *button : buttons) {
            button->setVisible(false);
        }
    }

    //清除学生姓名
    for(int i = 0 ; i < 8 ; i++)
    {
       for(QLabel* lab : this->m_studentRequestNameVec)
       {
           lab->setText("");
       }
    }

    //清除学生学号
    for(int i = 0 ; i < 8 ; i++)
    {
        for (QLabel *button : this->m_studentRequestStudentIdVec) {
            button->setText("");
        }
    }

    //清除申请时间
    for(int i = 0 ; i < 8;i++)
    {
        for (QLabel *button : this->m_studentRequestTimeVec) {
            button->setText("");
        }
    }

    //清除化操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QPushButton*> optButton = this->m_studentRequestOpetators.at(i)->findChildren<QPushButton*>();
        for (QPushButton *button : optButton) {
            button->setVisible(false);
        }
    }
}

void CMainMenueDlg::showStudentRequestTableUI(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    //进行UI显示
   this->clearStudentRequestTableUI();
   //将数据进行插入到表格中
   for(int i = 0 ; i < ret->size(); i++)
   {
       //显示序号
       QList<QCheckBox*> buttons = this->m_studentRequestCheckVec.at(i)->findChildren<QCheckBox*>();
       for (QCheckBox *button : buttons) {
           button->setVisible(true);
       }

       //显示学生姓名
       QString str = ret->at(i).at(0);
       this->m_studentRequestNameVec.at(i)->setText(str);

       //显示学生Id
       str = ret->at(i).at(1);
       this->m_studentRequestStudentIdVec.at(i)->setText(str);

       //显示申请时间
       str = ret->at(i).at(2);
       this->m_studentRequestTimeVec.at(i)->setText(str);

       //显示操作按钮
       QList<QPushButton*> optButton = this->m_studentRequestOpetators.at(i)->findChildren<QPushButton*>();
       for (QPushButton *button : optButton) {
           button->setVisible(true);
       }
   }
   if(ret != nullptr)
   {
       delete ret;
   }
   qDebug()<<"学生申请表格UI显示完成!";
}


typedef struct getStudentRequestTableDataArg{
    int curIndex;
    QString className;
    QString acount;
    CMainMenueDlg* thiz;
}GetStudentRequestTableDataArg;

void CMainMenueDlg:: getStudentRequestTableData()
{
    GetStudentRequestTableDataArg* arg = new GetStudentRequestTableDataArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->curIndex = this->m_curStudentRequestIndex;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentRequestTableDataEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentRequestTableDataEntry(LPVOID arg)
{
    GetStudentRequestTableDataArg* gInfo = (GetStudentRequestTableDataArg*)arg;
    std::vector<std::vector<std::string>> ret =  gInfo->thiz->m_mainMenueContorller->getStudentRequestTableData(gInfo->className,gInfo->acount,gInfo->curIndex);
    //处理结果集
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
    //发送数据回显信号
    emit gInfo->thiz->startShowStudentRequestTableUI(result);
    delete gInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::initStudentRequestDataBaseTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitStudentRequestDataBaseTableEntry,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitStudentRequestDataBaseTableEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initStudentRequestDataBaseTable();
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::initStudentRequestTable()
{
    this->ui->tableWidget_3->setRowCount(8);
    this->ui->tableWidget_3->setColumnCount(5);
    this->ui->tableWidget_3->horizontalHeader()->hide();
    this->ui->tableWidget_3->verticalHeader()->hide();

    //设置列宽
    int width = this->ui->tableWidget_3->width();
    int heigth = this->ui->tableWidget_3->height();
    this->ui->tableWidget_3->setColumnWidth(0,width / 15);
    this->ui->tableWidget_3->setColumnWidth(1,width / 4.5);
    this->ui->tableWidget_3->setColumnWidth(2,width / 4.5);
    this->ui->tableWidget_3->setColumnWidth(3,width / 4.5);
    this->ui->tableWidget_3->setColumnWidth(4,width / 3.8);

    this->ui->tableWidget_3->setRowHeight(0,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(1,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(2,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(3,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(4,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(5,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(6,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(7,heigth/ 8);
}

typedef struct showClassIconInStudentRequestArg
{
    CMainMenueDlg* thiz;
    QString acount;
    QString className;
}ShowClassIconInStudentRequestArg;

void CMainMenueDlg::showClassIconInStudentRequest()
{
    ShowClassIconInStudentRequestArg* arg = new ShowClassIconInStudentRequestArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadShowClassIconInStudentRequest,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadShowClassIconInStudentRequest(LPVOID arg)
{
    ShowClassIconInStudentRequestArg* sInfo = (ShowClassIconInStudentRequestArg*)arg;
    //访问数据库，拿到图片路径
    std::vector<std::vector<std::string>> ret =  sInfo->thiz->m_mainMenueContorller->showClassIconInStudentRequest(sInfo->acount,sInfo->className);

    const char* p = ret.at(0).at(0).c_str();
    //进行网络访问拿到网络数据,生成QImage,并且进行信号发送QImage
    CClientSocket* clientSocket = new CClientSocket();
    clientSocket->initSocket();
    bool ret2 =  clientSocket->connectToServer();
    if(!ret2)
    {
        return 0;
    }
    //进行封包操作
    char* data = new char[1024];
    memset(data,'\0',sizeof(char) * 1024);
    strcpy(data,p);
    clientSocket->makePacket(data,strlen(data),2); //获取课程图标的指令为2
    delete[] data;
    //发送数据包
    char* packet = clientSocket->getPacket();
    long long packetSize = clientSocket->getPacketSize();
    int size =  clientSocket->Send(packet);
    qDebug()<<"send size: "<<size;

    //先获取服务端发送的文件大小 8字节
    char* fileSize = new char[8];
    memset(fileSize,'\0',sizeof(char) * 8);
    size = clientSocket->Recv(fileSize,8);
    long long fileSizeNum;
    memmove(&fileSizeNum,fileSize,8);
    delete[] fileSize;
    qDebug()<<"fileSize: "<<fileSizeNum;

    char* recvBuffer = new char[fileSizeNum];
    memset(recvBuffer,'\0',sizeof(char) * fileSizeNum);
    size = clientSocket->Recv(recvBuffer,fileSizeNum); //直接接收到的就是图片文件数据，没有多余内容
    qDebug()<<"recv size: "<<size;
    clientSocket->closeSocket();
    delete clientSocket;

    QByteArray ba(recvBuffer,fileSizeNum);
    QImage* image = new QImage();
    bool ret3 = image->loadFromData(ba,"PNG");
    if(!ret3)
    {
     qDebug()<<"返回false";
    }
    if(image->isNull())
    {
        qDebug()<<"原先获取的图像无效,";
    }

    //发送出显示图像的信号
    emit  sInfo->thiz->startShowClassIconInStudentRequest(image);
//    delete[] pixmapData;
    delete[] recvBuffer;

    delete sInfo;
    _endthreadex(0);
    return 0;
}

typedef struct deleteMultiClassInfoArg
{
    QString acount;
    QList<QString>* createTimeLst;
    CMainMenueDlg* thiz;
}DeleteMultiClassInfoArg;

void CMainMenueDlg::deleteMultiClassInfo()
{
    DeleteMultiClassInfoArg*  arg = new DeleteMultiClassInfoArg();
    arg->thiz = this;
    arg->acount = this->m_acount;

    QList<QString>* createTimeLst = new QList<QString>();
    for(int i = 0 ; i < this->m_classCheckVec.size();i++)
    {
        QList<QCheckBox*> ret =  this->m_classCheckVec.at(i)->findChildren<QCheckBox*>();
        for(QCheckBox* check :ret)
        {
            if(check->isChecked())
            {
                QString createTime = this->m_classCreateTimeVec.at(i)->text().trimmed();
                if(createTime != "")
                {
                    createTimeLst->push_back(createTime);
                }
            }
        }
    }
    arg->createTimeLst = createTimeLst;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteMultiClassInfo,arg,0,nullptr);
    //将复选框进行设置为未选中
    for(int i = 0 ; i < this->m_classCheckVec.size();i++)
    {
        QList<QCheckBox*> ret =  this->m_classCheckVec.at(i)->findChildren<QCheckBox*>();
        for(QCheckBox* check : ret)
        {
            check->setChecked(false);
        }
    }
    this->ui->checkBox_8->setChecked(false);
}

void CMainMenueDlg::initStudentRequestTableControl()
{
//    //初始化序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout();
        widget->setLayout(layout);
        QCheckBox* checkBox = new QCheckBox();
        checkBox->setText(QString::number(++this->m_sortNumStudentRequest));
        checkBox->setFont(QFont("黑体"));
        checkBox->setStyleSheet("QCheckBox{margin-left:25px;}");
        checkBox->setVisible(false);
        layout->addWidget(checkBox);
        checkBox->setParent(widget);
        this->ui->tableWidget_3->setCellWidget(i,0,widget);
        this->m_studentRequestCheckVec.push_back(widget);
    }

    //初始化显示学生姓名
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_3->setCellWidget(i,1,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentRequestNameVec.push_back(testName);
    }

    //初始化学生学号
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_3->setCellWidget(i,2,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentRequestStudentIdVec.push_back(testName);
    }

    //初始化申请时间
    for(int i = 0 ; i < 8;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_3->setCellWidget(i,3,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentRequestTimeVec.push_back(testName);
    }


    //初始化操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QPushButton* deleteBtn = new QPushButton("同意");
        deleteBtn->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        deleteBtn->setParent(widget);
        QPushButton* release = new QPushButton("不同意");
        release->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        release->setParent(widget);
        deleteBtn->setGeometry(100,10,70,30);
        release->setGeometry(deleteBtn->width() + 30 + deleteBtn->x() ,deleteBtn->y(),70,30);
        deleteBtn->setFont(QFont("黑体",12));
        release->setFont(QFont("黑体",12));
        deleteBtn->setVisible(false);
        release->setVisible(false);
        this->ui->tableWidget_3->setCellWidget(i,4,widget);
        this->m_studentRequestOpetators.push_back(widget);
    }
}


unsigned WINAPI CMainMenueDlg::threadDeleteMultiClassInfo(LPVOID arg)
{
    DeleteMultiClassInfoArg* dInfo = (DeleteMultiClassInfoArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteMultiClassInfo(dInfo->acount,*dInfo->createTimeLst);
    delete dInfo->createTimeLst;
    delete dInfo;
    emit dInfo->thiz->startGetClassTableInfo();
    emit dInfo->thiz->startGetClassTableIndex();
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::changeClassCurPageCheckBoxStatus(bool status)
{
    for(int i = 0 ; i < this->m_classCheckVec.size();i++)
    {
       QList<QCheckBox*> ret =  this->m_classCheckVec.at(i)->findChildren<QCheckBox*>();
       for(QCheckBox* check : ret)
       {
          check->setChecked(status);
       }
    }
}

void CMainMenueDlg::bindClassOperators()
{

    for(QVector<QWidget*>::iterator pos = this->m_classOperationsVec.begin(); pos != this->m_classOperationsVec.end();pos++)
    {
         QList<QPushButton*> ret = (*pos)->findChildren<QPushButton*>();
         for(QPushButton* btn : ret)
         {
             if(btn->text() == "删除")
             {
                 //绑定的删除操作的槽函数
                 QObject::connect(btn,&QPushButton::clicked,[=](){
                     //进行遍历是哪一个按钮，并获取对应的行号
                     int row = 0;
                     for(int i = 0 ; i < this->m_operators.size();i++)
                     {
                         QList<QPushButton*> buttons = this->m_classOperationsVec.at(i)->findChildren<QPushButton*>();
                         for(QPushButton* clickedBtn: buttons)
                         {
                             if(clickedBtn == btn)
                             {
                                 this->m_classCurPageIndex = 1;
                                 this->deleteClassInfoByDateTime(row);
                                 break;
                             }
                         }
                         row++;
                     }
                 });

             }else if(btn->text() == "查看详情")
             {
                 //绑定的发布操作的槽函数
                 QObject::connect(btn,&QPushButton::clicked,[=](){
                     int row = 0;
                     for(int i = 0 ; i < this->m_classOperationsVec.size();i++)
                     {
                         QList<QPushButton*> buttons = this->m_classOperationsVec.at(i)->findChildren<QPushButton*>();
                         for(QPushButton* clickedBtn: buttons)
                         {
                             if(clickedBtn == btn)
                             {
                                 this->m_curStudentRequestIndex = 1;
                                 this->ui->stackedWidget->setCurrentIndex(6);
                                 this->m_classInfoSelected = this->m_classNameVec.at(row)->text().trimmed();
                                 //进行显示学生申请动态数据
                                 this->showStudentRequestInfo();
                                 break;
                             }
                         }
                         row++;
                     }
                 });
             }
         }
    }
}

void CMainMenueDlg::showStudentRequestInfo()
{
    //显示被选中的课程名称
    this->ui->label_60->setText(this->m_classInfoSelected);

    //显示课程图标
     this->showClassIconInStudentRequest();

    //显示数据库表内容
    emit this->startGetStudentRequestTableData();
    emit this->startGetStudentRequestCount();
}

typedef struct deleteClassInfoByDateTimeArg
{
    CMainMenueDlg* thiz;
    QString acount;
    QString createTime;
}DeleteClassInfoByDateTimeArg;

void CMainMenueDlg::deleteClassInfoByDateTime(int row)
{
    //获取到同一行的创建时间
    QString createTime = this->m_classCreateTimeVec.at(row)->text().trimmed();
    qDebug()<<"createTime: "<<createTime;

    DeleteClassInfoByDateTimeArg* arg = new DeleteClassInfoByDateTimeArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->createTime = createTime;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteClassInfoByDateTimeEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadDeleteClassInfoByDateTimeEntry(LPVOID arg)
{
    DeleteClassInfoByDateTimeArg* dInfo = (DeleteClassInfoByDateTimeArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteClassInfoByDateTime(dInfo->acount,dInfo->createTime);
    //重新显示和请求数据
    emit dInfo->thiz->startGetClassTableInfo();
    emit dInfo->thiz->startGetClassTableIndex();
    delete dInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::showClassTableNextPage()
{
    if(this->m_classCount == "0") //如果查询的结果集为空则不进行操作
    {
        return;
    }

    if(QString::number(this->m_classCurPageIndex) == this->m_classCount)
    {
        return;
    }
    //清除当前表中的记录
    this->clearClassTableControl();

    //给当前页自增，并且不能超过总页
    if(QString::number(this->m_classCurPageIndex) != this->m_classCount)
    {
        this->m_classCurPageIndex += 1;
    }
    emit this->startGetClassTableInfo();
    emit this->startGetClassTableIndex();
}

void CMainMenueDlg::showClassTableLastPage()
{
    if(this->m_classCount == "0")
    {
        return;
    }
    //防止恶意刷新
    if(this->m_classCurPageIndex <= 1)
    {
        return ;
    }
    //清除当前表中的记录
   this->clearClassTableControl();
    //给当前页递减，并且不能低于1
    if(this->m_classCurPageIndex > 1)
    {
       this->m_classCurPageIndex -= 1;
    }
    emit this->startGetClassTableInfo();
    emit this->startGetClassTableIndex();
}

void CMainMenueDlg::showClassTableIndex()
{
    QString first = QString::number(this->m_classCurPageIndex);
    first += "/";
    first += this->m_classCount;
    this->ui->label_58->setText(first);
}

typedef struct getClassTableCountArg
{
    QString acount;
    CMainMenueDlg* thiz;
}GetClassTableCountArg;

void CMainMenueDlg::getClassTableCount()
{
    GetClassTableCountArg* arg = new GetClassTableCountArg();
    arg->acount = this->m_acount;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetClassTableCountEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetClassTableCountEntry(LPVOID arg)
{
    GetClassTableCountArg* gInfo = (GetClassTableCountArg*)arg;
    int ret =  gInfo->thiz->m_mainMenueContorller->getClassTableCount(gInfo->acount);
    gInfo->thiz->m_classCount = QString::number(ret);
    //进行发送信号，进行显示总页数
    emit gInfo->thiz->startShowClassTableIndex();
    delete gInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::showClassIconInStudentRequestUI(QImage* image)
{
    if(image == nullptr)
    {
        return ;
    }
    this->ui->label_56->setPixmap(QPixmap::fromImage(*image));
    this->ui->label_56->setScaledContents(true);
    delete image;
}


void CMainMenueDlg::showClassIconUI(QImage* image)
{
    QList<QLabel*> ret =  this->m_classIconVec.at(this->classIconIndex++)->findChildren<QLabel*>();
    for(QLabel* lab : ret)
    {
        if(image->isNull())
        {
            qDebug()<<"图像无效";
        }
        lab->setPixmap(QPixmap::fromImage(*image));
        lab->setScaledContents(true);
        delete image;
    }
}

void CMainMenueDlg::clearClassTableControl()
{
    //隐藏序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QCheckBox*> buttons = this->m_classCheckVec.at(i)->findChildren<QCheckBox*>();
        for (QCheckBox *button : buttons) {
            button->setVisible(false);
        }
    }

    //清除课程图标
    for(int i = 0 ; i < 8 ; i++)
    {
       QList<QLabel*> labels = this->m_classIconVec.at(i)->findChildren<QLabel*>();
       for(QLabel* lab : labels)
       {
           lab->setPixmap(QPixmap());
       }
    }

    //清除课程名称
    for(int i = 0 ; i < 8 ; i++)
    {
        for (QLabel *button : this->m_classNameVec) {
            button->setText("");
        }
    }

    //清除创建时间
    for(int i = 0 ; i < 8;i++)
    {
        for (QLabel *button : this->m_classCreateTimeVec) {
            button->setText("");
        }
    }

    //清除创建人
    for(int i = 0 ; i < 8 ;i++)
    {
        for (QLabel *button : this->m_classCreatorVec) {
            button->setText("");
        }
    }

    //清除化操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QPushButton*> optButton = this->m_classOperationsVec.at(i)->findChildren<QPushButton*>();
        for (QPushButton *button : optButton) {
            button->setVisible(false);
        }
    }
}

unsigned WINAPI CMainMenueDlg::showClassIcon(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    //进行接收图片并且显示到UI上
//    CClientSocket* clientSocket = CClientSocket::getInstance();
    CClientSocket* clientSocket = new CClientSocket();
    clientSocket->initSocket();
    bool ret2 =  clientSocket->connectToServer();
    if(!ret2)
    {
        return 0;
    }
    //进行封包操作
    char* data = new char[1024];
    memset(data,'\0',sizeof(char) * 1024);
    WaitForSingleObject(thiz->m_Event,INFINITE);
    strcpy(data,thiz->m_ClassIconPath.c_str());
    ResetEvent(thiz->m_Event);
    SetEvent(thiz->m_Event_2);
    ResetEvent(thiz->m_Event_2);
    clientSocket->makePacket(data,strlen(data),2); //获取课程图标的指令为2
    delete[] data;
    //发送数据包
    char* packet = clientSocket->getPacket();
    long long packetSize = clientSocket->getPacketSize();
    int size =  clientSocket->Send(packet);
    qDebug()<<"send size: "<<size;

    //先获取服务端发送的文件大小 8字节
    char* fileSize = new char[8];
    memset(fileSize,'\0',sizeof(char) * 8);
    size = clientSocket->Recv(fileSize,8);
    long long fileSizeNum;
    memmove(&fileSizeNum,fileSize,8);
    delete[] fileSize;
    qDebug()<<"fileSize: "<<fileSizeNum;

    char* recvBuffer = new char[fileSizeNum];
    memset(recvBuffer,'\0',sizeof(char) * fileSizeNum);
    size = clientSocket->Recv(recvBuffer,fileSizeNum); //直接接收到的就是图片文件数据，没有多余内容
    qDebug()<<"recv size: "<<size;
    clientSocket->closeSocket();
    delete clientSocket;

    QByteArray ba(recvBuffer,fileSizeNum);
    QImage* image = new QImage();
    bool ret3 = image->loadFromData(ba,"PNG");
    if(!ret3)
    {
     qDebug()<<"返回false";
    }
    if(image->isNull())
    {
        qDebug()<<"原先获取的图像无效,";
    }
    emit  thiz->startShowClassIcon(image);
//    delete[] pixmapData;
    delete[] recvBuffer;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::Dump(const BYTE* Data, size_t nSize)
{
    std::string strOut;  //用于存储整个包的数据的结果
    //strOut.resize(nSize);
    for (size_t i = 0; i < nSize; i++)
    {
        char buf[8] = "";
        if (i > 0 && (i % 16 == 0))
        {
            strOut += '\n';
        }
        snprintf(buf, sizeof(buf), "%02X", Data[i] & 0xFF);  //%02X的意思是 写入的十六进制占两位，不足位是填充前导零
        strOut += buf;
    }
    strOut += "\n";
    OutputDebugStringA(strOut.c_str()); //用于输出调试的字符串，类似于QDebug
}

void CMainMenueDlg::showClassTableInfo(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    this->classIconIndex = 0;
    //进行UI显示
    this->clearClassTableControl();
   //将数据进行插入到表格中
   for(int i = 0 ; i < ret->size(); i++)
   {
       //显示序号
       QList<QCheckBox*> buttons = this->m_classCheckVec.at(i)->findChildren<QCheckBox*>();
       for (QCheckBox *button : buttons) {
           button->setVisible(true);
       }

       //显示试卷图标
//       QString str = ret->at(i).at(0);
//       this->m_testPaperName.at(i)->setText(str);
       QByteArray arr =  ret->at(i).at(0).toLocal8Bit();
       this->m_ClassIconPath = arr.data();
       SetEvent(this->m_Event);
       HANDLE thread =  (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::showClassIcon,this,0,nullptr);

       WaitForSingleObject(this->m_Event_2,INFINITE);

       //显示课程名称
       QString str = ret->at(i).at(1);
       this->m_classNameVec.at(i)->setText(str);

       //显示创建时间
       str = ret->at(i).at(2);
       this->m_classCreateTimeVec.at(i)->setText(str);

       //创建人
       str = ret->at(i).at(3);
       this->m_classCreatorVec.at(i)->setText(str);

       //显示操作按钮
       QList<QPushButton*> optButton = this->m_classOperationsVec.at(i)->findChildren<QPushButton*>();
       for (QPushButton *button : optButton) {
           button->setVisible(true);
       }
   }
   if(ret != nullptr)
   {
       delete ret;
   }
   qDebug()<<"试卷表格UI显示完成!";
}

typedef struct getClassTableDataArg
{
    QString acount;
    int curPageIndex;
    CMainMenueDlg* thiz;
}GetClassTableDataArg;

void CMainMenueDlg::getClassTableData()
{
    GetClassTableDataArg* arg = new GetClassTableDataArg();
    arg->acount = this->m_acount;
    arg->curPageIndex = this->m_classCurPageIndex;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetClassTableDataEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetClassTableDataEntry(LPVOID arg)
{
    GetClassTableDataArg* dInfo = (GetClassTableDataArg*)arg;
    std::vector<std::vector<std::string>>ret = dInfo->thiz->m_mainMenueContorller->getClassTableData(dInfo->thiz->m_acount,dInfo->curPageIndex);
    //通过信号将结果显示到页面中
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
    emit dInfo->thiz->startShowClassTable(result);
    delete dInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::initClassTableDatabase()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitClassTableDatabaseEntry,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitClassTableDatabaseEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initClassTableDatabase();
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::initClassTableControl()
{
    //初始化序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout();
        widget->setLayout(layout);
        QCheckBox* checkBox = new QCheckBox();
        checkBox->setText(QString::number(++this->sortNumberClass));
        checkBox->setFont(QFont("黑体"));
        checkBox->setStyleSheet("QCheckBox{margin-left:25px;}");
        checkBox->setVisible(false);
        layout->addWidget(checkBox);
        checkBox->setParent(widget);
        this->ui->tableWidget_2->setCellWidget(i,0,widget);
        this->m_classCheckVec.push_back(widget);
    }

    //初始化课程图标
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QLabel* testName = new QLabel(widget);
        testName->setGeometry(0,0,135,159);
//        testName->setPixmap(QPixmap(":/icons/acount.png"));
        testName->setScaledContents(true);
        this->ui->tableWidget_2->setCellWidget(i,1,widget);
        this->m_classIconVec.push_back(widget);
    }

    //初始化课程名称
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_2->setCellWidget(i,2,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_classNameVec.push_back(testName);
    }

    //初始化创建时间
    for(int i = 0 ; i < 8;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_2->setCellWidget(i,3,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_classCreateTimeVec.push_back(testName);
    }

    //初始化创建人
    for(int i = 0 ; i < 8 ;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_2->setCellWidget(i,4,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_classCreatorVec.push_back(testName);
    }


    //初始化操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QPushButton* deleteBtn = new QPushButton("删除");
        deleteBtn->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        deleteBtn->setParent(widget);
        QPushButton* release = new QPushButton("查看详情");
        release->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        release->setParent(widget);
        deleteBtn->setGeometry(20,63,150,40);
        release->setGeometry(deleteBtn->width() + 30,deleteBtn->y(),150,40);
        deleteBtn->setFont(QFont("黑体",12));
        release->setFont(QFont("黑体",12));
        deleteBtn->setVisible(false);
        release->setVisible(false);
        this->ui->tableWidget_2->setCellWidget(i,5,widget);
        this->m_classOperationsVec.push_back(widget);
    }

    this->bindClassOperators();
}

void CMainMenueDlg::initClassTable()
{
    this->ui->tableWidget_2->setRowCount(8);
    this->ui->tableWidget_2->setColumnCount(6);
    this->ui->tableWidget_2->horizontalHeader()->hide();
    this->ui->tableWidget_2->verticalHeader()->hide();

    //设置列宽
    int width = this->ui->tableWidget_2->width();
    int heigth = this->ui->tableWidget_2->height();
    this->ui->tableWidget_2->setColumnWidth(0,width / 15);
    this->ui->tableWidget_2->setColumnWidth(1,width / 10);
    this->ui->tableWidget_2->setColumnWidth(2,width / 5);
    this->ui->tableWidget_2->setColumnWidth(3,width / 5);
    this->ui->tableWidget_2->setColumnWidth(4,width / 6);
    this->ui->tableWidget_2->setColumnWidth(5,width / 4);

    this->ui->tableWidget_2->setRowHeight(0,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(1,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(2,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(3,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(4,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(5,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(6,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(7,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(8,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(9,heigth/ 4);
}

typedef struct deleteMultiClickBtnArg
{
    QString acount;
    QList<QString>* createTimeLst;
    CMainMenueDlg* thiz;
}DeleteMultiClickBtnArg;

void CMainMenueDlg::deleteMultiClickBtn()
{
    DeleteMultiClickBtnArg*  arg = new DeleteMultiClickBtnArg();
    arg->thiz = this;
    arg->acount = this->m_acount;

    QList<QString>* createTimeLst = new QList<QString>();
    for(int i = 0 ; i < this->m_checkVec.size();i++)
    {
        QList<QCheckBox*> ret =  m_checkVec.at(i)->findChildren<QCheckBox*>();
        for(QCheckBox* check :ret)
        {
            if(check->isChecked())
            {
                QString createTime = this->m_createTime.at(i)->text().trimmed();
                if(createTime != "")
                {
                    createTimeLst->push_back(createTime);
                }
            }
        }
    }
    arg->createTimeLst = createTimeLst;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteMultiClickBtnEntry,arg,0,nullptr);
    //将复选框进行设置为未选中
    for(int i = 0 ; i < this->m_checkVec.size();i++)
    {
        QList<QCheckBox*> ret =  this->m_checkVec.at(i)->findChildren<QCheckBox*>();
        for(QCheckBox* check : ret)
        {
            check->setChecked(false);
        }
    }
}

unsigned WINAPI CMainMenueDlg::threadDeleteMultiClickBtnEntry(LPVOID arg)
{
      DeleteMultiClickBtnArg* dInfo = (DeleteMultiClickBtnArg*)arg;
      dInfo->thiz->m_mainMenueContorller->deleteMultiClickBtn(dInfo->acount,*dInfo->createTimeLst);
      delete dInfo->createTimeLst;
      delete dInfo;
      dInfo->thiz->getCurPageIndexTableData();
      dInfo->thiz->getTablePageCount();
      _endthreadex(0);
      return 0;
}

typedef struct deleteFromShortAnswerArg
{
    QString acount;
    QString createTime;
    CMainMenueDlg* thiz;
}DeleteFromShortAnswerArg;

void CMainMenueDlg::deleteFromShortAnswer(QString createTime)
{
    DeleteFromShortAnswerArg* arg = new DeleteFromShortAnswerArg();
    arg->thiz = this;
    arg->acount =this->m_acount;
    arg->createTime = createTime;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteFromShortAnswerEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadDeleteFromShortAnswerEntry(LPVOID arg)
{
    DeleteFromShortAnswerArg* dInfo = ( DeleteFromShortAnswerArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteFromShortAnswer(dInfo->acount,dInfo->createTime);
    delete dInfo;
    _endthreadex(0);
    return 0;
}

typedef struct deleteFromJudgeArg{
    QString acount;
    QString createTime;
    CMainMenueDlg* thiz;
}DeleteFromJudgeArg;

void CMainMenueDlg::deleteFromJudge(QString createTime)
{
    DeleteFromJudgeArg* arg = new DeleteFromJudgeArg();
    arg->thiz = this;
    arg->acount =this->m_acount;
    arg->createTime = createTime;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteFromJudgeEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadDeleteFromJudgeEntry(LPVOID arg)
{
    DeleteFromJudgeArg* dInfo = (DeleteFromJudgeArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteFromJudge(dInfo->acount,dInfo->createTime);
    delete dInfo;
    _endthreadex(0);
    return 0;
}

typedef struct deleteFromMultiChoiseArg
{
    QString acount;
    QString createTime;
    CMainMenueDlg* thiz;
}DeleteFromMultiChoiseArg;

void CMainMenueDlg::deleteFromMultiChoise(QString createTime)
{
 DeleteFromMultiChoiseArg* arg = new DeleteFromMultiChoiseArg();
 arg->thiz = this;
 arg->acount = this->m_acount;
 arg->createTime =  createTime;
 _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteFromMultiChoiseEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadDeleteFromMultiChoiseEntry(LPVOID arg)
{
    DeleteFromMultiChoiseArg* dInfo = (DeleteFromMultiChoiseArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteFromMultiChoise(dInfo->acount,dInfo->createTime);
    delete dInfo;
    _endthreadex(0);
    return 0;
}

typedef struct deleteFromSignalChoiseArg
{
 QString acount;
 QString createTime;
 CMainMenueDlg* thiz;
}DeleteFromSignalChoiseArg;

void CMainMenueDlg::deleteFromSignalChoise(QString createTime)
{
    DeleteFromSignalChoiseArg* arg = new DeleteFromSignalChoiseArg();
    arg->thiz =this;
    arg->acount = this->m_acount;
    arg->createTime = createTime;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteFromSignalChoiseEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadDeleteFromSignalChoiseEntry(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteFromSignalChoise(dInfo->acount,dInfo->createTime);
    delete dInfo;
    _endthreadex(0);
    return 0;
}


void CMainMenueDlg::changeCurPageCheckBoxStatus(bool status)
{
    for(int i = 0 ; i < this->m_checkVec.size();i++)
    {
       QList<QCheckBox*> ret =  this->m_checkVec.at(i)->findChildren<QCheckBox*>();
       for(QCheckBox* check : ret)
       {
          check->setChecked(status);
       }
    }
}


void CMainMenueDlg::updateStatusClickBtn(int row)
{

}

typedef struct deleteClickBtnArg
{
    QString acount;
    QString createTime;
    CMainMenueDlg* thiz;
}DeleteClickBtnArg;

void CMainMenueDlg::deleteClickBtn(int row)
{
    //获取到同一行的创建时间
    QString createTime = this->m_createTime.at(row)->text().trimmed();
    qDebug()<<"createTime: "<<createTime; 

    this->deleteFromSignalChoise(createTime);
    this->deleteFromMultiChoise(createTime);
    this->deleteFromJudge(createTime);
    this->deleteFromShortAnswer(createTime);

    DeleteClickBtnArg* arg = new DeleteClickBtnArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->createTime = createTime;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteClickBtnEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadDeleteClickBtnEntry(LPVOID arg)
{
   DeleteClickBtnArg* dInfo = (DeleteClickBtnArg*)arg;
   dInfo->thiz->m_mainMenueContorller->deleteClickBtn(dInfo->acount,dInfo->createTime);
   //进行删除完成后重新进行查询和显示结果
   dInfo->thiz->getCurPageIndexTableData();
   dInfo->thiz->getTablePageCount();
   delete dInfo;
   _endthreadex(0);
   return 0;
}

void  CMainMenueDlg::bindOperatorBtns()
{
    for(QVector<QWidget*>::iterator pos = this->m_operators.begin(); pos != this->m_operators.end();pos++)
    {
         QList<QPushButton*> ret = (*pos)->findChildren<QPushButton*>();
         for(QPushButton* btn : ret)
         {
             if(btn->text() == "删除")
             {
                 //绑定的删除操作的槽函数
                 QObject::connect(btn,&QPushButton::clicked,[=](){
                     //进行遍历是哪一个按钮，并获取对应的行号
                     int row = 0;
                     for(int i = 0 ; i < this->m_operators.size();i++)
                     {
                         QList<QPushButton*> buttons = this->m_operators.at(i)->findChildren<QPushButton*>();
                         for(QPushButton* clickedBtn: buttons)
                         {
                             if(clickedBtn == btn)
                             {
                                 this->deleteClickBtn(row);
                                 break;
                             }
                         }
                         row++;
                     }
                 });

             }else if(btn->text() == "发布")
             {
                 //绑定的发布操作的槽函数
                 QObject::connect(btn,&QPushButton::clicked,[=](){
                     int row = 0;
                     for(int i = 0 ; i < this->m_operators.size();i++)
                     {                       
                         QList<QPushButton*> buttons = this->m_operators.at(i)->findChildren<QPushButton*>();
                         for(QPushButton* clickedBtn: buttons)
                         {
                             if(clickedBtn == btn)
                             {
                                 this->updateStatusClickBtn(row);
                                 break;
                             }
                         }
                         row++;
                     }
                 });
             }
         }
    }
}

typedef struct getTableDataByFindTestNameCountArg{
    CMainMenueDlg* thiz;
    QString acount;
    QString testPaperName;
}GetTableDataByFindTestNameCountArg;

void CMainMenueDlg::getTableDataByFindTestNameCount()
{
    GetTableDataByFindTestNameCountArg* arg = new GetTableDataByFindTestNameCountArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->testPaperName = this->ui->lineEdit_5->text().trimmed();
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetTableDataByFindTestNameCountEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetTableDataByFindTestNameCountEntry(LPVOID arg)
{
    GetTableDataByFindTestNameCountArg* gInfo = (GetTableDataByFindTestNameCountArg*)arg;
    int ret =  gInfo->thiz->m_mainMenueContorller->getTableDataByFindTestNameCount(gInfo->acount,gInfo->testPaperName);
    gInfo->thiz->m_pageCount = QString::number(ret);
    emit gInfo->thiz->startShowPageIndex();
    delete gInfo;
    _endthreadex(0);
    return 0;
}

typedef struct getTablePageCountNotPublishedArg{
    QString acount;
    QString status;
    CMainMenueDlg* thiz;
}GetTablePageCountNotPublishedArg;

void CMainMenueDlg::getTablePageCountNotPublished()
{
    GetTablePageCountNotPublishedArg* arg = new GetTablePageCountNotPublishedArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->status = "0";
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetTablePageCountNotPublishedEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetTablePageCountNotPublishedEntry(LPVOID arg)
{
    GetTablePageCountNotPublishedArg* gInfo = (GetTablePageCountNotPublishedArg*)arg;
    int ret = gInfo->thiz->m_mainMenueContorller->getTablePageCountNotPublished(gInfo->acount,gInfo->status);
    gInfo->thiz->m_pageCount =QString::number(ret);
    emit gInfo->thiz->startShowPageIndex();
    delete gInfo;
    _endthreadex(0);
    return 0;
}

typedef struct getTablePageCountPublished{
    QString acount;
    QString status;
    CMainMenueDlg* thiz;
}GetTablePageCountPublished;

void CMainMenueDlg::getTablePageCountPublished()
{
    GetTablePageCountPublished* arg = new GetTablePageCountPublished();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->status = "1";
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetTablePageCountPublishedEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetTablePageCountPublishedEntry(LPVOID arg)
{
    GetTablePageCountPublished* gInfo = (GetTablePageCountPublished*)arg;
    int ret = gInfo->thiz->m_mainMenueContorller->getTablePageCountPublished(gInfo->acount,gInfo->status);
    gInfo->thiz->m_pageCount =QString::number(ret);
    emit gInfo->thiz->startShowPageIndex();
    _endthreadex(0);
    delete gInfo;
    return 0;
}

typedef struct getTableDataByFindTestNameArg
{
    int curPageIndex;
    QString acount;
    QString testPaperName;
    CMainMenueDlg* thiz;
}GetTableDataByFindTestNameArg;

void CMainMenueDlg::getTableDataByFindTestName()
{
    if(this->ui->lineEdit_5->text().trimmed() == "") //如果模糊查询的条件为空的话默认转为查询全部
    {
        this->m_testPaperStatusChoise = 0;
    }else{
        this->m_testPaperStatusChoise = 3;
    }
    this->curPageIndex = 1;
    GetTableDataByFindTestNameArg* arg = new GetTableDataByFindTestNameArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->curPageIndex = this->curPageIndex;
    arg->testPaperName = this->ui->lineEdit_5->text().trimmed();
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetTableDataByFindTestNameEntry,arg,0,nullptr);
    this->getTableDataByFindTestNameCount();
}

unsigned WINAPI CMainMenueDlg::threadGetTableDataByFindTestNameEntry(LPVOID arg)
{
    GetTableDataByFindTestNameArg* gInfo = (GetTableDataByFindTestNameArg*)arg;
    std::vector<std::vector<std::string>> ret =  gInfo->thiz->m_mainMenueContorller->getTableDataByFindTestName(gInfo->curPageIndex
                                                                   ,gInfo->acount
                                                                   ,gInfo->testPaperName);
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
    emit gInfo->thiz->startShowCurPageIndexTable(result);
    delete gInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg:: showLastPageIndexTable()
{
    if(this->m_pageCount == "0")
    {
        return;
    }
    //防止恶意刷新
    if(this->curPageIndex <= 1)
    {
        return ;
    }
    //清除当前表中的记录
    this->clearTestPaperTableContorl();
    //给当前页递减，并且不能低于1
    if(this->curPageIndex > 1)
    {
        this->curPageIndex -= 1;
    }
    if(this->m_testPaperStatusChoise == 0) //选择状态为全部执行逻辑
    {
        //进行重新调用控制层获取数据
        this->getCurPageIndexTableData();
        //重新显示总量
        this->getTablePageCount();
    }else if(this->m_testPaperStatusChoise == 1)//选择状态为 已发布 执行逻辑
    {
        this->getCurPageIndexTableDataPubulished();
        this->getTablePageCountPublished();
    }else if(this->m_testPaperStatusChoise == 2)//选择状态为 未发布 执行逻辑
    {
        this->getCurPageIndexTableDataNotPubulished();
        this->getTablePageCountNotPublished();
    }else if(this->m_testPaperStatusChoise == 3) //进行的是模糊查询的上一页操作
    {
        this->getTableDataByFindTestName();
        this->getTableDataByFindTestNameCount();
    }
}

void CMainMenueDlg::showNextPageIndexTable()
{
    if(this->m_pageCount == "0") //如果查询的结果集为空则不进行操作
    {
        return;
    }

    if(QString::number(this->curPageIndex) == this->m_pageCount)
    {
        return;
    }
    //清除当前表中的记录
    this->clearTestPaperTableContorl();

    //给当前页自增，并且不能超过总页
    if(QString::number(this->curPageIndex) != this->m_pageCount)
    {
        this->curPageIndex += 1;
    }

    if(this->m_testPaperStatusChoise == 0) //选择状态为全部执行逻辑
    {
        //进行重新调用控制层获取数据
        this->getCurPageIndexTableData();
        //重新显示总量
        this->getTablePageCount();
    }else if(this->m_testPaperStatusChoise == 1)//选择状态为 已发布 执行逻辑
    {
        this->getCurPageIndexTableDataPubulished();
        this->getTablePageCountPublished();
    }else if(this->m_testPaperStatusChoise == 2)//选择状态为 未发布 执行逻辑
    {
        this->getCurPageIndexTableDataNotPubulished();
        this->getTablePageCountNotPublished();
    }else if(this->m_testPaperStatusChoise == 3) //进行的是模糊查询的下一页操作
    {
        this->getTableDataByFindTestName();
        this->getTableDataByFindTestNameCount();
    }
}

void CMainMenueDlg::clearTestPaperTableContorl()
{
    //隐藏序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QCheckBox*> buttons = this->m_checkVec.at(i)->findChildren<QCheckBox*>();
        for (QCheckBox *button : buttons) {
            button->setVisible(false);
        }
    }

    //清除试卷名称
    for(int i = 0 ; i < 8 ; i++)
    {
        for (QLabel *button : this->m_testPaperName) {
            button->setText("");
        }
    }

    //清除题量
    for(int i = 0 ; i < 8 ; i++)
    {
        for (QLabel *button : this->m_testPaperCount) {
            button->setText("");
        }
    }

    //清除创建时间
    for(int i = 0 ; i < 8;i++)
    {
        for (QLabel *button : this->m_createTime) {
            button->setText("");
        }
    }

    //清除出卷人
    for(int i = 0 ; i < 8 ;i++)
    {
        for (QLabel *button : this->m_creater) {
            button->setText("");
        }
    }

    //清除化发布状态
    for(int i = 0 ; i < 8 ;i++)
    {
        for (QLabel *button : this->m_status) {
            button->setText("");
        }
    }

    //清除化操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QPushButton*> optButton = this->m_operators.at(i)->findChildren<QPushButton*>();
        for (QPushButton *button : optButton) {
            button->setVisible(false);
        }
    }
}


void CMainMenueDlg::initTestPaperTableContorl()
{
    //初始化序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout();
        widget->setLayout(layout);
        QCheckBox* checkBox = new QCheckBox();
        checkBox->setText(QString::number(++this->sortNUmber));
        checkBox->setFont(QFont("黑体"));
        checkBox->setStyleSheet("QCheckBox{margin-left:45px;}");
        checkBox->setVisible(false);
        layout->addWidget(checkBox);
        checkBox->setParent(widget);
        this->ui->tableWidget->setCellWidget(i,0,widget);
        this->m_checkVec.push_back(widget);
    }

    //初始化试卷名称
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget->setCellWidget(i,1,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_testPaperName.push_back(testName);
    }

    //初始化题量
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget->setCellWidget(i,2,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_testPaperCount.push_back(testName);
    }

    //初始化创建时间
    for(int i = 0 ; i < 8;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",9));
        this->ui->tableWidget->setCellWidget(i,3,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_createTime.push_back(testName);
    }

    //初始化出卷人
    for(int i = 0 ; i < 8 ;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget->setCellWidget(i,4,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_creater.push_back(testName);
    }

    //初始化发布状态
    for(int i = 0 ; i < 8 ;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget->setCellWidget(i,5,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_status.push_back(testName);
    }

    //初始化操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout();
        widget->setLayout(layout);
        QPushButton* deleteBtn = new QPushButton("删除");
        deleteBtn->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        deleteBtn->setParent(widget);
        QPushButton* release = new QPushButton("发布");
        release->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        release->setParent(widget);
        layout->addWidget(deleteBtn);
        layout->addWidget(release);
        deleteBtn->setVisible(false);
        release->setVisible(false);
        this->ui->tableWidget->setCellWidget(i,6,widget);
        this->m_operators.push_back(widget);
    }

    //给操作按钮绑定信号槽函数
    this->bindOperatorBtns();
}

typedef struct getStudentRequestByStudentNameArg
{
    CMainMenueDlg* thiz;
    QString acount;
    QString className;
    int curIndex;
    QString studentName;
}GetStudentRequestByStudentNameArg;

void CMainMenueDlg::getStudentRequestByStudentName(QString studentName)
{
    GetStudentRequestByStudentNameArg* arg = new GetStudentRequestByStudentNameArg();
    arg->thiz = this;
    arg->studentName = studentName;
    arg->className =  this->m_classInfoSelected;
    arg->curIndex = this->m_curStudentRequestIndex;
    arg->acount = this->m_acount;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentRequestByStudentName,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentRequestByStudentName(LPVOID arg)
{
     GetStudentRequestByStudentNameArg* gInfo =(GetStudentRequestByStudentNameArg*)arg;
     std::vector<std::vector<std::string>> ret =  gInfo->thiz->m_mainMenueContorller->
             getStudentRequestByStudentName(gInfo->acount
                                            ,gInfo->className,
                                            gInfo->curIndex
                                            ,gInfo->studentName);
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
     //发送数据回显信号
     emit gInfo->thiz->startShowStudentRequestTableUI(result);
     delete gInfo;
     _endthreadex(0);
     return 0;
}

unsigned WINAPI CMainMenueDlg::threadGetCurPageIndexTableData(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    std::vector<std::vector<std::string>> ret = thiz->m_mainMenueContorller->showCurPageIndexTable(thiz->curPageIndex,thiz->m_acount);
    //转换成Qt的元对象后进行信号传递
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
    emit thiz->startShowCurPageIndexTable(result);
    _endthreadex(0);
    return 0;
}

typedef struct getCurPageIndexTableDataPubulishedArg
{
    int curPageIndex;
    QString acount;
    QString status;
    CMainMenueDlg* thiz;
}GetCurPageIndexTableDataPubulishedArg;

void CMainMenueDlg::getCurPageIndexTableDataPubulished()
{
    GetCurPageIndexTableDataPubulishedArg* arg = new GetCurPageIndexTableDataPubulishedArg();
    arg->thiz = this;
    arg->curPageIndex = this->curPageIndex;
    arg->acount = this->m_acount;
    arg->status = "1";
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetCurPageIndexTableDataPubulishedEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetCurPageIndexTableDataPubulishedEntry(LPVOID arg)
{
   GetCurPageIndexTableDataPubulishedArg* gInfo = (GetCurPageIndexTableDataPubulishedArg*)arg;
   std::vector<std::vector<std::string>>  ret =  gInfo->thiz->m_mainMenueContorller->getCurPageIndexTableDataPubulished(gInfo->curPageIndex,gInfo->acount,gInfo->status);
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
   emit gInfo->thiz->startShowCurPageIndexTable(result);
   delete gInfo;
   _endthreadex(0);
   return 0;
}

typedef struct getCurPageIndexTableDataNotPubulishedArg
{
    int curPageIndex;
    QString acount;
    QString status;
    CMainMenueDlg* thiz;
}GetCurPageIndexTableDataNotPubulishedArg;

void CMainMenueDlg::getCurPageIndexTableDataNotPubulished()
{
   GetCurPageIndexTableDataNotPubulishedArg* arg = new GetCurPageIndexTableDataNotPubulishedArg();
   arg->thiz = this;
   arg->curPageIndex = this->curPageIndex;
   arg->acount = this->m_acount;
   arg->status = "0";
   _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetCurPageIndexTableDataNotPubulishedEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetCurPageIndexTableDataNotPubulishedEntry(LPVOID arg)
{
   GetCurPageIndexTableDataNotPubulishedArg* gInfo = (GetCurPageIndexTableDataNotPubulishedArg*)arg;
   std::vector<std::vector<std::string>> ret = gInfo->thiz->m_mainMenueContorller->getCurPageIndexTableDataNotPubulished(gInfo->curPageIndex,
                                                                             gInfo->acount,
                                                                             gInfo->status);
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
   emit gInfo->thiz->startShowCurPageIndexTable(result);
   delete gInfo;
   _endthreadex(0);
   return 0;
}

void CMainMenueDlg::getCurPageIndexTableData()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetCurPageIndexTableData,this,0,nullptr);
}

void CMainMenueDlg::showCurPageIndexTable(QVector<QVector<QString>>* ret)
{
    this->clearTestPaperTableContorl();
   //将数据进行插入到表格中
   for(int i = 0 ; i < ret->size(); i++)
   {
       //显示序号
       QList<QCheckBox*> buttons = this->m_checkVec.at(i)->findChildren<QCheckBox*>();
       for (QCheckBox *button : buttons) {
           button->setVisible(true);
       }

       //显示试卷名
       QString str = ret->at(i).at(0);
       this->m_testPaperName.at(i)->setText(str);

       //显示题量
       str = ret->at(i).at(1);
       this->m_testPaperCount.at(i)->setText(str);

       //显示创建时间
       str = ret->at(i).at(2);
       this->m_createTime.at(i)->setText(str);
       //创建人
       str = ret->at(i).at(3);
       this->m_creater.at(i)->setText(str);

       //发布状态
       str = ret->at(i).at(4);
       this->m_status.at(i)->setText(str);

       //显示操作按钮
       QList<QPushButton*> optButton = this->m_operators.at(i)->findChildren<QPushButton*>();
       for (QPushButton *button : optButton) {
           button->setVisible(true);
       }
   }
   if(ret != nullptr)
   {
       delete ret;
   }
   qDebug()<<"试卷表格UI显示完成!";
}

void CMainMenueDlg::showPageIndex()
{
    QString first = QString::number(this->curPageIndex);
    first += "/";
    first += this->m_pageCount;
    this->ui->label_43->setText(first);
}

void CMainMenueDlg::initTableWidgetHeader()
{

    this->ui->tableWidget->setRowCount(8);
    this->ui->tableWidget->setColumnCount(7);
    this->ui->tableWidget->horizontalHeader()->hide();
    this->ui->tableWidget->verticalHeader()->hide();

    //设置列宽
    int width = this->ui->tableWidget->width();
    int heigth = this->ui->tableWidget->height();
    this->ui->tableWidget->setColumnWidth(0,135);
    this->ui->tableWidget->setColumnWidth(1,205);
    this->ui->tableWidget->setColumnWidth(2,135);
    this->ui->tableWidget->setColumnWidth(3,153);
    this->ui->tableWidget->setColumnWidth(4,135);
    this->ui->tableWidget->setColumnWidth(5,175);
    this->ui->tableWidget->setColumnWidth(6,445);

    this->ui->tableWidget->setRowHeight(0,heigth/ 8);
    this->ui->tableWidget->setRowHeight(1,heigth/ 8);
    this->ui->tableWidget->setRowHeight(2,heigth/ 8);
    this->ui->tableWidget->setRowHeight(3,heigth/ 8);
    this->ui->tableWidget->setRowHeight(4,heigth/ 8);
    this->ui->tableWidget->setRowHeight(5,heigth/ 8);
    this->ui->tableWidget->setRowHeight(6,heigth/ 8);
    this->ui->tableWidget->setRowHeight(7,heigth/ 8);
    this->ui->tableWidget->setRowHeight(8,heigth/ 8);
    this->ui->tableWidget->setRowHeight(9,heigth/ 8);

    // 动态设置每行的背景色
       for (int row = 0; row < this->ui->tableWidget->rowCount(); ++row) {
           QColor bgColor;
           if (row % 2 == 0) {
               bgColor = QColor(200, 255, 200); // 偶数行背景色
           } else {
               bgColor = QColor(255, 200, 200); // 奇数行背景色
           }
//           QBrush brush(bgColor);
           for (int col = 0; col <this->ui->tableWidget->columnCount(); ++col) {
//              this->ui->tableWidget->item(row, col)->setBackground(brush); //item拿到的是每一个单元格
               QTableWidgetItem* item = this->ui->tableWidget->item(row,col);
               if(item != nullptr)
               {
                   item->setBackgroundColor(bgColor);
               }

           }
       }
}

unsigned WINAPI CMainMenueDlg::threadGetTablePageCountEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_pageCount = thiz->m_mainMenueContorller->getTablePageCount(thiz->m_acount);
    emit thiz->startShowPageIndex();
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::getTablePageCount()
{
   //this->m_pageCount = this->m_mainMenueContorller->getTablePageCount(this->m_acount);
   _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetTablePageCountEntry,this,0,nullptr);
}

void CMainMenueDlg::clearTreeItemSignal()
{
    for(int i = 0 ; i < this->m_signalOperatorLst.size();i++)
    {
        QTreeWidgetItem* item = this->m_signalOperatorLst.at(i);
        delete item;
    }
    this->m_signalOperatorLst.clear();
    this->m_signalMap.clear();
    this->signalCount = 0;
}

void CMainMenueDlg::clearTreeItemMulti()
{
    for(int i = 0 ; i < this->m_multiOeratorLst.size();i++)
    {
        QTreeWidgetItem* item = this->m_multiOeratorLst.at(i);
        delete item;
    }
    this->m_multiOeratorLst.clear();
    this->m_multiMap.clear();
    this->multiCount = 0;
}

void CMainMenueDlg::clearTreeItemJudge()
{
    for(int i = 0 ; i < this->m_judgeLst.size();i++)
    {
        QTreeWidgetItem* item = this->m_judgeLst.at(i);
        delete item;
    }
    this->m_judgeLst.clear();
    this->m_judgeMap.clear();
    this->judgeCount = 0;
}

void CMainMenueDlg::clearTreeItemShortAnswer()
{
    for(int i = 0 ; i < this->m_ShortAnswerLst.size();i++)
    {
        QTreeWidgetItem* item = this->m_ShortAnswerLst.at(i);
        delete item;
    }
    this->m_ShortAnswerLst.clear();
    this->m_shortAnswerMap.clear();
    this->shortAnswerCount = 0;
}

 void CMainMenueDlg::clearShortAnswer()
 {
     this->ui->lineEdit_4->clear();
     this->ui->textEdit_16->clear();
     this->ui->textEdit_17->clear();
 }

 typedef struct shortAnswerInfoArg
 {
     QString grade;
     QString question;
     QString referenceAnswer;
     int order;
     CMainMenueDlg* thiz;
 }ShortAnswerInfoArg;

void CMainMenueDlg::addShortAnswerInfo(QString grade,QString question,QString referenceAnswer,int order)
{
    ShortAnswerInfoArg* arg = new ShortAnswerInfoArg();
    arg->thiz = this;
    arg->grade = grade;
    arg->question = question;
    arg->referenceAnswer = referenceAnswer;
    arg->order = order;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadAddShortAnswerInfoEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadAddShortAnswerInfoEntry(LPVOID arg)
{
    ShortAnswerInfoArg* pram = (ShortAnswerInfoArg*)arg;
    pram->thiz->m_mainMenueContorller->addShortAnswerInfo(pram->grade,pram->question,pram->referenceAnswer,
                                                       pram->order);
    delete pram;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::clearJudge()
{
    this->ui->lineEdit_3->clear();
    this->ui->textEdit_13->clear();
    this->ui->textEdit_14->clear();
    this->ui->textEdit_15->clear();

    this->ui->radioButton_5->setAutoExclusive(false);
    this->ui->radioButton_5->setChecked(false);
    this->ui->radioButton_5->setAutoExclusive(true);

    this->ui->radioButton_6->setAutoExclusive(false);
    this->ui->radioButton_6->setChecked(false);
    this->ui->radioButton_6->setAutoExclusive(true);
}

typedef struct addJudgeInfoArg
{
    QString grade;
    QString question;
    QString sessionTrue;
    QString sessionFalse;
    QString correctAnswer;
    int order;
    CMainMenueDlg* thiz;
}AddJudgeInfoArg;

void CMainMenueDlg::addJudgeInfo(QString grade,QString question,QString sessionTrue,QString sessionFalse,QString correctAnswer,int order)
{
    AddJudgeInfoArg* arg = new AddJudgeInfoArg();
    arg->grade = grade;
    arg->question = question;
    arg->sessionTrue = sessionTrue;
    arg->sessionFalse = sessionFalse;
    arg->correctAnswer = correctAnswer;
    arg->order = order;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadAddJudgeInfoEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadAddJudgeInfoEntry(LPVOID arg)
{
    AddJudgeInfoArg* aInfo = (AddJudgeInfoArg*)arg;
    aInfo->thiz->m_mainMenueContorller->addJudgeInfo(aInfo->grade,aInfo->question,aInfo->sessionTrue,
                                                     aInfo->sessionFalse,aInfo->correctAnswer,aInfo->order);
    delete aInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::clearMultiOption()
{
    this->ui->lineEdit_2->clear();
    this->ui->textEdit_6->clear();
    this->ui->textEdit_12->clear();
    this->ui->textEdit_7->clear();
    this->ui->textEdit_8->clear();
    this->ui->textEdit_9->clear();
    this->ui->textEdit_10->clear();
    this->ui->textEdit_11->clear();

    //清除多选框的选中
    this->ui->checkBox->setChecked(false);
    this->ui->checkBox_2->setChecked(false);
    this->ui->checkBox_3->setChecked(false);
    this->ui->checkBox_4->setChecked(false);
    this->ui->checkBox_5->setChecked(false);
    this->ui->checkBox_6->setChecked(false);
}

typedef struct addMultiChoiceInfoArg
{
    QString grade;
    QString question;
    QString sessionA;
    QString sessionB;
    QString sessionC;
    QString sessionD;
    QString sessionE;
    QString sessionF;
    QString correctOpetions;
    int order ;
    CMainMenueDlg* thiz;
}AddMultiChoiceInfoArg;

void CMainMenueDlg::addMultiChoiceInfo(QString grade,QString question,QString sessionA,
                                       QString sessionB,QString sessionC,QString sessionD,
                                       QString sessionE,QString sessionF,
                                       QString correctOpetions,int order)
{

   AddMultiChoiceInfoArg* arg = new  AddMultiChoiceInfoArg();
   arg->grade = grade;
   arg->question = question;
   arg->sessionA = sessionA;
   arg->sessionB = sessionB;
   arg->sessionC = sessionC;
   arg->sessionD = sessionD;
   arg->sessionE = sessionE;
   arg->sessionF = sessionF;
   arg->correctOpetions = correctOpetions;
   arg->order = order;
   arg->thiz = this;
   _beginthreadex(nullptr,0,&CMainMenueDlg::threadAddMultiChoiceInfoEntry,arg,0,nullptr);

}

unsigned WINAPI CMainMenueDlg::threadAddMultiChoiceInfoEntry(LPVOID arg)
{
    AddMultiChoiceInfoArg* aInfo = (AddMultiChoiceInfoArg*)arg;
    aInfo->thiz->m_mainMenueContorller->addMultiChoiceInfo(aInfo->grade,aInfo->question,aInfo->sessionA,
                                                           aInfo->sessionB,aInfo->sessionC,
                                                        aInfo->sessionD,aInfo->sessionE,aInfo->sessionF,
                                                        aInfo->correctOpetions,aInfo->order);
    delete aInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::clearSignalOption()
{
    this->ui->lineEdit->clear();
    this->ui->textEdit->clear();
    this->ui->textEdit_2->clear();
    this->ui->textEdit_3->clear();
    this->ui->textEdit_4->clear();
    this->ui->textEdit_5->clear();
    //设置所有的radiobutton都为未点击
    this->ui->radioButton->setAutoExclusive(false);
    this->ui->radioButton->setChecked(false);
    this->ui->radioButton->setAutoExclusive(true);

    this->ui->radioButton_2->setAutoExclusive(false);
    this->ui->radioButton_2->setChecked(false);
    this->ui->radioButton_2->setAutoExclusive(true);

    this->ui->radioButton_3->setAutoExclusive(false);
    this->ui->radioButton_3->setChecked(false);
    this->ui->radioButton_3->setAutoExclusive(true);

    this->ui->radioButton_4->setAutoExclusive(false);
    this->ui->radioButton_4->setChecked(false);
    this->ui->radioButton_4->setAutoExclusive(true);
}

typedef struct addSignalChoiceInfoArg
{
   QString grade;
   QString question;
   QString sessionA;
   QString sessionB;
   QString sessionC;
   QString sessionD;
   QString correctOptions;
   int order;
   CMainMenueDlg* thiz;
}AddSignalChoiceInfoArg;

void CMainMenueDlg::addSignalChoiceInfo(QString grade,QString question,QString sessionA,QString sessionB,QString sessionC,QString sessionD,QString correctOptions,int order)
{
    AddSignalChoiceInfoArg* arg = new AddSignalChoiceInfoArg();
    arg->correctOptions = correctOptions;
    arg->grade = grade;
    arg->order = order;
    arg->question = question;
    arg->sessionA = sessionA;
    arg->sessionB = sessionB;
    arg->sessionC = sessionC;
    arg->sessionD = sessionD;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadAddSignalChoiceInfoEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadAddSignalChoiceInfoEntry(LPVOID arg)
{
    AddSignalChoiceInfoArg* aInfo = (AddSignalChoiceInfoArg*)arg;
    aInfo->thiz->m_mainMenueContorller->addSignalChoiceInfo(aInfo->grade,aInfo->question,aInfo->sessionA
                                                            ,aInfo->sessionB,
                                                            aInfo->sessionC,aInfo->sessionD,
                                                            aInfo->correctOptions,aInfo->order);
    delete aInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::deleteTreeItemRecursively(QTreeWidgetItem* item) {
    if (!item) return; // 若传入的item为空，则直接返回

    // 获取并删除item的所有子项
    int childCount = item->childCount();
    for (int i = 0; i < childCount; ++i) {
        deleteTreeItemRecursively(item->takeChild(0)); // 递归删除子项，
       /*  注意：takeChild(0)会移除并返回第一个子项，
         因此每次循环都会处理下一个子项（因为列表已经更新）。
         如果您不希望修改原始子项列表（即不移除它们），
         则应使用child(i)来获取子项，并手动管理索引。
         但在此递归删除场景中，使用takeChild()是更合适的选择，
         因为它允许我们在遍历过程中直接修改列表。*/
    }
    // 删除当前item（现在已无子项）
    delete item;
}

void CMainMenueDlg::deleteAllTreeItems(QTreeWidget* treeWidget) {
    if (!treeWidget) return; // 若传入的treeWidget为空，则直接返回

    // 获取treeWidget的顶层项数量
    int topLevelItemCount = treeWidget->topLevelItemCount();
    for (int i = 0; i < topLevelItemCount; ++i) {
        // 获取并删除每一个顶层项及其所有子项
        deleteTreeItemRecursively(treeWidget->topLevelItem(i));
    }
     /*注意：此处我们并未清空treeWidget本身，只是删除了所有项。
     若您希望清空treeWidget（即移除所有项的指针，但不删除它们），
     则应在此处调用treeWidget->clear()，但请注意，这样做不会释放内存，
     因为clear()只会移除指针，不会delete指向的对象。
     由于我们已经递归删除了所有项，因此在此处调用clear()是多余的，
     除非您需要在之后重新向treeWidget添加项，并希望从UI中移除所有现有项。*/
}


unsigned WINAPI CMainMenueDlg::threadInitTestPaperTableEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initTestPaperTable();
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::initTestPaperTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitTestPaperTableEntry,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitSingleChoiceTableEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initSingleChoiceTable();
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::initSingleChoiceTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitSingleChoiceTableEntry,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitMultiChoiceTableEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initMultiChoiceTable();
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::initMultiChoiceTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitMultiChoiceTableEntry,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitJudgeTableEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initJudgeTable();
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::initJudgeTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitJudgeTableEntry,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitShortAnswerTableEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initShortAnswerTable();
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::initShortAnswerTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitShortAnswerTableEntry,this,0,nullptr);
}

void CMainMenueDlg::headPictureChange()
{
    QString fileName = QFileDialog::getOpenFileName(
         this,
         tr("请选择PNG图片,并且单张图片不得超过400KB"),
         QDir::homePath(),
         tr("PNG Files (*.png);;All Files (*)")
     );
     if (!fileName.isEmpty()) {
       qDebug()<<fileName;
       this->m_mainMenueContorller->changeHeadPicture(fileName,this->m_acount);
       emit this->startShowTeacherInfo(this->m_acount);
     } else {
       return;
     }
}

typedef struct changeGenderArg
{
   bool isChecked;
   CMainMenueDlg* thiz;
}ChangeGenderArg;

void CMainMenueDlg::changeGender(bool isChecked)
{
   ChangeGenderArg* arg = new ChangeGenderArg();
   arg->thiz = this;
   arg->isChecked = isChecked;
   _beginthreadex(nullptr,0,&CMainMenueDlg::threadChangeGenderEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadChangeGenderEntry(LPVOID arg)
{
    ChangeGenderArg* cInfo =  (ChangeGenderArg*)arg;
    cInfo->thiz->m_mainMenueContorller->changeGender(cInfo->isChecked,cInfo->thiz->m_acount);
    delete cInfo;
    _endthreadex(0);
    return 0;
}

typedef struct teacherAcountInfoArg
{
    QString acount;
    CMainMenueDlg* thiz;
}TeacherAcountInfoArg;

void CMainMenueDlg::getTeacherAcountInfoData()
{
    TeacherAcountInfoArg* arg = new TeacherAcountInfoArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetTeacherAcountInfoDataEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetTeacherAcountInfoDataEntry(LPVOID arg)
{
    TeacherAcountInfoArg* tInfo = (TeacherAcountInfoArg*)arg;
    std::vector<std::vector<std::string>> ret =  tInfo->thiz->m_mainMenueContorller->showTeacherAcountInfo(tInfo->acount); //view层调用conntorller层的接口全部写到子线程中
    emit tInfo->thiz->startShowTeacherAcountInfo(&ret);
    delete tInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::showTeacherAcountInfo(std::vector<std::vector<std::string>>* ret)
{
    QString name = QString::fromLocal8Bit(ret->at(0).at(0).c_str());
    QString teacherId = QString::fromLocal8Bit(ret->at(0).at(1).c_str());
    QString gender = QString::fromLocal8Bit(ret->at(0).at(2).c_str());
    QString phoneNumber = QString::fromLocal8Bit(ret->at(0).at(3).c_str());

    this->ui->label_39->setText(name);
    this->ui->label_40->setText(teacherId);
    if(gender == "1")
    {
      this->ui->radioButton_7->setChecked(true);
    }else if(gender == "0")
    {
        this->ui->radioButton_8->setChecked(true);
    }
    this->ui->label_41->setText(phoneNumber);
}

void CMainMenueDlg::setLoginedAcount(QString acount)
{
    this->m_acount = acount;
}

/*
网络通信的解决办法，1、定好一个数据包的包长
                2、循环发送
                3、循环接收
*/

void  CMainMenueDlg::showTeacherInfo(QString acount)
{
   std::vector<std::vector<std::string>> ret =  this->m_mainMenueContorller->showTeacherInfo(acount);
   std::string tempStr =  ret.at(0).at(0);
   QString str = QString::fromLocal8Bit(tempStr.c_str());
   qDebug()<<str;
   //对数据进行回显
   this->ui->label_3->setText(str);
   this->ui->label_name->setText(str);

   //头像回显
   if(ret.at(0).at(1) != "null")
   {
       //进行回显头像
       this->m_headPath = ret.at(0).at(1);
       this->m_recvHeadThead = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadShowHeadEntry,this,0,nullptr);
   }
}

void CMainMenueDlg::showHeadImageUI(QImage image)
{
    this->ui->label_head->setPixmap(QPixmap::fromImage(image));
    this->ui->label_head->setScaledContents(true);
    this->ui->label_head2->setPixmap(QPixmap::fromImage(image));
    this->ui->label_head2->setScaledContents(true);
}

void CMainMenueDlg::threadShowHead()
{
//    CClientSocket* clientSocket = CClientSocket::getInstance();
    CClientSocket* clientSocket = new CClientSocket();
    clientSocket->initSocket();
    bool ret2 =  clientSocket->connectToServer();
    if(!ret2)
    {
        return;
    }
    //进行封包操作
    char* data = new char[1024];
    memset(data,'\0',sizeof(char) * 1024);
    strcpy(data,this->m_headPath.c_str());
    clientSocket->makePacket(data,strlen(data),0);
    delete[] data;
    //发送数据包
    char* packet = clientSocket->getPacket();
    long long packetSize = clientSocket->getPacketSize();
    int size =  clientSocket->Send(packet);
    qDebug()<<"send size: "<<size;
    char* recvBuffer = new char[packetSize]; //服务器返回也是一个包的大小
    size =  clientSocket->Recv(recvBuffer);
    qDebug()<<"recv size: "<<size;
    clientSocket->closeSocket();
    delete clientSocket;
    //解包拿去数据
    char* p = recvBuffer;
    WORD head ;
    memcpy(&head,p,sizeof(WORD));
    p += sizeof(WORD);
    DWORD length;
    memcpy(&length,p,sizeof(DWORD));
    p += sizeof(DWORD);
    WORD cmd;
    memcpy(&cmd,p,sizeof(WORD));
    p += sizeof(WORD);
    char* pixmapData = new char[length]; //只要数据，不包含\0
    memmove(pixmapData,p,length);

    QByteArray ba(pixmapData,length);
    QImage image; 
    image.loadFromData(ba,"PNG");
    if(image.isNull())
    {
        qDebug()<<"头像获取失败！";
    }
    emit this->startShowHeadImage(image);
    delete[] pixmapData;
    delete[] recvBuffer;
}

unsigned WINAPI CMainMenueDlg::threadShowHeadEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->threadShowHead();
    _endthreadex(0);
    return 0;
}

unsigned WINAPI CMainMenueDlg::threadInitTeacherInfoTableEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initTeacherInfoTable();
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::initTeacherInfoTable()
{
   _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitTeacherInfoTableEntry,this,0,nullptr);
}

bool CMainMenueDlg::eventFilter (QObject* obj, QEvent* e) //原理底层跟一个定时器一样一直触发执行的函数
{
    if(obj == this->ui->label_name)
    {
        if(e->type() == QEvent::Enter)
        {
            this->m_exitLoginDlg->show();
        }
    }else if(obj == this->m_exitLoginDlg)
    {
        if(e->type() == QEvent::Leave)
        {
            this->m_exitLoginDlg->hide();
        }
    }
    return QDialog::eventFilter(obj,e);
}

CMainMenueDlg::~CMainMenueDlg()
{
    if(this->m_exitLoginDlg != nullptr)
    {
        delete this->m_exitLoginDlg;
        this->m_exitLoginDlg = nullptr;
    }
    if(this->m_signalOperator != nullptr)
    {
        delete this->m_signalOperator;
        this->m_signalOperator = nullptr;
    }
    if(this->m_multiOerator != nullptr)
    {
        delete this->m_multiOerator;
        this->m_multiOerator = nullptr;
    }
    if(this->m_judge != nullptr)
    {
        delete this->m_judge;
        this->m_judge = nullptr;
    }
    if(this->m_ShortAnswer != nullptr)
    {
        delete this->m_ShortAnswer;
        this->m_ShortAnswer = nullptr;
    }
    if(this->m_mainMenueContorller != nullptr)
    {
        delete this->m_mainMenueContorller;
        this->m_mainMenueContorller = nullptr;
    }

    for(QVector<QWidget*>::iterator pos = this->m_checkVec.begin(); pos != this->m_checkVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_checkVec.clear();

    for(QVector<QLabel*>::iterator pos = this->m_testPaperName.begin(); pos != this->m_testPaperName.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_testPaperName.clear();

    for(QVector<QLabel*>::iterator pos = this->m_testPaperCount.begin(); pos != this->m_testPaperCount.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_testPaperCount.clear();

    for(QVector<QLabel*>::iterator pos = this->m_createTime.begin(); pos != this->m_createTime.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_createTime.clear();

    for(QVector<QLabel*>::iterator pos = this->m_creater.begin(); pos != this->m_creater.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_creater.clear();

    for(QVector<QLabel*>::iterator pos = this->m_status.begin(); pos != this->m_status.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_status.clear();

    for(QVector<QWidget*>::iterator pos = this->m_operators.begin(); pos != this->m_operators.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_operators.clear();

    for(QVector<QWidget*>::iterator pos = this->m_classCheckVec.begin(); pos != this->m_classCheckVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_classCheckVec.clear();

    for(QVector<QWidget*>::iterator pos = this->m_classIconVec.begin(); pos != this->m_classIconVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_classIconVec.clear();

    for(QVector<QLabel*>::iterator pos = this->m_classNameVec.begin(); pos != this->m_classNameVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_classNameVec.clear();

    for(QVector<QLabel*>::iterator pos = this->m_classCreateTimeVec.begin(); pos != this->m_classCreateTimeVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_classCreateTimeVec.clear();

    for(QVector<QLabel*>::iterator pos =  this->m_classCreatorVec.begin(); pos !=  this->m_classCreatorVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_classCreatorVec.clear();

    for(QVector<QWidget*>::iterator pos =  this->m_classOperationsVec.begin(); pos !=  this->m_classOperationsVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_classOperationsVec.clear();

    for(QVector<QWidget*>::iterator pos = this->m_studentRequestCheckVec.begin(); pos != this->m_studentRequestCheckVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_studentRequestCheckVec.clear();

    for(QVector<QLabel*>::iterator pos =  this->m_studentRequestNameVec.begin(); pos !=  this->m_studentRequestNameVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_studentRequestNameVec.clear();

    for(QVector<QLabel*>::iterator pos =  this->m_studentRequestStudentIdVec.begin(); pos !=  this->m_studentRequestStudentIdVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_studentRequestStudentIdVec.clear();

    for(QVector<QLabel*>::iterator pos =  this->m_studentRequestTimeVec.begin(); pos !=  this->m_studentRequestTimeVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_studentRequestTimeVec.clear();

    for(QVector<QWidget*>::iterator pos =  this->m_studentRequestOpetators.begin(); pos !=  this->m_studentRequestOpetators.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_studentRequestOpetators.clear();

    //如果关闭界面，接收头像信息的线程还在执行的话就等待接收后结束线程
    WaitForSingleObject(this->m_recvHeadThead,INFINITE); //找到退出崩溃的原因，因为关闭界面的时候，接收头像线程还在执行，但是UI已经释放导致异常
    //释放容器中的QTreeItem
    this->deleteAllTreeItems(this->ui->treeWidget);
    delete ui;
}
