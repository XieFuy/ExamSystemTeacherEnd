#include "previewtestpaperdlg.h"
#include "ui_previewtestpaperdlg.h"

CPreviewTestPaperDlg::CPreviewTestPaperDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPreviewTestPaperDlg)
{
    ui->setupUi(this);
}

CPreviewTestPaperDlg::~CPreviewTestPaperDlg()
{
    delete ui;
}
