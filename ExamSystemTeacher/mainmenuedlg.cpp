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
    this->m_sortNumStudentManeger = 0;
    this->curPageIndexCorrect = 1;
    this->m_correctTestPaperCount = "0";

    this->strSignalLabelStyleSheet = "QLabel{border:none;background-color:#E1EFD8;border-bottom:1px solid #646465;}";
    this->strSignalWidgetStyleSheet = "QWidget{border:none;background-color:#E1EFD8;border-bottom:1px solid #646465;}";

    this->strDoubleLabelStyleSheet = "QLabel{border:none;background-color:#FFFFFF;border-bottom:1px solid #646465;}";
    this->strDoubleWidgetStyleSheet = "QWidget{border:none;background-color:#FFFFFF;border-bottom:1px solid #646465;}";

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
    this->m_correctMemberCurIndex = 1;

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

    this->m_studentManegerCount = "";
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

    this->bindStudentRequestOperators();
    this->initStudentManegerTable();
    this->initStudentManegerTableContorl();
    this->m_studentManegerCurPageIndex = 1;
    this->m_studentManegerEvent = CreateEvent(nullptr,false,false,nullptr);
    this->m_studentManegerEvent_2 = CreateEvent(nullptr,false,false,nullptr);
    this->bindStudentManegerOperators();

    QObject::connect(this,&CMainMenueDlg::startInitTeacherInfoTable,this,&CMainMenueDlg::initTeacherInfoTable);
    emit this->startInitTeacherInfoTable();

//    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
//        this->ui->stackedWidget->setCurrentIndex(5);
//    });

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
        this->getCurPageIndexCorrect();
        this->getCorrectTestPaperCount();
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
    QObject::connect(this,&CMainMenueDlg::startShowStudentHeadIconUI,this,&CMainMenueDlg::showStudentHeadIconUI);
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
        this->ui->label_67->setPixmap(QPixmap());
        this->clearStudentManegerTableUI();
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
        }else if(strCondition != "" && value == 2)
        {
            this->showStudentRequestByRequestTimeNextPage(strCondition);
        }
        emit this->ui->checkBox_9->toggled(false);
        this->ui->checkBox_9->setChecked(false);
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
        }else if(strCondition != "" && value == 2)
        {
            this->showStudentRequestByRequestTimeLastPage(strCondition);
        }
        emit this->ui->checkBox_9->toggled(false);
        this->ui->checkBox_9->setChecked(false);
    });

    QObject::connect(this->ui->pushButton_68,&QPushButton::clicked,this,&CMainMenueDlg::getStudentRequestByCondition);
    QObject::connect(this->ui->checkBox_9,&QCheckBox::toggled,this,&CMainMenueDlg::changeStudentRequestCurPageCheckBoxStatus);
    QObject::connect(this,&CMainMenueDlg::startInitJoinClassStudentManeageTable,this,&CMainMenueDlg::initJoinClassStudentManeageTable);
    emit this->startInitJoinClassStudentManeageTable();
    QObject::connect(this->ui->pushButton_33,&QPushButton::clicked,this,&CMainMenueDlg::agreeMultiRequestByStudentId);
    QObject::connect(this->ui->pushButton_36,&QPushButton::clicked,this,&CMainMenueDlg::degreeMultiRequestByStudentId);

    QObject::connect(this->ui->tabWidget,&QTabWidget::currentChanged,this,&CMainMenueDlg::initStudentInfoManagerData);

    QObject::connect(this,&CMainMenueDlg::startShowClassIconInStudentManagerUI,this,&CMainMenueDlg::showClassIconInStudentManagerUI);

    QObject::connect(this,&CMainMenueDlg::startShowStudentManegerCurPagaUI,this,&CMainMenueDlg::showStudentManegerCurPagaUI);

    QObject::connect(this,&CMainMenueDlg::startShowStudentManegerTableIndex,this,&CMainMenueDlg::showStudentManegerTableIndex);

    QObject::connect(this->ui->pushButton_41,&QPushButton::clicked,[=](){
        QString studentName = this->ui->lineEdit_12->text().trimmed();
        if(studentName == "")
        {
            //执行全部结果集的下一页操作
            this->showStudentManegerTableNextPage();
        }else
        {
            //执行按姓名模糊查询结果集的下一页
            this->showStudentManegerTableNextPageByStudentName(studentName);
        }
    });

    QObject::connect(this->ui->pushButton_40,&QPushButton::clicked,[=](){
        QString studentName = this->ui->lineEdit_12->text().trimmed();
        if(studentName == "")
        {
            //执行全部结果集的上一页操作
            this->showStudentManegerTableLastPage();
        }else
        {
            //执行按姓名模糊查询结果集的上一页
            this->showStudentManegerTableLastPageByStudentName(studentName);
        }
    });

    QObject::connect(this->ui->checkBox_10,&QCheckBox::toggled,this,&CMainMenueDlg::changeStudentManegerCurPageCheckBoxStatus);

    QObject::connect(this->ui->pushButton_39,&QPushButton::clicked,this,&CMainMenueDlg::deleteMultiManegerByStudentId);

    QObject::connect(this->ui->pushButton_69,&QPushButton::clicked,[=](){
        //进行按姓名进行模糊查询
        this->m_studentManegerCurPageIndex =1;
        QString studentName = this->ui->lineEdit_12->text().trimmed();
        if(studentName == "")
        {
            this->getStudentManegerCurPageData();
            this->getStudentManegerTableCount();
        }else
        {
          this->getStudentManegerCurPageDataByStudentName(studentName);
          this->getStudentManegerTableCountByStudentName(studentName);
        }
    });

    QObject::connect(this,&CMainMenueDlg::startShowCorrectTestPaper,this,&CMainMenueDlg::showCorrectTestPaperUI);
    QObject::connect(this,&CMainMenueDlg::startShowCorrectTestPaperIndex,this,&CMainMenueDlg::showCorrectTestPaperIndex);


    QObject::connect(this->ui->pushButton_38,&QPushButton::clicked,[=](){
        QString testPaperName = this->ui->lineEdit_6->text().trimmed();
        if(testPaperName != "") //按照模糊查询的结果集进行上一页操作
        {
            this->getCorrectTestPaperLastByName(testPaperName);
        }else
        {
            this->showLastCorrectTestPaper();
        }
    });

    QObject::connect(this->ui->pushButton_42,&QPushButton::clicked,[=](){
        QString testPaperName = this->ui->lineEdit_6->text().trimmed();
        if(testPaperName != "") //按照模糊查询的结果集进行上一页操作
        {
            this->getCorrectTestPaperNextByName(testPaperName);
        }else
        {
            this->showNextCorrectTestPaper();
        }
    });

    QObject::connect(this->ui->pushButton_26,&QPushButton::clicked,[=](){
      this->curPageIndexCorrect = 1;
      QString  testPaperName = this->ui->lineEdit_6->text().trimmed();
      this->getCorrectTestPaperDataByName(testPaperName);
      this->getCorrectTestPaperCountByName(testPaperName);
    });

    QObject::connect(this->ui->pushButton_43,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(4);
    });

    QObject::connect(this,&CMainMenueDlg::startShowCorrectMemberUI,this,&CMainMenueDlg::showCorrectMemberUI);
    QObject::connect(this,&CMainMenueDlg::startShowCorrectMemberCount,this,&CMainMenueDlg::showCorrectMemberCount);


    QObject::connect(this->ui->pushButton_44,&QPushButton::clicked,this,&CMainMenueDlg::showLastCorrectMember);
    QObject::connect(this->ui->pushButton_45,&QPushButton::clicked,this,&CMainMenueDlg::showNextCorrectMember);

    this->initDataBaseTestPaperReleaseTable();
    this->initStudentAnswerSingaleTable();
    this->initStudentAnswerMultiTable();
    this->initStudentAnswerJudgeTable();
    this->initStudentAnswerShortAnswerTable();
    this->initCorrectTestPaperTableUI();
    this->initCorrectTestPaperTableContorl();
    this->initCommitTestPaperTable();   
    this->initCorrectMemberTableUI();
    this->initCorrectMemberTableContorl();
    this->initCorrectShortAnswerTable();
}

void CMainMenueDlg::showLastCorrectMember()
{
    if(this->m_correctMemberCount == "0")
    {
        return;
    }
    //防止恶意刷新
    if(this->m_correctMemberCurIndex <= 1)
    {
        return ;
    }
    //清除当前表中的记录
    this->clearCorrectMemberUI();
    //给当前页递减，并且不能低于1
    if(this->m_correctMemberCurIndex > 1)
    {
       this->m_correctMemberCurIndex -= 1;
    }
    this->getCurPageCorrectMember(this->m_tmpTestPaperName,this->m_classId
                                  ,this->m_testPaperId);

    this->getCorrectMemberCount(this->m_tmpTestPaperName,this->m_classId
                                ,this->m_testPaperId);
}

void CMainMenueDlg::joinCorrectSubjectDlg(QString studentName,QString subject,QString testPaperName,QString studentId)
{
    this->m_correctSubjectDlg = std::make_shared<CCorrectSubjectiveQuestionsDlg>();
    this->m_correctSubjectDlg->move((this->width() - this->m_correctSubjectDlg->width()) / 2
                                    ,(this->height() - this->m_correctSubjectDlg->height()) /2);
    this->m_correctSubjectDlg->testPaperName = testPaperName;
    this->m_correctSubjectDlg->studentName = studentName;
    this->m_correctSubjectDlg->subject = subject;

    this->m_correctSubjectDlg->teacherId = this->m_acount;
    this->m_correctSubjectDlg->studentId = studentId;
    this->m_correctSubjectDlg->classId = this->m_classId;
    this->m_correctSubjectDlg->testPaperId = this->m_testPaperId;

    this->m_correctSubjectDlg->show();
    emit this->m_correctSubjectDlg->startShowDlg();
    this->hide();
    QObject::connect(this->m_correctSubjectDlg.get(),&CCorrectSubjectiveQuestionsDlg::rejected,[=](){
        this->show();
        if(this->m_correctSubjectDlg.get() != nullptr)
        {
            this->m_correctSubjectDlg.reset();
        }
    });
}

