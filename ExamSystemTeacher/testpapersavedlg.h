#ifndef TESTPAPERSAVEDLG_H
#define TESTPAPERSAVEDLG_H

#include <QDialog>
#include "DBHelper.h"
#include <vector>
#include <string>
namespace Ui {
class CTestPaperSaveDlg;
}

class CTestPaperSaveDlg : public QDialog //该对话框为试卷保存对话框
{
    Q_OBJECT

public:
    explicit CTestPaperSaveDlg(QWidget *parent = nullptr);
    ~CTestPaperSaveDlg();
    QString m_acount;
private:
    Ui::CTestPaperSaveDlg *ui;
};

#endif // TESTPAPERSAVEDLG_H
