#ifndef NAMECHANGEDLG_H
#define NAMECHANGEDLG_H

#include <QDialog>
#include "DBHelper.h"
namespace Ui {
class CNameChangeDlg;
}

class CNameChangeDlg : public QDialog //用户名修改对话框
{
    Q_OBJECT

public:
    explicit CNameChangeDlg(QWidget *parent = nullptr);
    ~CNameChangeDlg();
    QString m_acount;
private:
    Ui::CNameChangeDlg *ui;
};

#endif // NAMECHANGEDLG_H
