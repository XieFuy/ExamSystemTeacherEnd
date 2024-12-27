#ifndef PREVIEWTESTPAPERDLG_H
#define PREVIEWTESTPAPERDLG_H

#include <QDialog>

namespace Ui {
class CPreviewTestPaperDlg;
}

class CPreviewTestPaperDlg : public QDialog //试卷预览对话框
{
    Q_OBJECT

public:
    explicit CPreviewTestPaperDlg(QWidget *parent = nullptr);
    ~CPreviewTestPaperDlg();

private:
    Ui::CPreviewTestPaperDlg *ui;
};

#endif // PREVIEWTESTPAPERDLG_H