void CMainMenueDlg::bindCorrectMemberOperator()
{
    //获取参数等操作
    for(QVector<QWidget*>::iterator pos = this->m_correctMemberOperator.begin(); pos != this->m_correctMemberOperator.end();pos++)
    {
        QList<QPushButton*> ret = (*pos)->findChildren<QPushButton*>();
        for(QPushButton* btn : ret)
        {
            if(btn->text() == "批改")
            {
                //绑定的删除操作的槽函数
                QObject::connect(btn,&QPushButton::clicked,[=](){
                    //进行遍历是哪一个按钮，并获取对应的行号
                    int row = 0;
                    for(int i = 0 ; i < this->m_correctMemberOperator.size();i++)
                    {
                        QList<QPushButton*> buttons = this->m_correctMemberOperator.at(i)->findChildren<QPushButton*>();
                        for(QPushButton* clickedBtn: buttons)
                        {
                            if(clickedBtn == btn)
                            {
                                qDebug()<<"点击进入批改";
                                QString testPaperName = this->m_tmpTestPaperName;
                                QString studentName = this->m_correctMemberName.at(row)->text().trimmed();
                                QString subject = this->m_correctMemberSubject.at(row)->text().trimmed();
                                QString studentId = this->m_correctMemberStudentId.at(row).trimmed();
                                this->joinCorrectSubjectDlg(studentName,subject,testPaperName,studentId);
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

void CMainMenueDlg::showNextCorrectMember()
{
    if(this->m_correctMemberCount == "0") //如果查询的结果集为空则不进行操作
    {
        return;
    }

    if(QString::number(this->m_correctMemberCurIndex) == this->m_correctMemberCount)
    {
        return;
    }
    //清除当前表中的记录
    this->clearCorrectMemberUI();

    //给当前页自增，并且不能超过总页
    if(QString::number(this->m_correctMemberCurIndex) != this->m_correctMemberCount)
    {
        this->m_correctMemberCurIndex += 1;
    }
    this->getCurPageCorrectMember(this->m_tmpTestPaperName,this->m_classId
                                  ,this->m_testPaperId);

    this->getCorrectMemberCount(this->m_tmpTestPaperName,this->m_classId
                                ,this->m_testPaperId);
}

void CMainMenueDlg::clearCorrectMemberUI()
{
    //清除学生姓名
    for(QLabel* lab : this->m_correctMemberName)
    {
        if(lab != nullptr)
        {
            lab->setText("");
        }
    }

    //清除科目
    for(QLabel* lab : this->m_correctMemberSubject)
    {
        if(lab != nullptr)
        {
            lab->setText("");
        }
    }

    //清除客观题
    for(QLabel* lab : this->m_correctMemberKeGuan)
    {
        if(lab != nullptr)
        {
            lab->setText("");
        }
    }

    //清除主观题
    for(QLabel* lab : this->m_correctMemberZhuGuan)
    {
        if(lab != nullptr)
        {
            lab->setText("");
        }
    }

    //清除总分
    for(QLabel* lab : this->m_correctMemberSum)
    {
        if(lab != nullptr)
        {
            lab->setText("");
        }
    }

    //清除操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QPushButton*> optButton = this->m_correctMemberOperator.at(i)->findChildren<QPushButton*>();
        for (QPushButton *button : optButton) {
            button->setVisible(false);
        }
    }
}

void CMainMenueDlg::showCorrectMemberUI(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }

    //进行清除当前表的UI
    this->clearCorrectMemberUI();  
    //进行清除当前表的容器存储数据
    this->m_correctMemberStudentId.clear();

    //进行显示数据
    for(int i = 0 ; i < ret->size(); i++)
    {
        this->m_correctMemberStudentId.push_back(ret->at(i).at(0));

        //显示学生姓名
        QString str = ret->at(i).at(1);
        this->m_correctMemberName.at(i)->setText(str);

        //显示科目
        str = ret->at(i).at(2);
        this->m_correctMemberSubject.at(i)->setText(str);

        //显示客观分数
        str = ret->at(i).at(3);
        int num1 = str.toDouble();
        this->m_correctMemberKeGuan.at(i)->setText(str);

        //显示主观分数
        str = ret->at(i).at(4);
        int num2 = str.toDouble();
        this->m_correctMemberZhuGuan.at(i)->setText(str);

        //显示总分
        double  num3 = num1 + num2;
        str =  QString::number(num3);
        this->m_correctMemberSum.at(i)->setText(str);

        //显示操作按钮
        QList<QPushButton*> optButton = this->m_correctMemberOperator.at(i)->findChildren<QPushButton*>();
        for (QPushButton *button : optButton) {
            button->setVisible(true);
        }
    }
    delete ret;
}

void CMainMenueDlg::showCorrectMemberCount()
{
    QString first = QString::number(this->m_correctMemberCurIndex);
    first += "/";
    first += this->m_correctMemberCount;
    this->ui->label_89->setText(first);
}

typedef struct getCorrectMemberCountArg{
    QString testPaperName;
    QString teacherId;
    int classId;
    int testPaperId;
    CMainMenueDlg* thiz;
}GetCorrectMemberCountArg;

void CMainMenueDlg::getCorrectMemberCount(QString testPaperName,int classId,int testPaperId)
{
    std::shared_ptr<GetCorrectMemberCountArg> arg = std::make_shared<GetCorrectMemberCountArg>();
    arg->testPaperName = testPaperName;
    arg->classId = classId;
    arg->teacherId = this->m_acount;
    arg->testPaperId = testPaperId;
    arg->thiz = this;
    std::shared_ptr<GetCorrectMemberCountArg>* p = new std::shared_ptr<GetCorrectMemberCountArg>(arg);
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetCorrectMemberCount,p,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetCorrectMemberCount(LPVOID arg)
{
   std::shared_ptr<GetCorrectMemberCountArg>* p = (std::shared_ptr<GetCorrectMemberCountArg>*)arg;
   std::shared_ptr<GetCorrectMemberCountArg> gInfo = *p;
   int ret =  gInfo->thiz->m_mainMenueContorller->getCorrectMemberCount(gInfo->testPaperName,gInfo->teacherId
                                                             ,gInfo->classId,gInfo->testPaperId);
   gInfo->thiz->m_correctMemberCount = QString::number(ret);
   //发送新信号
   emit gInfo->thiz->startShowCorrectMemberCount();
   delete p;
   return 0;
}

void CMainMenueDlg::initCorrectMemberTableUI()
{
    this->ui->tableWidget_6->setRowCount(8);
    this->ui->tableWidget_6->setColumnCount(6);
    this->ui->tableWidget_6->horizontalHeader()->hide();
    this->ui->tableWidget_6->verticalHeader()->hide();

    //设置列宽
    int width = this->ui->tableWidget_6->width();
    int heigth = this->ui->tableWidget_6->height();
    this->ui->tableWidget_6->setColumnWidth(0,width / 4);
    this->ui->tableWidget_6->setColumnWidth(1,width / 6);
    this->ui->tableWidget_6->setColumnWidth(2,width / 6);
    this->ui->tableWidget_6->setColumnWidth(3,width / 6);
    this->ui->tableWidget_6->setColumnWidth(4,width / 12);
    this->ui->tableWidget_6->setColumnWidth(5,width / 6);

    this->ui->tableWidget_6->setRowHeight(0,heigth/ 8);
    this->ui->tableWidget_6->setRowHeight(1,heigth/ 8);
    this->ui->tableWidget_6->setRowHeight(2,heigth/ 8);
    this->ui->tableWidget_6->setRowHeight(3,heigth/ 8);
    this->ui->tableWidget_6->setRowHeight(4,heigth/ 8);
    this->ui->tableWidget_6->setRowHeight(5,heigth/ 8);
    this->ui->tableWidget_6->setRowHeight(6,heigth/ 8);
    this->ui->tableWidget_6->setRowHeight(7,heigth/ 8);
}

void CMainMenueDlg::getCorrectTestPaperLastByName(QString testPaperName)
{
    qDebug()<<"执行的是模糊查询结果集上一页！";
    if(this->m_correctTestPaperCount == "0")
    {
        return;
    }
    //防止恶意刷新
    if(this->curPageIndexCorrect<= 1)
    {
        return ;
    }
    //清除当前表中的记录
    this->clearCorrectTestPaperTable();
    //给当前页递减，并且不能低于1
    if(this->curPageIndexCorrect > 1)
    {
       this->curPageIndexCorrect -= 1;
    }
    this->getCorrectTestPaperDataByName(testPaperName);
    this->getCorrectTestPaperCountByName(testPaperName);
}

void CMainMenueDlg::getCorrectTestPaperNextByName(QString testPaperName)
{
    qDebug()<<"执行的是模糊查询结果集下一页！";
    if(this->m_correctTestPaperCount == "0") //如果查询的结果集为空则不进行操作
    {
        return;
    }

    if(QString::number(this->curPageIndexCorrect) == this->m_correctTestPaperCount)
    {
        return;
    }
    //清除当前表中的记录
    this->clearCorrectTestPaperTable();

    //给当前页自增，并且不能超过总页
    if(QString::number(this->curPageIndexCorrect) != this->m_correctTestPaperCount)
    {
        this->curPageIndexCorrect += 1;
    }
    this->getCorrectTestPaperDataByName(testPaperName);
    this->getCorrectTestPaperCountByName(testPaperName);
}

typedef struct getCorrectTestPaperDataByNameArg{
    QString testPaperName;
    QString teacherId;
    CMainMenueDlg* thiz;
    int curIndex;
    getCorrectTestPaperDataByNameArg()=default;
    ~getCorrectTestPaperDataByNameArg()
    {
        qDebug()<<"GetCorrectTestPaperDataByNameArg 被释放！";
    }
}GetCorrectTestPaperDataByNameArg;

void CMainMenueDlg::getCorrectTestPaperDataByName(QString testPaperName)
{
    std::shared_ptr<GetCorrectTestPaperDataByNameArg> arg = std::make_shared<GetCorrectTestPaperDataByNameArg>();
    arg->testPaperName = testPaperName;
    arg->teacherId = this->m_acount;
    arg->curIndex = this->curPageIndexCorrect;
    arg->thiz = this;
    std::shared_ptr<GetCorrectTestPaperDataByNameArg>* p = new std::shared_ptr<GetCorrectTestPaperDataByNameArg>(arg);
    HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadGetCorrectTestPaperDataByName,p,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetCorrectTestPaperDataByName(LPVOID arg)
{
  std::shared_ptr<GetCorrectTestPaperDataByNameArg>* p = (std::shared_ptr<GetCorrectTestPaperDataByNameArg>*)arg;
  std::shared_ptr<GetCorrectTestPaperDataByNameArg> gInfo = *p;
  std::vector<std::vector<std::string>>ret =  gInfo->thiz->m_mainMenueContorller->getCorrectTestPaperDataByName(gInfo->teacherId
                                                                    ,gInfo->testPaperName,gInfo->curIndex);

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
  //发送回显信号
  emit gInfo->thiz->startShowCorrectTestPaper(result);
    delete p;
//  //_endthreadex(0); //建议不要在线程函数中写();
  return 0;
}

void CMainMenueDlg::initCorrectMemberTableContorl()
{
    // 学生名称
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_6->setCellWidget(i,0,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_correctMemberName.push_back(testName);
    }

    //科目
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_6->setCellWidget(i,1,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_correctMemberSubject.push_back(testName);
    }

    //客观题分数
    for(int i = 0 ; i < 8;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_6->setCellWidget(i,2,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_correctMemberKeGuan.push_back(testName);
    }

    //主观题分数
    for(int i = 0 ; i < 8;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_6->setCellWidget(i,3,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_correctMemberZhuGuan.push_back(testName);
    }

    //总分
    for(int i = 0 ; i < 8;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_6->setCellWidget(i,4,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_correctMemberSum.push_back(testName);
    }

    //操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QPushButton* deleteBtn = new QPushButton("批改");
        deleteBtn->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        deleteBtn->setParent(widget);
        deleteBtn->setGeometry(70,20,100,30);
        deleteBtn->setFont(QFont("黑体",12));
        deleteBtn->setVisible(false);
        this->ui->tableWidget_6->setCellWidget(i,5,widget);
        this->m_correctMemberOperator.push_back(widget);
    }

    //进行设置表格样式
    for(int i = 0 ; i < 8 ; i++)
    {
        //同一行的所有控件都进行设置同样的背景颜色
        if(i % 2 == 0)//
        {
            this->m_correctMemberName.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_correctMemberSubject.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_correctMemberKeGuan.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_correctMemberZhuGuan.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_correctMemberSum.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_correctMemberOperator.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
        }else
        {
            this->m_correctMemberName.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_correctMemberSubject.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_correctMemberKeGuan.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_correctMemberZhuGuan.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_correctMemberSum.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_correctMemberOperator.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
        }
    }
    this->bindCorrectMemberOperator();
}

typedef struct getCurPageCorrectMemberArg{
    QString testPaperName;
    QString teacherId;
    int classId;
    int testPaperId;
    int curIndex;
    CMainMenueDlg* thiz;
}GetCurPageCorrectMemberArg;

void CMainMenueDlg::getCurPageCorrectMember(QString testPaperName,int classId,int testPaperId)
{
   std::shared_ptr<GetCurPageCorrectMemberArg> arg = std::make_shared<GetCurPageCorrectMemberArg>();
   //进行给参数赋值
   arg->teacherId = this->m_acount;
   arg->testPaperName = testPaperName;
   arg->classId = classId;
   arg->testPaperId = testPaperId;
   arg->thiz = this;
   arg->curIndex = this->m_correctMemberCurIndex;
   std::shared_ptr<GetCurPageCorrectMemberArg>* p = new std::shared_ptr<GetCurPageCorrectMemberArg>(arg);
   _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetCurPageCorrectMember,p,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetCurPageCorrectMember(LPVOID arg)
{
  std::shared_ptr<GetCurPageCorrectMemberArg>* p = (std::shared_ptr<GetCurPageCorrectMemberArg>*)arg;
  std::shared_ptr<GetCurPageCorrectMemberArg> gInfo = *p;
  //调用控制层
  std::vector<std::vector<std::string>> ret =  gInfo->thiz->m_mainMenueContorller->getCurPageCorrectMember(gInfo->testPaperName
                                                                                                           ,gInfo->teacherId,gInfo->classId
                                                                                                          ,gInfo->testPaperId,gInfo->curIndex);
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
  emit gInfo->thiz->startShowCorrectMemberUI(result);
  delete p;
  return 0;
}


//这里是点击进入批改试卷的逻辑
void CMainMenueDlg::joinCorrectTestPaper(QString testPaperName,QString teacherId,int classId,int testPaperId)
{
    this->m_tmpTestPaperName = testPaperName;
    this->m_classId = classId;
    this->m_testPaperId = testPaperId;

    this->ui->stackedWidget->setCurrentIndex(7);
    this->ui->label_84->setText(testPaperName);
    this->getCurPageCorrectMember(testPaperName,classId,testPaperId);
    this->getCorrectMemberCount(testPaperName,classId,testPaperId);
}

void CMainMenueDlg::initCorrectShortAnswerTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadCorrectShortAnswerTable,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadCorrectShortAnswerTable(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initCorrectShortAnswerTable();
    return 0;
}

void CMainMenueDlg::bindOperatorCorrect()
{
    for(QVector<QWidget*>::iterator pos = this->m_correctOprator.begin(); pos != this->m_correctOprator.end();pos++)
    {
        QList<QPushButton*> ret = (*pos)->findChildren<QPushButton*>();
        for(QPushButton* btn : ret)
        {
            if(btn->text() == "进入批改")
            {
                //绑定的删除操作的槽函数
                QObject::connect(btn,&QPushButton::clicked,[=](){
                    //进行遍历是哪一个按钮，并获取对应的行号
                    int row = 0;
                    for(int i = 0 ; i < this->m_correctOprator.size();i++)
                    {
                        QList<QPushButton*> buttons = this->m_correctOprator.at(i)->findChildren<QPushButton*>();
                        for(QPushButton* clickedBtn: buttons)
                        {
                            if(clickedBtn == btn)
                            {
                                qDebug()<<"点击进入批改";
                                QString testPaperName = this->m_correctTestPaperName.at(i)->text().trimmed();
                                //职工id
                                QString teacherId = this->m_acount;
                                int classId = this->m_correctTestPaperClassIdVec.at(row);
                                int testPaperId = this->m_correctTestPaperTestPaperIdVec.at(row);
                                this->joinCorrectTestPaper(testPaperName,teacherId,classId,testPaperId);
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

typedef struct getCorrectTestPaperCountByNameArg
{
    QString teacherId;
    QString testPaperName;
    CMainMenueDlg* thiz;
}GetCorrectTestPaperCountByNameArg;

void CMainMenueDlg::getCorrectTestPaperCountByName(QString testPaperName)
{
  std::shared_ptr<GetCorrectTestPaperCountByNameArg> arg = std::make_shared<GetCorrectTestPaperCountByNameArg>();
  arg->teacherId = this->m_acount;
  arg->testPaperName = testPaperName;
  arg->thiz = this;
  std::shared_ptr<GetCorrectTestPaperCountByNameArg>* p = new std::shared_ptr<GetCorrectTestPaperCountByNameArg>(arg);
  _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetCorrectTestPaperCountByName,p,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetCorrectTestPaperCountByName(LPVOID arg)
{
   std::shared_ptr<GetCorrectTestPaperCountByNameArg>* p = (std::shared_ptr<GetCorrectTestPaperCountByNameArg>*)arg;
   std::shared_ptr<GetCorrectTestPaperCountByNameArg> gInfo = *p;
   int ret =  gInfo->thiz->m_mainMenueContorller->getCorrectTestPaperCountByName(gInfo->teacherId
                                                                     ,gInfo->testPaperName);
   qDebug()<<"ret: "<<ret;
   gInfo->thiz->m_correctTestPaperCount = QString::number(ret);
   //进行发送信号，进行显示总页数
   emit gInfo->thiz->startShowCorrectTestPaperIndex();
   delete p;
   return 0;
}

void CMainMenueDlg::showLastCorrectTestPaper()
{
    if(this->m_correctTestPaperCount == "0")
    {
        return;
    }
    //防止恶意刷新
    if(this->curPageIndexCorrect<= 1)
    {
        return ;
    }
    //清除当前表中的记录
    this->clearCorrectTestPaperTable();
    //给当前页递减，并且不能低于1
    if(this->curPageIndexCorrect > 1)
    {
       this->curPageIndexCorrect -= 1;
    }
    this->getCurPageIndexCorrect();
    this->getCorrectTestPaperCount();
}

void CMainMenueDlg::showNextCorrectTestPaper()
{
    if(this->m_correctTestPaperCount == "0") //如果查询的结果集为空则不进行操作
    {
        return;
    }

    if(QString::number(this->curPageIndexCorrect) == this->m_correctTestPaperCount)
    {
        return;
    }
    //清除当前表中的记录
    this->clearCorrectTestPaperTable();

    //给当前页自增，并且不能超过总页
    if(QString::number(this->curPageIndexCorrect) != this->m_correctTestPaperCount)
    {
        this->curPageIndexCorrect += 1;
    }
    this->getCurPageIndexCorrect();
    this->getCorrectTestPaperCount();
}

void CMainMenueDlg::showCorrectTestPaperIndex()
{
    QString first = QString::number(this->curPageIndexCorrect);
    first += "/";
    first += this->m_correctTestPaperCount;
    this->ui->label_80->setText(first);
}

typedef struct  getCorrectTestPaperCountArg{
    QString teacherId;
    CMainMenueDlg* thiz;
}GetCorrectTestPaperCountArg;

void CMainMenueDlg::getCorrectTestPaperCount()
{
    std::shared_ptr<GetCorrectTestPaperCountArg> arg = std::make_shared<GetCorrectTestPaperCountArg>();
    arg->teacherId = this->m_acount;
    arg->thiz = this;
    std::shared_ptr<GetCorrectTestPaperCountArg>* p = new std::shared_ptr<GetCorrectTestPaperCountArg>(arg);
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetCorrectTestPaperCount,p,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetCorrectTestPaperCount(LPVOID arg)
{
    std::shared_ptr<GetCorrectTestPaperCountArg>* p = (std::shared_ptr<GetCorrectTestPaperCountArg>*)arg;
    std::shared_ptr<GetCorrectTestPaperCountArg> gInfo = *p;
    int ret =  gInfo->thiz->m_mainMenueContorller->getCorrectTestPaperCount(gInfo->teacherId);
    gInfo->thiz->m_correctTestPaperCount = QString::number(ret);
    //进行发送信号，进行显示总页数
    emit gInfo->thiz->startShowCorrectTestPaperIndex();
    delete p;
//    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::initCommitTestPaperTable()
{
     _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitCommitTestPaperTable,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitCommitTestPaperTable(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initCommitTestPaperTable();
//    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::initCorrectTestPaperTableContorl()
{
    // 试卷名称
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_5->setCellWidget(i,0,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_correctTestPaperName.push_back(testName);
    }

    //待批人数
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_5->setCellWidget(i,1,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_notCorrected.push_back(testName);

    }

    //已批人数
    for(int i = 0 ; i < 8;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_5->setCellWidget(i,2,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_corrected.push_back(testName);
    }

    //操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QPushButton* deleteBtn = new QPushButton("进入批改");
        deleteBtn->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        deleteBtn->setParent(widget);
        deleteBtn->setGeometry(120,20,100,30);
        deleteBtn->setFont(QFont("黑体",12));
        deleteBtn->setVisible(false);
        this->ui->tableWidget_5->setCellWidget(i,3,widget);
        this->m_correctOprator.push_back(widget);
    }

    //进行设置表格样式
    for(int i = 0 ; i < 8 ; i++)
    {
        //同一行的所有控件都进行设置同样的背景颜色
        if(i % 2 == 0)//
        {
            this->m_correctTestPaperName.at(i)->setStyleSheet("QLabel{border:none;background-color:#E1EFD8;border-bottom:1px solid #646465;}");
            this->m_corrected.at(i)->setStyleSheet("QLabel{border:none;background-color:#E1EFD8;border-bottom:1px solid #646465;}");
            this->m_notCorrected.at(i)->setStyleSheet("QLabel{border:none;background-color:#E1EFD8;border-bottom:1px solid #646465;}");
            this->m_correctOprator.at(i)->setStyleSheet("QWidget{border:none;background-color:#E1EFD8;border-bottom:1px solid #646465;}");
        }else
        {
            this->m_correctTestPaperName.at(i)->setStyleSheet("QLabel{border:none;background-color:#FFFFFF;border-bottom:1px solid #646465;}");
            this->m_corrected.at(i)->setStyleSheet("QLabel{border:none;background-color:#FFFFFF;border-bottom:1px solid #646465;}");
            this->m_notCorrected.at(i)->setStyleSheet("QLabel{border:none;background-color:#FFFFFF;border-bottom:1px solid #646465;}");
            this->m_correctOprator.at(i)->setStyleSheet("QWidget{border:none;background-color:#FFFFFF;border-bottom:1px solid #646465;}");
        }
    }
    this->bindOperatorCorrect();
}

void CMainMenueDlg::initCorrectTestPaperTableUI()
{
    this->ui->tableWidget_5->setRowCount(8);
    this->ui->tableWidget_5->setColumnCount(4);
    this->ui->tableWidget_5->horizontalHeader()->hide();
    this->ui->tableWidget_5->verticalHeader()->hide();

    //设置列宽
    int width = this->ui->tableWidget_5->width();
    int heigth = this->ui->tableWidget_5->height();
    this->ui->tableWidget_5->setColumnWidth(0,width / 4);
    this->ui->tableWidget_5->setColumnWidth(1,width / 4);
    this->ui->tableWidget_5->setColumnWidth(2,width / 4);
    this->ui->tableWidget_5->setColumnWidth(3,width / 4);

    this->ui->tableWidget_5->setRowHeight(0,heigth/ 8);
    this->ui->tableWidget_5->setRowHeight(1,heigth/ 8);
    this->ui->tableWidget_5->setRowHeight(2,heigth/ 8);
    this->ui->tableWidget_5->setRowHeight(3,heigth/ 8);
    this->ui->tableWidget_5->setRowHeight(4,heigth/ 8);
    this->ui->tableWidget_5->setRowHeight(5,heigth/ 8);
    this->ui->tableWidget_5->setRowHeight(6,heigth/ 8);
    this->ui->tableWidget_5->setRowHeight(7,heigth/ 8);
}

void CMainMenueDlg::clearCorrectTestPaperTable()
{
    //清除试卷名称
    for(QLabel* lab : this->m_correctTestPaperName)
    {
        if(lab != nullptr)
        {
            lab->setText("");
        }
    }

    //清除待批人数
    for(QLabel* lab : this->m_corrected)
    {
        if(lab != nullptr)
        {
            lab->setText("");
        }
    }

    //清除已批人数
    for(QLabel* lab : this->m_notCorrected)
    {
        if(lab != nullptr)
        {
            lab->setText("");
        }
    }

    //清除操作按钮
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QPushButton*> optButton = this->m_correctOprator.at(i)->findChildren<QPushButton*>();
        for (QPushButton *button : optButton) {
            button->setVisible(false);
        }
    }
}

void CMainMenueDlg::showCorrectTestPaperUI(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    //进行UI显示
    this->clearCorrectTestPaperTable();
    this->m_correctTestPaperClassIdVec.clear(); //清除保证记录的都是当前页的
    this->m_correctTestPaperTestPaperIdVec.clear();//清除保证记录的都是当前页的
   //将数据进行插入到表格中
   for(int i = 0 ; i < ret->size(); i++)
   {
       //显示试卷名称
       QString str = ret->at(i).at(0);
       this->m_correctTestPaperName.at(i)->setText(str);

       //显示待批人数
       str = ret->at(i).at(1);
       this->m_notCorrected.at(i)->setText(str);

       //显示已批人数
       str = ret->at(i).at(2);
       this->m_corrected.at(i)->setText(str);

       //进行存储课程Id
       str = ret->at(i).at(3);
       int num = str.toInt();
       this->m_correctTestPaperClassIdVec.push_back(num);

       //进行存储试卷id
       str = ret->at(i).at(4);
       num = str.toInt();
       this->m_correctTestPaperTestPaperIdVec.push_back(num);

       //显示操作按钮
       QList<QPushButton*> optButton = this->m_correctOprator.at(i)->findChildren<QPushButton*>();
       for (QPushButton *button : optButton) {
           button->setVisible(true);
       }
   }
   if(ret != nullptr)
   {
       delete ret;
   }
}

typedef struct getCurPageIndexCorrectArg{
    QString teacherId;
    CMainMenueDlg* thiz;
    int curIndex;
}GetCurPageIndexCorrectArg;

//TODO:明天接着这里写
void CMainMenueDlg::getCurPageIndexCorrect()
{
  std::shared_ptr<GetCurPageIndexCorrectArg> arg = std::make_shared<GetCurPageIndexCorrectArg>();
  arg->teacherId = this->m_acount; //m_acount就是职工号
  arg->thiz = this;
  arg->curIndex = this->curPageIndexCorrect;
  std::shared_ptr<GetCurPageIndexCorrectArg>* p = new std::shared_ptr<GetCurPageIndexCorrectArg>(arg);
  _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetCurPageIndexCorrect,p,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetCurPageIndexCorrect(LPVOID arg)
{
    std::shared_ptr<GetCurPageIndexCorrectArg>* p = (std::shared_ptr<GetCurPageIndexCorrectArg>*)arg;
    std::shared_ptr<GetCurPageIndexCorrectArg> gInfo = *p;
    std::vector<std::vector<std::string>> ret =  gInfo->thiz->m_mainMenueContorller->getCurPageIndexCorrect(gInfo->teacherId,gInfo->curIndex);
    delete  p;
    //进行处理结果集
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

    //发送回显信号
    emit gInfo->thiz->startShowCorrectTestPaper(result);
//    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::initStudentAnswerSingaleTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitStudentAnswerSingaleTableEntry,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitStudentAnswerSingaleTableEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initStudentAnswerSingaleTable();
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::initDataBaseTestPaperReleaseTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitDataBaseTestPaperReleaseTable,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitDataBaseTestPaperReleaseTable(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initDataBaseTestPaperReleaseTable();
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::showStudentManegerTableLastPageByStudentName(QString studentName)
{
    if(this->m_studentManegerCount == "0")
    {
        return;
    }
    //防止恶意刷新
    if(this->m_studentManegerCurPageIndex <= 1)
    {
        return ;
    }
    //清除当前表中的记录
    this->clearStudentManegerTableUI();
    //给当前页递减，并且不能低于1
    if(this->m_studentManegerCurPageIndex > 1)
    {
       this->m_studentManegerCurPageIndex -= 1;
    }
    emit this->ui->checkBox_10->toggled(false);
    this->ui->checkBox_10->setChecked(false);

    this->getStudentManegerCurPageDataByStudentName(studentName);
    this->getStudentManegerTableCountByStudentName(studentName);
}

void  CMainMenueDlg::showStudentManegerTableNextPageByStudentName(QString studentName)
{
    if(this->m_studentManegerCount == "0") //如果查询的结果集为空则不进行操作
    {
        return;
    }

    if(QString::number(this->m_studentManegerCurPageIndex) == this->m_studentManegerCount)
    {
        return;
    }
    //清除当前表中的记录
    this->clearStudentManegerTableUI();

    //给当前页自增，并且不能超过总页
    if(QString::number(this->m_studentManegerCurPageIndex) != this->m_studentManegerCount)
    {
        this->m_studentManegerCurPageIndex += 1;
    }

    //清除选中项
    emit this->ui->checkBox_10->toggled(false);
    this->ui->checkBox_10->setChecked(false);

    this->getStudentManegerCurPageDataByStudentName(studentName);
    this->getStudentManegerTableCountByStudentName(studentName);
}

typedef struct getStudentManegerTableCountByStudentNameArg{
    CMainMenueDlg* thiz;
    QString acount;
    QString className;
    QString studentName;
}GetStudentManegerTableCountByStudentNameArg;

void CMainMenueDlg::getStudentManegerTableCountByStudentName(QString studentName)
{
    GetStudentManegerTableCountByStudentNameArg* arg = new GetStudentManegerTableCountByStudentNameArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->studentName  = studentName;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentManegerTableCountByStudentNameEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentManegerTableCountByStudentNameEntry(LPVOID arg)
{
    GetStudentManegerTableCountByStudentNameArg* gInfo = (GetStudentManegerTableCountByStudentNameArg*)arg;
    int ret =  gInfo->thiz->m_mainMenueContorller->getStudentManegerTableCountByStudentName(gInfo->acount
                                                                                            ,gInfo->className
                                                                                            ,gInfo->studentName);

    gInfo->thiz->m_studentManegerCount = QString::number(ret);
    //进行发送信号，进行显示总页数
    emit gInfo->thiz->startShowStudentManegerTableIndex();
    delete gInfo;
    //_endthreadex(0);
    return 0;
}

typedef struct getStudentManegerCurPageDataByStudentNameArg{
    QString acount;
    QString className;
    CMainMenueDlg* thiz;
    int curIndex;
    QString studentName;
}GetStudentManegerCurPageDataByStudentNameArg;

void CMainMenueDlg::getStudentManegerCurPageDataByStudentName(QString studentName)
{
    //TODO:明天接着这里继续
    GetStudentManegerCurPageDataByStudentNameArg* arg = new GetStudentManegerCurPageDataByStudentNameArg();
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->thiz = this;
    arg->curIndex = this->m_studentManegerCurPageIndex;
    arg->studentName = studentName;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentManegerCurPageDataByStudentName,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentManegerCurPageDataByStudentName(LPVOID arg)
{
    GetStudentManegerCurPageDataByStudentNameArg* gInfo = ( GetStudentManegerCurPageDataByStudentNameArg*)arg;
    std::vector<std::vector<std::string>> ret =  gInfo->thiz->m_mainMenueContorller->getStudentManegerCurPageDataByStudentName(gInfo->acount
                                                                                                                               ,gInfo->className
                                                                                                                               ,gInfo->studentName
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
    //发送数据回显信号
    emit gInfo->thiz->startShowStudentManegerCurPagaUI(result);
    //_endthreadex(0);
    return 0;
}

typedef struct deleteMultiManegerByStudentIdArg{
    QString acount;
    QString className;
    QList<QString>* studentIdLst;
    CMainMenueDlg* thiz;
}DeleteMultiManegerByStudentIdArg;

void CMainMenueDlg::deleteMultiManegerByStudentId()
{
    this->m_studentManegerCurPageIndex = 1;
    DeleteMultiManegerByStudentIdArg* arg = new DeleteMultiManegerByStudentIdArg();
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->studentIdLst = new QList<QString>();
    arg->thiz = this;
    //将选中的记录的学生学号进行存储
    for(int i = 0 ; i < this->m_studentManegerCheckVec.size();i++)
    {
        QList<QCheckBox*> checkLst = this->m_studentManegerCheckVec.at(i)->findChildren<QCheckBox*>();
        for(QCheckBox* check : checkLst)
        {
            if(check->isChecked())
            {
                //获取到同一行的学号
                QString studentId = this->m_studentManagerStudentIdVec.at(i)->text().trimmed();
                arg->studentIdLst->push_back(studentId);
            }
        }
    }
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteMultiManegerByStudentId,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadDeleteMultiManegerByStudentId(LPVOID arg)
{
    //TODO:接着继续
    DeleteMultiManegerByStudentIdArg* aInfo = (DeleteMultiManegerByStudentIdArg*)arg;
    aInfo->thiz->m_mainMenueContorller->deleteMultiManegerByStudentId(aInfo->acount
                                                                     ,aInfo->className
                                                                     ,aInfo->studentIdLst);
    //进行回显数据  回显的是全部的数据
    aInfo->thiz->getStudentManegerCurPageData();
    aInfo->thiz->getStudentMenberCountData();
    aInfo->thiz->getStudentManegerTableCount();
    emit aInfo->thiz->ui->checkBox_10->toggled(false);
    aInfo->thiz->ui->checkBox_10->setChecked(false);
    delete aInfo->studentIdLst;
    delete aInfo;
    //_endthreadex(0);
    return 0;
}

typedef  struct deleteStudentManegerByStudentIdArg{
    QString studentId;
    QString acount;
    QString className;
    CMainMenueDlg* thiz;
}DeleteStudentManegerByStudentIdArg;

void CMainMenueDlg::deleteStudentManegerByStudentId(QString studentId)
{
    DeleteStudentManegerByStudentIdArg* arg = new DeleteStudentManegerByStudentIdArg();
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->studentId = studentId;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteStudentManegerByStudentId,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadDeleteStudentManegerByStudentId(LPVOID arg)
{
    DeleteStudentManegerByStudentIdArg* dInfo = (DeleteStudentManegerByStudentIdArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteStudentManegerByStudentId(dInfo->acount
                                                                        ,dInfo->className
                                                                        ,dInfo->studentId);
    //重新回显数据 进行单条操作或者批量操作后都要将当前页下标进行重置为1

    //如果有文本则显示学生姓名查询的否则显示全部
    QString studentName = dInfo->thiz->ui->lineEdit_12->text().trimmed();
    if(studentName == "")
    {
        dInfo->thiz->getStudentManegerCurPageData();
        dInfo->thiz->getStudentManegerTableCount();
        dInfo->thiz->getStudentMenberCountData();
    }else
    {
        dInfo->thiz->getStudentManegerCurPageDataByStudentName(studentName);
        dInfo->thiz->getStudentManegerTableCountByStudentName(studentName);
        dInfo->thiz->getStudentMenberCountData();
    }
    delete dInfo;
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::bindStudentManegerOperators()
{
    for(QVector<QWidget*>::iterator pos = this->m_studentManegerOperators.begin(); pos != this->m_studentManegerOperators.end();pos++)
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
                    for(int i = 0 ; i < this->m_studentManegerOperators.size();i++)
                    {
                        QList<QPushButton*> buttons = this->m_studentManegerOperators.at(i)->findChildren<QPushButton*>();
                        for(QPushButton* clickedBtn: buttons)
                        {
                            if(clickedBtn == btn)
                            {
                                QString studentId = this->m_studentManagerStudentIdVec.at(row)->text().trimmed();
                                this->m_studentManegerCurPageIndex = 1;
                                this->deleteStudentManegerByStudentId(studentId);
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

void CMainMenueDlg::changeStudentManegerCurPageCheckBoxStatus(bool status)
{
    for(int i = 0 ; i < this->m_studentManegerCheckVec.size();i++)
    {
       QList<QCheckBox*> ret =  this->m_studentManegerCheckVec.at(i)->findChildren<QCheckBox*>();
       for(QCheckBox* check : ret)
       {
          check->setChecked(status);
       }
    }
}

void  CMainMenueDlg::showStudentManegerTableLastPage()
{
    if(this->m_studentManegerCount == "0")
    {
        return;
    }
    //防止恶意刷新
    if(this->m_studentManegerCurPageIndex <= 1)
    {
        return ;
    }
    //清除当前表中的记录
    this->clearStudentManegerTableUI();
    //给当前页递减，并且不能低于1
    if(this->m_studentManegerCurPageIndex > 1)
    {
       this->m_studentManegerCurPageIndex -= 1;
    }
    emit this->ui->checkBox_10->toggled(false);
    this->ui->checkBox_10->setChecked(false);

    this->getStudentManegerCurPageData();
    this->getStudentManegerTableCount();
}

void  CMainMenueDlg::showStudentManegerTableNextPage()
{
    if(this->m_studentManegerCount == "0") //如果查询的结果集为空则不进行操作
    {
        return;
    }

    if(QString::number(this->m_studentManegerCurPageIndex) == this->m_studentManegerCount)
    {
        return;
    }
    //清除当前表中的记录
    this->clearStudentManegerTableUI();

    //给当前页自增，并且不能超过总页
    if(QString::number(this->m_studentManegerCurPageIndex) != this->m_studentManegerCount)
    {
        this->m_studentManegerCurPageIndex += 1;
    }

    //清除选中项
    emit this->ui->checkBox_10->toggled(false);
    this->ui->checkBox_10->setChecked(false);

    this->getStudentManegerCurPageData();
    this->getStudentManegerTableCount();
//    emit this->startGetClassTableInfo();
//    emit this->startGetClassTableIndex();
}

void CMainMenueDlg::showStudentManegerTableIndex()
{
    QString first = QString::number(this->m_studentManegerCurPageIndex);
    first += "/";
    first += this->m_studentManegerCount;
    this->ui->label_74->setText(first);
}

typedef struct getStudentManegerTableCountArg{
    QString acount;
    QString className;
    CMainMenueDlg* thiz;
}GetStudentManegerTableCountArg;

void CMainMenueDlg::getStudentManegerTableCount()
{
     GetStudentManegerTableCountArg* arg = new GetStudentManegerTableCountArg();
     arg->thiz = this;
     arg->acount = this->m_acount;
     arg->className = this->m_classInfoSelected;
     _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentManegerTableCountEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentManegerTableCountEntry(LPVOID arg)
{
    GetStudentManegerTableCountArg* gInfo = (GetStudentManegerTableCountArg*)arg;
    int ret =  gInfo->thiz->m_mainMenueContorller->getStudentManegerTableCount(gInfo->acount,gInfo->className);
    gInfo->thiz->m_studentManegerCount = QString::number(ret);
    //进行发送信号，进行显示总页数
    emit gInfo->thiz->startShowStudentManegerTableIndex();
    delete gInfo;
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::clearStudentManegerTableUI()
{
    //隐藏序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QCheckBox*> buttons = this->m_studentManegerCheckVec.at(i)->findChildren<QCheckBox*>();
        for (QCheckBox *button : buttons) {
            button->setVisible(false);
        }
    }

    //清除学生头像
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QLabel*> buttons = this->m_studentManegerHeadIconVec.at(i)->findChildren<QLabel*>();
        for (QLabel *button : buttons) {
            button->setPixmap(QPixmap());
        }
    }

    //清除学生姓名
    for (QLabel *button : this->m_studentManagerStudentNameVec) {
        button->setText("");
    }

    //清除学生学号
    for (QLabel *button : this->m_studentManagerStudentIdVec) {
        button->setText("");
    }

    //清除学生电话
    for (QLabel *button : this->m_studentManegerPhoneNumberVec) {
        button->setText("");
    }

    //清除加入时间
    for (QLabel *button : this->m_studentManegerJoinTimeVec) {
        button->setText("");
    }

    //清除操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QPushButton*> optButton = this->m_studentManegerOperators.at(i)->findChildren<QPushButton*>();
        for (QPushButton *button : optButton) {
            button->setVisible(false);
        }
    }
}

unsigned WINAPI  CMainMenueDlg::showStudentHeadIcon(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    //进行接收图片并且显示到UI上
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
    WaitForSingleObject(thiz->m_studentManegerEvent,INFINITE);
    strcpy(data,thiz->m_studentManegerHeadIconPath.c_str());
    ResetEvent(thiz->m_studentManegerEvent);
    SetEvent(thiz->m_studentManegerEvent_2);
    ResetEvent(thiz->m_studentManegerEvent_2);
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
    emit  thiz->startShowStudentHeadIconUI(image);
    delete[] recvBuffer;
    //_endthreadex(0);
    return 0;
}


void CMainMenueDlg::showStudentManegerCurPagaUI(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    this->m_studentManegerClassIconIndex = 0;
    //进行UI显示
    this->clearStudentManegerTableUI();
   //将数据进行插入到表格中
   for(int i = 0 ; i < ret->size(); i++)
   {
       //显示序号
       QList<QCheckBox*> buttons = this->m_studentManegerCheckVec.at(i)->findChildren<QCheckBox*>();
       for (QCheckBox *button : buttons) {
           button->setVisible(true);
       }

       //显示学生头像
       QByteArray arr =  ret->at(i).at(0).toLocal8Bit();
       this->m_studentManegerHeadIconPath = arr.data();
       SetEvent(this->m_studentManegerEvent);
       HANDLE thread =  (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::showStudentHeadIcon,this,0,nullptr);

       WaitForSingleObject(this->m_studentManegerEvent_2,INFINITE);

       //显示学生姓名
       QString str = ret->at(i).at(1);
       this->m_studentManagerStudentNameVec .at(i)->setText(str);

       //显示学生学号
       str = ret->at(i).at(2);
       this->m_studentManagerStudentIdVec.at(i)->setText(str);

       //显示学生电话
       str = ret->at(i).at(3);
       this->m_studentManegerPhoneNumberVec.at(i)->setText(str);

       //显示加入时间
       str = ret->at(i).at(4);
       this->m_studentManegerJoinTimeVec.at(i)->setText(str);

       //显示操作按钮
       QList<QPushButton*> optButton = this->m_studentManegerOperators.at(i)->findChildren<QPushButton*>();
       for (QPushButton *button : optButton) {
           button->setVisible(true);
       }
   }
   if(ret != nullptr)
   {
       delete ret;
   }
   qDebug()<<"学生管理UI显示完成!";
}

typedef  struct getStudentManegerCurPageDataArg{
    CMainMenueDlg* thiz;
    QString acount;
    QString className;
    int curIndex;
}GetStudentManegerCurPageDataArg;

void CMainMenueDlg::getStudentManegerCurPageData()
{    
    GetStudentManegerCurPageDataArg* arg = new GetStudentManegerCurPageDataArg();
//    std::shared_ptr<GetStudentManegerCurPageDataArg> arg = std::make_shared<GetStudentManegerCurPageDataArg>();
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->thiz = this;
    arg->curIndex = this->m_studentManegerCurPageIndex;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentManegerCurPageData,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentManegerCurPageData(LPVOID arg)
{
    GetStudentManegerCurPageDataArg* gInfo = (GetStudentManegerCurPageDataArg*)arg;
//    std::shared_ptr<GetStudentManegerCurPageDataArg> gInfo = *(std::shared_ptr<GetStudentManegerCurPageDataArg>*)arg;
    std::vector<std::vector<std::string>> ret =  gInfo->thiz->m_mainMenueContorller->getStudentManegerCurPageData(gInfo->acount
                                                                                                                  ,gInfo->className
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
    //发送数据回显信号
    emit gInfo->thiz->startShowStudentManegerCurPagaUI(result);
    //emit gInfo->thiz->startShowStudentRequestTableUI(result);
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::initStudentManegerTableContorl()
{
    //初始化序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout();
        widget->setLayout(layout);
        QCheckBox* checkBox = new QCheckBox();
        checkBox->setText(QString::number(++this->m_sortNumStudentManeger));
        checkBox->setFont(QFont("黑体"));
        checkBox->setStyleSheet("QCheckBox{border:none;margin-left:20px;}");
        checkBox->setVisible(false);
        layout->addWidget(checkBox);
        checkBox->setParent(widget);
        this->ui->tableWidget_4->setCellWidget(i,0,widget);
        this->m_studentManegerCheckVec.push_back(widget);
    }

    //学生头像
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QLabel* testName = new QLabel(widget);
        testName->setStyleSheet("QLabel{border:none;}");
        testName->setGeometry(0,0,136,136);
//        testName->setPixmap(QPixmap(":/icons/acount.png"));
        testName->setScaledContents(true);
        this->ui->tableWidget_4->setCellWidget(i,1,widget);
        this->m_studentManegerHeadIconVec.push_back(widget);
    }

    // 学生姓名
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_4->setCellWidget(i,2,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentManagerStudentNameVec .push_back(testName);
    }

    // 学生学号
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_4->setCellWidget(i,3,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentManagerStudentIdVec.push_back(testName);
    }

    //学生电话
    for(int i = 0 ; i < 8;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_4->setCellWidget(i,4,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentManegerPhoneNumberVec.push_back(testName);
    }

    //加入时间
    for(int i = 0 ; i < 8;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_4->setCellWidget(i,5,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentManegerJoinTimeVec.push_back(testName);
    }

    //操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QPushButton* deleteBtn = new QPushButton("删除");
        deleteBtn->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        deleteBtn->setParent(widget);
        deleteBtn->setGeometry(40,50,70,30);
        deleteBtn->setFont(QFont("黑体",12));
        deleteBtn->setVisible(false);
        this->ui->tableWidget_4->setCellWidget(i,6,widget);
        this->m_studentManegerOperators.push_back(widget);
    }

    //进行设置表格样式
    for(int i = 0 ; i < 8 ; i++)
    {
        if(i % 2 == 0)
        {
            this->m_studentManegerCheckVec.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
            this->m_studentManegerHeadIconVec.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
            this->m_studentManagerStudentNameVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_studentManagerStudentIdVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_studentManegerPhoneNumberVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_studentManegerJoinTimeVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_studentManegerOperators.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
        }else
        {
            this->m_studentManegerCheckVec.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
            this->m_studentManegerHeadIconVec.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
            this->m_studentManagerStudentNameVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_studentManagerStudentIdVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_studentManegerPhoneNumberVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_studentManegerJoinTimeVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_studentManegerOperators.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
        }
    }
}

void CMainMenueDlg::initStudentManegerTable()
{
    this->ui->tableWidget_4->setRowCount(8);
    this->ui->tableWidget_4->setColumnCount(7);
    this->ui->tableWidget_4->horizontalHeader()->hide();
    this->ui->tableWidget_4->verticalHeader()->hide();

    //设置列宽
    int width = this->ui->tableWidget_4->width();
    int heigth = this->ui->tableWidget_4->height();
    this->ui->tableWidget_4->setColumnWidth(0,width / 18);
    this->ui->tableWidget_4->setColumnWidth(1,width / 10);
    this->ui->tableWidget_4->setColumnWidth(2,width / 7);
    this->ui->tableWidget_4->setColumnWidth(3,width / 5.5);
    this->ui->tableWidget_4->setColumnWidth(4,width / 5.5);
    this->ui->tableWidget_4->setColumnWidth(5,width / 4.5);
    this->ui->tableWidget_4->setColumnWidth(6,width / 10);

    this->ui->tableWidget_4->setRowHeight(0,width / 10);
    this->ui->tableWidget_4->setRowHeight(1,width / 10);
    this->ui->tableWidget_4->setRowHeight(2,width / 10);
    this->ui->tableWidget_4->setRowHeight(3,width / 10);
    this->ui->tableWidget_4->setRowHeight(4,width / 10);
    this->ui->tableWidget_4->setRowHeight(5,width / 10);
    this->ui->tableWidget_4->setRowHeight(6,width / 10);
    this->ui->tableWidget_4->setRowHeight(7,width / 10);
}

typedef struct getStudentMenberCountDataArg
{
 CMainMenueDlg* thiz;
 QString acount;
 QString className;
}GetStudentMenberCountDataArg;

void CMainMenueDlg::getStudentMenberCountData()
{
    GetStudentMenberCountDataArg* arg = new GetStudentMenberCountDataArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentMenberCountData,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentMenberCountData(LPVOID arg)
{
    GetStudentMenberCountDataArg* gInfo = (GetStudentMenberCountDataArg*)arg;
    int ret =   gInfo->thiz->m_mainMenueContorller->getStudentMenberCountData(gInfo->acount,gInfo->className);
    QString strResult = QString::number(ret);
    strResult += "人";
    gInfo->thiz->ui->label_78->setText(strResult);
    delete gInfo;
    //_endthreadex(0);
    return 0;
}

typedef struct showClassIconInStudentManegerArg
{
    CMainMenueDlg* thiz;
    QString acount;
    QString className;
}ShowClassIconInStudentManegerArg;

void CMainMenueDlg::showClassIconInStudentManeger()
{
    ShowClassIconInStudentManegerArg* arg = new ShowClassIconInStudentManegerArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadShowClassIconInStudentManeger,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadShowClassIconInStudentManeger(LPVOID arg)
{
    ShowClassIconInStudentManegerArg* sInfo = (ShowClassIconInStudentManegerArg*)arg;
    //访问数据库，拿到图片路径
    std::vector<std::vector<std::string>> ret =  sInfo->thiz->m_mainMenueContorller->showClassIconInStudentManeger(sInfo->acount,sInfo->className);

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
    emit  sInfo->thiz->startShowClassIconInStudentManagerUI(image);
//    delete[] pixmapData;
    delete[] recvBuffer;

    delete sInfo;
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::initStudentInfoManagerData(int index)
{
    if(index == 1)
    {
       this->showClassIconInStudentManeger();
       this->ui->label_68->setText(this->m_classInfoSelected);
       this->getStudentMenberCountData();
       this->getStudentManegerCurPageData();
       this->getStudentManegerTableCount();
    }
}

typedef struct degreeMultiRequestByStudentIdArg
{
    CMainMenueDlg* thiz;
    QString acount;
    QString className;
    QList<QString>* studentIdLst;
}DegreeMultiRequestByStudentIdArg;

void CMainMenueDlg::degreeMultiRequestByStudentId()
{
    this->m_curStudentRequestIndex = 1;
    DegreeMultiRequestByStudentIdArg* arg = new DegreeMultiRequestByStudentIdArg();
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->studentIdLst = new QList<QString>();
    arg->thiz = this;
    //将选中的记录的学生学号进行存储
    for(int i = 0 ; i < this->m_studentRequestCheckVec.size();i++)
    {
        QList<QCheckBox*> checkLst = this->m_studentRequestCheckVec.at(i)->findChildren<QCheckBox*>();
        for(QCheckBox* check : checkLst)
        {
            if(check->isChecked())
            {
                //获取到同一行的学号
                QString studentId = this->m_studentRequestStudentIdVec.at(i)->text().trimmed();
                arg->studentIdLst->push_back(studentId);
            }
        }
    }
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDegreeMultiRequestByStudentId,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadDegreeMultiRequestByStudentId(LPVOID arg)
{
    DegreeMultiRequestByStudentIdArg* aInfo = (DegreeMultiRequestByStudentIdArg*)arg;
    aInfo->thiz->m_mainMenueContorller->degreeMultiRequestByStudentId(aInfo->acount
                                                                     ,aInfo->className
                                                                     ,aInfo->studentIdLst);
    //进行回显数据  回显的是全部的数据
    aInfo->thiz->getStudentRequestTableData();
    aInfo->thiz->getStudentRequestTableCount();
    delete aInfo->studentIdLst;
    delete aInfo;
    emit aInfo->thiz->ui->checkBox_9->toggled(false);
    aInfo->thiz->ui->checkBox_9->setChecked(false);
    //_endthreadex(0);
    return 0;
}

typedef struct agreeMultiRequestByStudentIdArg
{
    CMainMenueDlg* thiz;
    QString acount;
    QString className;
    QList<QString>* studentIdLst;
}AgreeMultiRequestByStudentIdArg;

void CMainMenueDlg::agreeMultiRequestByStudentId()
{
    this->m_curStudentRequestIndex = 1;
    AgreeMultiRequestByStudentIdArg* arg = new AgreeMultiRequestByStudentIdArg();
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->studentIdLst = new QList<QString>();
    arg->thiz = this;
    //将选中的记录的学生学号进行存储
    for(int i = 0 ; i < this->m_studentRequestCheckVec.size();i++)
    {
        QList<QCheckBox*> checkLst = this->m_studentRequestCheckVec.at(i)->findChildren<QCheckBox*>();
        for(QCheckBox* check : checkLst)
        {
            if(check->isChecked())
            {
                //获取到同一行的学号
                QString studentId = this->m_studentRequestStudentIdVec.at(i)->text().trimmed();
                arg->studentIdLst->push_back(studentId);
            }
        }
    }
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadAgreeMultiRequestByStudentId,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadAgreeMultiRequestByStudentId(LPVOID arg)
{
    AgreeMultiRequestByStudentIdArg* aInfo = (AgreeMultiRequestByStudentIdArg*)arg;
    aInfo->thiz->m_mainMenueContorller->agreeMultiRequestByStudentId(aInfo->acount
                                                                     ,aInfo->className
                                                                     ,aInfo->studentIdLst);
    //进行回显数据  回显的是全部的数据
    aInfo->thiz->getStudentRequestTableData();
    aInfo->thiz->getStudentRequestTableCount();
    delete aInfo->studentIdLst;
    delete aInfo;
    emit aInfo->thiz->ui->checkBox_9->toggled(false);
    aInfo->thiz->ui->checkBox_9->setChecked(false);
    //_endthreadex(0);
    return 0;
}

typedef struct degreeStudentRequestByStudentIdArg
{
    CMainMenueDlg* thiz;
    QString className;
    QString acount;
    QString studentId;
}DegreeStudentRequestByStudentIdArg;

void CMainMenueDlg::degreeStudentRequestByStudentId(int row)
{
    QString studentId = this->m_studentRequestStudentIdVec.at(row)->text().trimmed();
    DegreeStudentRequestByStudentIdArg* arg = new DegreeStudentRequestByStudentIdArg();
    arg->acount = this->m_acount;
    arg->studentId = studentId;
    arg->className = this->m_classInfoSelected;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDegreeStudentRequestByStudentId,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadDegreeStudentRequestByStudentId(LPVOID arg)
{
    DegreeStudentRequestByStudentIdArg* dInfo = (DegreeStudentRequestByStudentIdArg*)arg;
    dInfo->thiz->m_mainMenueContorller->degreeStudentRequestByStudentId(dInfo->acount
                                                                        ,dInfo->className
                                                                        ,dInfo->studentId);
    //进行回显数据
    dInfo->thiz->getStudentRequestTableData();
    dInfo->thiz->getStudentRequestTableCount();
    delete dInfo;
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::initJoinClassStudentManeageTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitJoinClassStudentManeageTable,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitJoinClassStudentManeageTable(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initJoinClassStudentManeageTable();
    //_endthreadex(0);
    return 0;
}


typedef struct agreeStudentRequestByStudentIdArg
{
    CMainMenueDlg* thiz;
    QString acount;
    QString className;
    QString studentId;
}AgreeStudentRequestByStudentIdArg;

void CMainMenueDlg::agreeStudentRequestByStudentId(int row)
{
    QString studentId = this->m_studentRequestStudentIdVec.at(row)->text().trimmed();

    AgreeStudentRequestByStudentIdArg* arg = new AgreeStudentRequestByStudentIdArg();
    arg->thiz = this;
    arg->acount  = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->studentId = studentId;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadAgreeStudentRequestByStudentId,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadAgreeStudentRequestByStudentId(LPVOID arg)
{
   AgreeStudentRequestByStudentIdArg* aInfo = (AgreeStudentRequestByStudentIdArg*)arg;
   aInfo->thiz->m_mainMenueContorller->agreeStudentRequestByStudentId(aInfo->acount
                                                                      ,aInfo->className
                                                                      ,aInfo->studentId);
   //进行回显数据
   aInfo->thiz->getStudentRequestTableData();
   aInfo->thiz->getStudentRequestTableCount();
   delete aInfo;
   //_endthreadex(0);
   return 0;
}

void CMainMenueDlg::bindStudentRequestOperators()
{
    for(QVector<QWidget*>::iterator pos = this->m_studentRequestOpetators.begin(); pos != this->m_studentRequestOpetators.end();pos++)
    {
         QList<QPushButton*> ret = (*pos)->findChildren<QPushButton*>();
         for(QPushButton* btn : ret)
         {
             if(btn->text() == "同意")
             {
                 //绑定的同意操作的槽函数
                 QObject::connect(btn,&QPushButton::clicked,[=](){
                     //进行遍历是哪一个按钮，并获取对应的行号
                     int row = 0;
                     for(int i = 0 ; i < this->m_studentRequestOpetators.size();i++)
                     {
                         QList<QPushButton*> buttons = this->m_studentRequestOpetators.at(i)->findChildren<QPushButton*>();
                         for(QPushButton* clickedBtn: buttons)
                         {
                             if(clickedBtn == btn)
                             {
                                 this->m_curStudentRequestIndex = 1;
                                 this->agreeStudentRequestByStudentId(row);
                                 break;
                             }
                         }
                         row++;
                     }
                 });

             }else if(btn->text() == "不同意")
             {
                 //绑定的发布操作的槽函数
                 QObject::connect(btn,&QPushButton::clicked,[=](){
                     int row = 0;
                     for(int i = 0 ; i < this->m_studentRequestOpetators.size();i++)
                     {
                         QList<QPushButton*> buttons = this->m_studentRequestOpetators.at(i)->findChildren<QPushButton*>();
                         for(QPushButton* clickedBtn: buttons)
                         {
                             if(clickedBtn == btn)
                             {
                                 this->m_curStudentRequestIndex = 1;
                                 this->degreeStudentRequestByStudentId(row);
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

void CMainMenueDlg::changeStudentRequestCurPageCheckBoxStatus(bool status)
{
    for(int i = 0 ; i < this->m_studentRequestCheckVec.size();i++)
    {
       QList<QCheckBox*> ret =  this->m_studentRequestCheckVec.at(i)->findChildren<QCheckBox*>();
       for(QCheckBox* check : ret)
       {
          check->setChecked(status);
       }
    }
}

void CMainMenueDlg::showStudentRequestByRequestTimeNextPage(QString createTime)
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
    this->getStudentRequestByRequestTime(createTime);
    this->getStudentRequestByRequestTimeCount(createTime);
}

void CMainMenueDlg::showStudentRequestByRequestTimeLastPage(QString createTime)
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
    this->getStudentRequestByRequestTime(createTime);
    this->getStudentRequestByRequestTimeCount(createTime);
}

typedef struct getStudentRequestByRequestTimeCountArg
{
   CMainMenueDlg* thiz;
   QString acount;
   QString className;
   QString requestTime;
}GetStudentRequestByRequestTimeCountArg;

void CMainMenueDlg::getStudentRequestByRequestTimeCount(QString createTime)
{
    GetStudentRequestByRequestTimeCountArg* arg = new GetStudentRequestByRequestTimeCountArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->className = this->m_classInfoSelected;
    arg->requestTime = createTime;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentRequestByRequestTimeCount,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentRequestByRequestTimeCount(LPVOID arg)
{
   GetStudentRequestByRequestTimeCountArg* gInfo = (GetStudentRequestByRequestTimeCountArg*)arg;
   int ret =  gInfo->thiz->m_mainMenueContorller->getStudentRequestByRequestTimeCount(gInfo->acount
                                                                           ,gInfo->className
                                                                           ,gInfo->requestTime);
   gInfo->thiz->m_studentRequestCount = QString::number(ret);
   emit gInfo->thiz->startShowStudentRequestIndexUI();
   delete gInfo;
   //_endthreadex(0);
   return 0;
}

typedef struct getStudentRequestByRequestTimeArg
{
    CMainMenueDlg* thiz;
    QString className;
    QString acount;
    QString requestTime;
    int curIndex;
}GetStudentRequestByRequestTimeArg;

void  CMainMenueDlg::getStudentRequestByRequestTime(QString createTime)
{
    GetStudentRequestByRequestTimeArg* arg = new GetStudentRequestByRequestTimeArg();
    arg->thiz = this;
    arg->requestTime = createTime;
    arg->className =  this->m_classInfoSelected;
    arg->curIndex = this->m_curStudentRequestIndex;
    arg->acount = this->m_acount;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentRequestByRequestTime,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentRequestByRequestTime(LPVOID arg)
{
    GetStudentRequestByRequestTimeArg* gInfo =(GetStudentRequestByRequestTimeArg*)arg;
    std::vector<std::vector<std::string>> ret =  gInfo->thiz->m_mainMenueContorller->
            getStudentRequestByRequestTime(gInfo->acount
                                           ,gInfo->className,
                                           gInfo->curIndex
                                           ,gInfo->requestTime);
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
    //_endthreadex(0);
    return 0;
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
        //_endthreadex(0);
        return 0;
    }else if(strCondition != "" && value == 0) //按学生姓名
    {
        gInfo->thiz->getStudentRequestByStudentName(strCondition);
        gInfo->thiz->getStudentRequestByStudentNameCount(strCondition);
        delete gInfo;
        //_endthreadex(0);
        return 0;
    }else if(strCondition != "" && value == 1)//按学生学号
    {
        gInfo->thiz->getStudentRequestByStudentId(strCondition);
        gInfo->thiz->getStudentRequestByStudentIdCount(strCondition);
        delete gInfo;
        //_endthreadex(0);
        return 0;
    }else if(strCondition != "" && value == 2)//按申请时间
    {
        gInfo->thiz->getStudentRequestByRequestTime(strCondition);
        gInfo->thiz->getStudentRequestByRequestTimeCount(strCondition);
        delete gInfo;
        //_endthreadex(0);
        return 0;
    }
    delete gInfo;
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
    return 0;
}

typedef struct deleteMultiClassInfoArg
{
    QString acount;
    QList<QString>* createTimeLst;
    QList<QString>* classNameLst;
    CMainMenueDlg* thiz;
}DeleteMultiClassInfoArg;

void CMainMenueDlg::deleteMultiClassInfo()
{
    DeleteMultiClassInfoArg*  arg = new DeleteMultiClassInfoArg();
    arg->thiz = this;
    arg->acount = this->m_acount;

    QList<QString>* createTimeLst = new QList<QString>();
    arg->classNameLst = new QList<QString>();
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
                QString className = this->m_classNameVec.at(i)->text().trimmed();
                if(className != "")
                {
                    arg->classNameLst->push_back(className);
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
    //初始化序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout();
        widget->setLayout(layout);
        QCheckBox* checkBox = new QCheckBox();
        checkBox->setText(QString::number(++this->m_sortNumStudentRequest));
        checkBox->setFont(QFont("黑体"));
        checkBox->setStyleSheet("QCheckBox{border:none;margin-left:25px;}");
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

    //进行修改样式
    for(int i = 0 ; i < 8;i++)
    {
        if(i % 2 == 0)
        {
            this->m_studentRequestCheckVec.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
            this->m_studentRequestNameVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_studentRequestStudentIdVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_studentRequestTimeVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_studentRequestOpetators.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
        }else
        {
            this->m_studentRequestCheckVec.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
            this->m_studentRequestNameVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_studentRequestStudentIdVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_studentRequestTimeVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_studentRequestOpetators.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
        }
    }
}


unsigned WINAPI CMainMenueDlg::threadDeleteMultiClassInfo(LPVOID arg)
{
    DeleteMultiClassInfoArg* dInfo = (DeleteMultiClassInfoArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteMultiClassInfo(dInfo->acount,*dInfo->createTimeLst,*dInfo->classNameLst);
    delete dInfo->createTimeLst;
    delete dInfo->classNameLst;
    delete dInfo;

    //批量操作后需要将下表进行设置为1
    dInfo->thiz->m_classCurPageIndex = 1;
    emit dInfo->thiz->startGetClassTableInfo();
    emit dInfo->thiz->startGetClassTableIndex();
    //_endthreadex(0);
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
    QString className;
}DeleteClassInfoByDateTimeArg;

void CMainMenueDlg::deleteClassInfoByDateTime(int row)
{
    //获取到同一行的创建时间
    QString createTime = this->m_classCreateTimeVec.at(row)->text().trimmed();
    qDebug()<<"createTime: "<<createTime;

    QString className = this->m_classNameVec.at(row)->text().trimmed();

    DeleteClassInfoByDateTimeArg* arg = new DeleteClassInfoByDateTimeArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->createTime = createTime;
    arg->className = className;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteClassInfoByDateTimeEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadDeleteClassInfoByDateTimeEntry(LPVOID arg)
{
    DeleteClassInfoByDateTimeArg* dInfo = (DeleteClassInfoByDateTimeArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteClassInfoByDateTime(dInfo->acount,dInfo->createTime,dInfo->className);
    //重新显示和请求数据
    emit dInfo->thiz->startGetClassTableInfo();
    emit dInfo->thiz->startGetClassTableIndex();
    delete dInfo;
    //_endthreadex(0);
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

    //清除选中项
    emit this->ui->checkBox_8->toggled(false);
    this->ui->checkBox_8->setChecked(false);
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
    emit this->ui->checkBox_8->toggled(false);
    this->ui->checkBox_8->setChecked(false);
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
    //_endthreadex(0);
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

void CMainMenueDlg::showClassIconInStudentManagerUI(QImage* image)
{
    if(image == nullptr)
    {
        return ;
    }
    this->ui->label_67->setPixmap(QPixmap::fromImage(*image));
    this->ui->label_67->setScaledContents(true);
    delete image;
}

void  CMainMenueDlg::showStudentHeadIconUI(QImage* image)
{
    QList<QLabel*> ret =  this->m_studentManegerHeadIconVec.at(this->m_studentManegerClassIconIndex++)->findChildren<QLabel*>();
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
    //_endthreadex(0);
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
//       QString str = ret->at(i).at//_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
        checkBox->setStyleSheet("QCheckBox{border:none;margin-left:25px;}");
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

    //进行修改表格的样式
    for(int i = 0 ; i < 8; i++)
    {
        if(i % 2 == 0)
        {
            this->m_classCheckVec.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
            this->m_classIconVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_classNameVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_classCreateTimeVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_classCreatorVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_classOperationsVec.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
        }else
        {
            this->m_classCheckVec.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
            this->m_classIconVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_classNameVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_classCreateTimeVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_classCreatorVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_classOperationsVec.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
        }
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
    QList<QString>* testPaperIdLst;
    CMainMenueDlg* thiz;
}DeleteMultiClickBtnArg;

void CMainMenueDlg::deleteMultiClickBtn()
{
    DeleteMultiClickBtnArg*  arg = new DeleteMultiClickBtnArg();
    arg->thiz = this;
    arg->acount = this->m_acount;

    QList<QString>* createTimeLst = new QList<QString>();
    QList<QString>* testPaperNameLst = new QList<QString>(); //用于存储被选中的试卷的试卷Id
    for(int i = 0 ; i < this->m_checkVec.size();i++)
    {
        QList<QCheckBox*> ret =  m_checkVec.at(i)->findChildren<QCheckBox*>();
        for(QCheckBox* check :ret)
        {
            if(check->isChecked())
            {
                QString createTime = this->m_createTime.at(i)->text().trimmed();
                QString testPaperName = this->m_testPaperName.at(i)->text().trimmed();
                if(createTime != "")
                {
                    createTimeLst->push_back(createTime);
                    testPaperNameLst->push_back(testPaperName);
                }
            }
        }
    }
    arg->createTimeLst = createTimeLst;
    arg->testPaperIdLst = testPaperNameLst;
    this->curPageIndex = 1;
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
    this->ui->checkBox_7->setChecked(false);
}

unsigned WINAPI CMainMenueDlg::threadDeleteMultiClickBtnEntry(LPVOID arg)
{
      DeleteMultiClickBtnArg* dInfo = (DeleteMultiClickBtnArg*)arg;
      dInfo->thiz->m_mainMenueContorller->deleteMultiClickBtn(dInfo->acount,*dInfo->createTimeLst,*dInfo->testPaperIdLst);
      delete dInfo->createTimeLst;
      delete dInfo->testPaperIdLst;
      delete dInfo;
      dInfo->thiz->getCurPageIndexTableData();
      dInfo->thiz->getTablePageCount();
      //_endthreadex(0);
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
    HANDLE thread =(HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteFromShortAnswerEntry,arg,0,nullptr);
    this->m_deleteTestPaperThread.push_back(thread);
}

unsigned WINAPI CMainMenueDlg::threadDeleteFromShortAnswerEntry(LPVOID arg)
{
    DeleteFromShortAnswerArg* dInfo = ( DeleteFromShortAnswerArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteFromShortAnswer(dInfo->acount,dInfo->createTime);
    delete dInfo;
    //_endthreadex(0);
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
    HANDLE thread = (HANDLE) _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteFromJudgeEntry,arg,0,nullptr);
    this->m_deleteTestPaperThread.push_back(thread);
}

unsigned WINAPI CMainMenueDlg::threadDeleteFromJudgeEntry(LPVOID arg)
{
    DeleteFromJudgeArg* dInfo = (DeleteFromJudgeArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteFromJudge(dInfo->acount,dInfo->createTime);
    delete dInfo;
    //_endthreadex(0);
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
 HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteFromMultiChoiseEntry,arg,0,nullptr);
 this->m_deleteTestPaperThread.push_back(thread);
}

unsigned WINAPI CMainMenueDlg::threadDeleteFromMultiChoiseEntry(LPVOID arg)
{
    DeleteFromMultiChoiseArg* dInfo = (DeleteFromMultiChoiseArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteFromMultiChoise(dInfo->acount,dInfo->createTime);
    delete dInfo;
    //_endthreadex(0);
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
    HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteFromSignalChoiseEntry,arg,0,nullptr);
    this->m_deleteTestPaperThread.push_back(thread);
}

void CMainMenueDlg::deleteTestPaperCorrectInfo(QString testPaperName)
{
    DeleteFromSignalChoiseArg* arg = new DeleteFromSignalChoiseArg();
    arg->thiz =this;
    arg->acount = this->m_acount;
    arg->createTime = testPaperName;
    HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,CMainMenueDlg::threadDeleteTestPaperCorrectInfo,arg,0,nullptr);
    this->m_deleteTestPaperThread.push_back(thread);
}

unsigned WINAPI CMainMenueDlg::threadDeleteTestPaperCorrectInfo(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteTestPaperCorrectInfo(dInfo->createTime,dInfo->acount);
    delete dInfo;
    return 0;
}

unsigned WINAPI CMainMenueDlg::threadDeleteFromSignalChoiseEntry(LPVOID arg)
{
    DeleteFromSignalChoiseArg* dInfo = (DeleteFromSignalChoiseArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteFromSignalChoise(dInfo->acount,dInfo->createTime);
    delete dInfo;
    //_endthreadex(0);
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


void CMainMenueDlg::updateStatusClickBtn(int row)  //这里是点击发布的处理函数
{
    QString testPaperName =  this->m_testPaperName.at(row)->text().trimmed();
    //进行试卷发布操作
    if(this->m_testPaperReleaseDlg == nullptr)  //生成对话框
    {
        this->m_testPaperReleaseDlg = new CTestPaperReleaseDlg();
        this->m_testPaperReleaseDlg->SetAcount(this->m_acount);
        this->m_testPaperReleaseDlg->SetTestPaperName(testPaperName);
        this->m_testPaperReleaseDlg->move((this->width() - this->m_testPaperReleaseDlg->width()) / 2 ,(this->height() - this->m_testPaperReleaseDlg->height()) / 2);
        int ret =  this->m_testPaperReleaseDlg->exec(); //线程会在此进行阻塞
        if(this->m_testPaperReleaseDlg != nullptr)
        {
            delete this->m_testPaperReleaseDlg;
            this->m_testPaperReleaseDlg = nullptr;
        }

        //点击的是确认的时候才进行更新
        if(ret == QDialog::Accepted)
        {
            //执行更新发布的试卷信息的状态，并且重新回显全部数据
            this->curPageIndex = 1;
            this->updateTestPaperStatus(testPaperName);
        }
    }
}

typedef struct updateTestPaperStatusArg{
    CMainMenueDlg* thiz;
    QString acount;
    QString testPaperName;
}UpdateTestPaperStatusArg;

void CMainMenueDlg::updateTestPaperStatus(QString testPaperName)
{
    UpdateTestPaperStatusArg* arg = new UpdateTestPaperStatusArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->testPaperName = testPaperName;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadUpdateTestPaperStatus,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadUpdateTestPaperStatus(LPVOID arg)
{
    UpdateTestPaperStatusArg* uInfo = (UpdateTestPaperStatusArg*)arg;
    uInfo->thiz->m_mainMenueContorller->updateTestPaperStatus(uInfo->acount,uInfo->testPaperName);
    //重新回显数据
    uInfo->thiz->getCurPageIndexTableData();
    uInfo->thiz->getTablePageCount();
    delete uInfo;
    //_endthreadex(0);
    return 0;
}

//该结构体作为参数进行删除试卷答题记录
typedef struct deleteAnswerArg{
    QString teacherId;
    QString testPaperName; //前端要进行限制用户进行存储重复的试卷名称信息，确保唯一性
    CMainMenueDlg* thiz;
}DeleteAnswerArg;

void CMainMenueDlg::deleteSignalAnswer(QString testPaperName)
{
   std::shared_ptr<DeleteAnswerArg> arg = std::make_shared<DeleteAnswerArg>();
   arg->teacherId = this->m_acount;
   arg->testPaperName = testPaperName;
   arg->thiz = this;
   std::shared_ptr<DeleteAnswerArg>* p = new std::shared_ptr<DeleteAnswerArg>(arg);
   HANDLE thread =(HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteSignalAnswer,p,0,nullptr);
   this->m_deleteTestPaperThread.push_back(thread);
}

unsigned WINAPI CMainMenueDlg::threadDeleteSignalAnswer(LPVOID arg)
{
    std::shared_ptr<DeleteAnswerArg>* p = (std::shared_ptr<DeleteAnswerArg>*)arg;
    std::shared_ptr<DeleteAnswerArg> dInfo = *p;
    dInfo->thiz->m_mainMenueContorller->deleteSignalAnswer(dInfo->teacherId
                                                           ,dInfo->testPaperName);
    delete p;
    return 0;
}

void CMainMenueDlg::deleteTestPaperCommitInfo(QString testPaperName)
{
    std::shared_ptr<DeleteAnswerArg> arg = std::make_shared<DeleteAnswerArg>();
    arg->teacherId = this->m_acount;
    arg->testPaperName = testPaperName;
    arg->thiz = this;
    std::shared_ptr<DeleteAnswerArg>* p = new std::shared_ptr<DeleteAnswerArg>(arg);
    HANDLE thread =(HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteTestPaperCommitInfo,p,0,nullptr);
    this->m_deleteTestPaperThread.push_back(thread);
}

unsigned WINAPI CMainMenueDlg::threadDeleteTestPaperCommitInfo(LPVOID arg)
{
    std::shared_ptr<DeleteAnswerArg>* p = (std::shared_ptr<DeleteAnswerArg>*)arg;
    std::shared_ptr<DeleteAnswerArg> dInfo = *p;
    dInfo->thiz->m_mainMenueContorller->deleteTestPaperCommitInfo(dInfo->teacherId
                                                           ,dInfo->testPaperName);
    delete p;
    return 0;
}

void CMainMenueDlg::deleteCorrectShortAnswer(QString testPaperName)
{
    std::shared_ptr<DeleteAnswerArg> arg = std::make_shared<DeleteAnswerArg>();
    arg->teacherId = this->m_acount;
    arg->testPaperName = testPaperName;
    arg->thiz = this;
    std::shared_ptr<DeleteAnswerArg>* p = new std::shared_ptr<DeleteAnswerArg>(arg);
    HANDLE thread =(HANDLE) _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteCorrectShortAnswer,p,0,nullptr);
    this->m_deleteTestPaperThread.push_back(thread);
}

unsigned WINAPI CMainMenueDlg::threadDeleteCorrectShortAnswer(LPVOID arg)
{
    std::shared_ptr<DeleteAnswerArg>* p = (std::shared_ptr<DeleteAnswerArg>*)arg;
    std::shared_ptr<DeleteAnswerArg> dInfo = *p;
    dInfo->thiz->m_mainMenueContorller->deleteCorrectShortAnswer(dInfo->teacherId
                                                           ,dInfo->testPaperName);
    delete p;
    return 0;
}

void CMainMenueDlg::deleteShortAnswer(QString testPaperName)
{
    std::shared_ptr<DeleteAnswerArg> arg = std::make_shared<DeleteAnswerArg>();
    arg->teacherId = this->m_acount;
    arg->testPaperName = testPaperName;
    arg->thiz = this;
    std::shared_ptr<DeleteAnswerArg>* p = new std::shared_ptr<DeleteAnswerArg>(arg);
    HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteShortAnswer,p,0,nullptr);
    this->m_deleteTestPaperThread.push_back(thread);
}

unsigned WINAPI CMainMenueDlg::threadDeleteShortAnswer(LPVOID arg)
{
    std::shared_ptr<DeleteAnswerArg>* p = (std::shared_ptr<DeleteAnswerArg>*)arg;
    std::shared_ptr<DeleteAnswerArg> dInfo = *p;
    dInfo->thiz->m_mainMenueContorller->deleteShortAnswer(dInfo->teacherId
                                                           ,dInfo->testPaperName);
    delete p;
    return 0;
}

void CMainMenueDlg::deleteJudgeAnswer(QString testPaperName)
{
    std::shared_ptr<DeleteAnswerArg> arg = std::make_shared<DeleteAnswerArg>();
    arg->teacherId = this->m_acount;
    arg->testPaperName = testPaperName;
    arg->thiz = this;
    std::shared_ptr<DeleteAnswerArg>* p = new std::shared_ptr<DeleteAnswerArg>(arg);
    HANDLE thread =(HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteJudgeAnswer,p,0,nullptr);
    this->m_deleteTestPaperThread.push_back(thread);
}

unsigned WINAPI CMainMenueDlg::threadDeleteJudgeAnswer(LPVOID arg)
{
    std::shared_ptr<DeleteAnswerArg>* p = (std::shared_ptr<DeleteAnswerArg>*)arg;
    std::shared_ptr<DeleteAnswerArg> dInfo = *p;
    dInfo->thiz->m_mainMenueContorller->deleteJudgeAnswer(dInfo->teacherId
                                                           ,dInfo->testPaperName);
    delete p;
    return 0;
}

void CMainMenueDlg::deleteMultiAnswer(QString testPaperName)
{
    std::shared_ptr<DeleteAnswerArg> arg = std::make_shared<DeleteAnswerArg>();
    arg->teacherId = this->m_acount;
    arg->testPaperName = testPaperName;
    arg->thiz = this;
    std::shared_ptr<DeleteAnswerArg>* p = new std::shared_ptr<DeleteAnswerArg>(arg);
    HANDLE thread= (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteMultiAnswer,p,0,nullptr);
    this->m_deleteTestPaperThread.push_back(thread);
}

//TODO:明天的控制层接着继续
unsigned WINAPI CMainMenueDlg::threadDeleteMultiAnswer(LPVOID arg)
{
    std::shared_ptr<DeleteAnswerArg>* p = (std::shared_ptr<DeleteAnswerArg>*)arg;
    std::shared_ptr<DeleteAnswerArg> dInfo = *p;
    dInfo->thiz->m_mainMenueContorller->deleteMultiAnswer(dInfo->teacherId
                                                           ,dInfo->testPaperName);
    delete p;
    return 0;
}

typedef struct deleteTestPaperReleaseInfoArg{
    CMainMenueDlg* thiz;
    QString acount;
    QString testPaperName;
}DeleteTestPaperReleaseInfoArg;

void CMainMenueDlg::deleteTestPaperReleaseInfo(QString testPaperName)
{
   DeleteTestPaperReleaseInfoArg* arg = new DeleteTestPaperReleaseInfoArg();
   arg->thiz = this;
   arg->acount = this->m_acount;
   arg->testPaperName = testPaperName;
   HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteTestPaperReleaseInfo,arg,0,nullptr);
   WaitForSingleObject(thread,INFINITE);
}

unsigned WINAPI CMainMenueDlg::threadDeleteTestPaperReleaseInfo(LPVOID arg)
{
     DeleteTestPaperReleaseInfoArg* dInfo = ( DeleteTestPaperReleaseInfoArg*)arg;
     dInfo->thiz->m_mainMenueContorller->deleteTestPaperReleaseInfo(dInfo->acount,dInfo->testPaperName);
     delete dInfo;
     //_endthreadex(0);
     return 0;
}

typedef struct deleteClickBtnArg
{
    QString acount;
    QString createTime;
    CMainMenueDlg* thiz;
}DeleteClickBtnArg;

void CMainMenueDlg::deleteClickBtn(int row)  //点击单次调用的函数
{
    //获取到同一行的创建时间
    QString createTime = this->m_createTime.at(row)->text().trimmed();
    qDebug()<<"createTime: "<<createTime; 

    QString testPaperName = this->m_testPaperName.at(row)->text().trimmed();
    qDebug()<<"testPaperName: "<<testPaperName;


    //进行删除单选题、多选题、判断题的题库
    this->deleteFromSignalChoise(createTime);
    this->deleteFromMultiChoise(createTime);
    this->deleteFromJudge(createTime);
    this->deleteFromShortAnswer(createTime);

    //进行删除该试卷的所有的答题记录
    this->deleteSignalAnswer(testPaperName);
    this->deleteMultiAnswer(testPaperName);
    this->deleteJudgeAnswer(testPaperName);
    this->deleteShortAnswer(testPaperName);

    //进行删除该试卷的所有的简答题评分记录
    this->deleteCorrectShortAnswer(testPaperName);

    //进行删除该试卷的提交记录
    this->deleteTestPaperCommitInfo(testPaperName);

    //进行删除简答题批改表记录
    this->deleteTestPaperCorrectInfo(testPaperName);

    //需要等待上面的任务都执行完毕才能进行删除试卷表的信息
    WaitForMultipleObjects(this->m_deleteTestPaperThread.size()
                           ,this->m_deleteTestPaperThread.data(),TRUE,INFINITE);
    //删除与该试卷的发布信息记录
    this->deleteTestPaperReleaseInfo(testPaperName); //这里要等记录先删除完毕再进行往下执行删除试卷信息

    //进行清除存储句柄的容器
    this->m_deleteTestPaperThread.clear();

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
   dInfo->thiz->curPageIndex = 1;
   dInfo->thiz->getCurPageIndexTableData();
   dInfo->thiz->getTablePageCount();
   delete dInfo;
   //_endthreadex(0);
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
             }else if(btn->text() == "预览")
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
                                 this->previewTestPaper(row);
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

void CMainMenueDlg::previewTestPaper(int row)
{
    QString testPaperName = this->m_testPaperName.at(row)->text().trimmed();
    if(this->m_previewTestPaper == nullptr)
    {
        this->m_previewTestPaper = new CPreviewTestPaperDlg();
        this->m_previewTestPaper->SetAcount(this->m_acount);
        this->m_previewTestPaper->SetTestPaperName(testPaperName);
        this->m_previewTestPaper->move(this->x(),this->y());
        this->m_previewTestPaper->show();
        this->hide();
        QObject::connect(this->m_previewTestPaper,&CPreviewTestPaperDlg::rejected,[=](){
            if(this->m_previewTestPaper!= nullptr)
            {
                delete this->m_previewTestPaper;
                this->m_previewTestPaper = nullptr;
                this->show();
            }
        });
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    emit this->ui->checkBox_7->toggled(false);
    this->ui->checkBox_7->setChecked(false);
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
    emit this->ui->checkBox_7->toggled(false);
    this->ui->checkBox_7->setChecked(false);
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
        checkBox->setStyleSheet("QCheckBox{border:none;margin-left:45px;}");
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
        QPushButton* release2 = new QPushButton("预览");
        release2->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        release2->setParent(widget);
        layout->addWidget(deleteBtn);
        layout->addWidget(release);
        layout->addWidget(release2);
        deleteBtn->setVisible(false);
        release->setVisible(false);
        release2->setVisible(false);
        this->ui->tableWidget->setCellWidget(i,6,widget);
        this->m_operators.push_back(widget);
    }

    //初始化表格样式
    for(int i = 0 ; i < 8 ; i++)
    {
        if(i % 2 == 0)
        {
            this->m_checkVec.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
            this->m_testPaperName.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_testPaperCount.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_createTime.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_creater.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_status.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_operators.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
        }else
        {
            this->m_checkVec.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
            this->m_testPaperName.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_testPaperCount.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_createTime.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_creater.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_status.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_operators.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
        }
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
     //_endthreadex(0);
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
    //_endthreadex(0);
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
   //_endthreadex(0);
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
   //_endthreadex(0);
   return 0;
}

void CMainMenueDlg::initStudentAnswerShortAnswerTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitStudentAnswerShortAnswerTableEntry,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitStudentAnswerShortAnswerTableEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initStudentAnswerShortAnswerTable();
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::initStudentAnswerJudgeTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitStudentAnswerJudgeTableEntry,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitStudentAnswerJudgeTableEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initStudentAnswerJudgeTable();
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::initStudentAnswerMultiTable()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitStudentAnswerMultiTableEntry,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitStudentAnswerMultiTableEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initStudentAnswerMultiTable();
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::getCurPageIndexTableData()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetCurPageIndexTableData,this,0,nullptr);
}

void CMainMenueDlg::showCurPageIndexTable(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return;
    }
    this->clearTestPaperTableContorl();
    qDebug()<<"获取已发布的数量："<<ret->size();
    this->m_teacherIdVec.clear();
    this->m_testPaperIdVec.clear();
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

       //进行存储教师的Id
       str = ret->at(i).at(5);
       this->m_teacherIdVec.push_back(str);

       //进行存储试卷的Id
       str = ret->at(i).at(6);
       this->m_testPaperIdVec.push_back(str);

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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::deleteTreeItemRecursively(QTreeWidgetItem* item) {
    if (!item) return; // 若传入的item为空，则直接返回

    // 获取并删除item的所有子项
    int childCount = item->childCount();
    for (int i = 0; i < childCount; ++i) {
        deleteTreeItemRecursively(item->takeChild(0)); // 递归删除子项，
       /*  注意：takeChild//_endthreadex(0)会移除并返回第一个子项，
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
    return 0;
}

typedef struct teacherAcountInfoArg
{
    QString acount;
    CMainMenueDlg* thiz;
}TeacherAcountInfoArg;

void CMainMenueDlg::getTeacherAcountInfoData()
{
    this->ui->stackedWidget->setCurrentIndex(5);
    TeacherAcountInfoArg* arg = new TeacherAcountInfoArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetTeacherAcountInfoDataEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetTeacherAcountInfoDataEntry(LPVOID arg)
{
    TeacherAcountInfoArg* tInfo = (TeacherAcountInfoArg*)arg;
    std::vector<std::vector<std::string>> ret =  tInfo->thiz->m_mainMenueContorller->showTeacherAcountInfo(tInfo->acount); //view层调用conntorller层的接口全部写到子线程中
    std::vector<std::vector<std::string>>* result  = new std::vector<std::vector<std::string>>();
    for(int i = 0 ; i < ret.size() ; i++)
    {
        std::vector<std::string> temp;
        for(int j = 0 ; j < ret.at(i).size();j++)
        {
            temp.push_back(ret.at(i).at(j));
        }
        result->push_back(temp);
    }

    emit tInfo->thiz->startShowTeacherAcountInfo(result);
    delete tInfo;
    //_endthreadex(0);
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
    if(ret != nullptr)
    {
        delete ret;
    }
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
    //_endthreadex(0);
    return 0;
}

unsigned WINAPI CMainMenueDlg::threadInitTeacherInfoTableEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initTeacherInfoTable();
    //_endthreadex(0);
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

    for(QVector<QWidget*>::iterator pos =  this->m_studentManegerCheckVec.begin(); pos !=  this->m_studentManegerCheckVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_studentManegerCheckVec.clear();

    for(QVector<QWidget*>::iterator pos =  this->m_studentManegerHeadIconVec.begin(); pos !=  this->m_studentManegerHeadIconVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_studentManegerHeadIconVec.clear();

    for(QVector<QLabel*>::iterator pos =  this->m_studentManagerStudentNameVec.begin(); pos !=  this->m_studentManagerStudentNameVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_studentManagerStudentNameVec.clear();

    for(QVector<QLabel*>::iterator pos =  this->m_studentManagerStudentIdVec.begin(); pos !=  this->m_studentManagerStudentIdVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_studentManagerStudentIdVec.clear();

    for(QVector<QLabel*>::iterator pos =  this->m_studentManegerPhoneNumberVec.begin(); pos !=  this->m_studentManegerPhoneNumberVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_studentManegerPhoneNumberVec.clear();

    for(QVector<QLabel*>::iterator pos =  this->m_studentManegerJoinTimeVec.begin(); pos !=  this->m_studentManegerJoinTimeVec.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_studentManegerJoinTimeVec.clear();

    for(QVector<QWidget*>::iterator pos =  this->m_studentManegerOperators.begin(); pos !=  this->m_studentManegerOperators.end();pos++)
    {
        if(*pos != nullptr)
        {
           delete  *pos;
        }
    }
    this->m_studentManegerOperators.clear();

    for(QLabel* lab : this->m_correctTestPaperName)
    {
        if(lab != nullptr)
        {
            delete  lab;
        }
    }
    this->m_correctTestPaperName.clear();

    for(QLabel* lab : this->m_corrected)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_corrected.clear();


    for(QLabel* lab : this->m_notCorrected)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_notCorrected.clear();

    for(QWidget* widget : this->m_correctOprator)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_correctOprator.clear();

    for(QLabel* lab : this->m_correctMemberName)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_correctMemberName.clear();

    for(QLabel* lab : this->m_correctMemberSubject)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_correctMemberSubject.clear();

    for(QLabel* lab : this->m_correctMemberKeGuan)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_correctMemberKeGuan.clear();

    for(QLabel* lab : this->m_correctMemberZhuGuan)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_correctMemberZhuGuan.clear();

    for(QLabel* lab : this->m_correctMemberSum)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_correctMemberSum.clear();

    for(QWidget* widget : this->m_correctMemberOperator)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_correctMemberOperator.clear();

    //如果关闭界面，接收头像信息的线程还在执行的话就等待接收后结束线程
    WaitForSingleObject(this->m_recvHeadThead,INFINITE); //找到退出崩溃的原因，因为关闭界面的时候，接收头像线程还在执行，但是UI已经释放导致异常
    //释放容器中的QTreeItem
    this->deleteAllTreeItems(this->ui->treeWidget);
    delete ui;
}
