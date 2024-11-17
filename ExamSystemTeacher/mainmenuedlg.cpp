#include "mainmenuedlg.h"
#include "ui_mainmenuedlg.h"

CMainMenueDlg::CMainMenueDlg(QWidget *parent) : //主菜单界面类
    QDialog(parent),
    ui(new Ui::CMainMenueDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("在线考试系统-教师端");
    this->setWindowIcon(QIcon(":/icons/winIcon.png"));

    this->signalCount = 0;
    this->multiCount = 0;
    this->judgeCount = 0;
    this->shortAnswerCount = 0;
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



    QObject::connect(this->ui->pushButton_15,&QPushButton::clicked,[=](){
        QString str = "(";
        QString num = QString::number(++this->multiCount);
        str += num;
        str +=")";
        QTreeWidgetItem* multiItem = new QTreeWidgetItem(QStringList()<<str);
        this->m_multiOerator->addChild(multiItem);
        this->m_multiOeratorLst.push_back(multiItem);
        this->m_multiMap.insert(str,this->multiCount);

        //将数据存储到数据库中

        //将UI的题进行清空
    });

    QObject::connect(this->ui->pushButton_9,&QPushButton::clicked,[=](){
        this->ui->stackedWidget_2->setCurrentIndex(1);
        this->ui->pushButton_9->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_8->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_10->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_11->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_17,&QPushButton::clicked,[=](){
        QString str = "(";
        QString num = QString::number(++this->judgeCount);
        str += num;
        str +=")";
        QTreeWidgetItem* judgeItem = new QTreeWidgetItem(QStringList()<<str);
        this->m_judge->addChild(judgeItem);
        this->m_judgeLst.push_back(judgeItem);
        this->m_judgeMap.insert(str,this->judgeCount);

        //将数据存储到数据库中

        //将UI的题进行清空
    });

    QObject::connect(this->ui->pushButton_10,&QPushButton::clicked,[=](){       
        this->ui->stackedWidget_2->setCurrentIndex(2);
        this->ui->pushButton_10->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_8->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_9->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_11->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_19,&QPushButton::clicked,[=](){
        QString str = "(";
        QString num = QString::number(++this->shortAnswerCount);
        str += num;
        str +=")";
        QTreeWidgetItem* shortAnswerItem = new QTreeWidgetItem(QStringList()<<str);
        this->m_ShortAnswer->addChild(shortAnswerItem);
        this->m_ShortAnswerLst.push_back(shortAnswerItem);
        this->m_shortAnswerMap.insert(str,this->shortAnswerCount);

        //将数据存储到数据库中

        //将UI的题进行清空
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
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,this,&CMainMenueDlg::showTeacherAcountInfo);
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

void CMainMenueDlg::addSignalChoiceInfo(QString grade,QString question,QString sessionA,QString sessionB,QString sessionC,QString sessionD,QString correctOptions,int order)
{
   this->m_mainMenueContorller->addSignalChoiceInfo(grade,question,sessionA,sessionB,sessionC,sessionD,correctOptions,order);
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


void CMainMenueDlg::initTestPaperTable()
{
     this->m_mainMenueContorller->initTestPaperTable();
}

void CMainMenueDlg::initSingleChoiceTable()
{
    this->m_mainMenueContorller->initSingleChoiceTable();
}

void CMainMenueDlg::initMultiChoiceTable()
{
    this->m_mainMenueContorller->initMultiChoiceTable();
}

void CMainMenueDlg::initJudgeTable()
{
    this->m_mainMenueContorller->initJudgeTable();
}

void CMainMenueDlg::initShortAnswerTable()
{
    this->m_mainMenueContorller->initShortAnswerTable();
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

void CMainMenueDlg::changeGender(bool isChecked)
{
    this->m_mainMenueContorller->changeGender(isChecked,this->m_acount);
}

void CMainMenueDlg::showTeacherAcountInfo()
{
    std::vector<std::vector<std::string>> ret =  this->m_mainMenueContorller->showTeacherAcountInfo(this->m_acount);
    QString name = QString::fromLocal8Bit(ret.at(0).at(0).c_str());
    QString teacherId = QString::fromLocal8Bit(ret.at(0).at(1).c_str());
    QString gender = QString::fromLocal8Bit(ret.at(0).at(2).c_str());
    QString phoneNumber = QString::fromLocal8Bit(ret.at(0).at(3).c_str());

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

void CMainMenueDlg::initTeacherInfoTable()
{
  this->m_mainMenueContorller->initTeacherInfoTable();
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
    //如果关闭界面，接收头像信息的线程还在执行的话就等待接收后结束线程
    WaitForSingleObject(this->m_recvHeadThead,INFINITE); //找到退出崩溃的原因，因为关闭界面的时候，接收头像线程还在执行，但是UI已经释放导致异常
    //释放容器中的QTreeItem
    this->deleteAllTreeItems(this->ui->treeWidget);
    delete ui;
}
