#include "mainmenuedlg.h"
#include "ui_mainmenuedlg.h"

CMainMenueDlg::CMainMenueDlg(QWidget *parent) : //主菜单界面类
    QDialog(parent),
    ui(new Ui::CMainMenueDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("在线考试系统-教师端");
    this->setWindowIcon(QIcon(":/icons/winIcon.png"));

    this->sortNUmber = 0;
    this->signalCount = 0;
    this->multiCount = 0;
    this->judgeCount = 0;
    this->shortAnswerCount = 0;
    this->m_multiCorrectOptions = "";
    this->m_testPaperStatusChoise = 0;

    this->m_judgeAnswer = "";
    this->ui->comboBox->addItem("全部",0);
    this->ui->comboBox->addItem("已发布",1);
    this->ui->comboBox->addItem("未发布",2);
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
    delete gInfo;
    _endthreadex(0);
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
         tr("请选择PNG图片,并且单张图片不得超过2MB"),
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
    CClientSocket* clientSocket = CClientSocket::getInstance();
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
    //如果关闭界面，接收头像信息的线程还在执行的话就等待接收后结束线程
    WaitForSingleObject(this->m_recvHeadThead,INFINITE); //找到退出崩溃的原因，因为关闭界面的时候，接收头像线程还在执行，但是UI已经释放导致异常
    //释放容器中的QTreeItem
    this->deleteAllTreeItems(this->ui->treeWidget);
    delete ui;
}
