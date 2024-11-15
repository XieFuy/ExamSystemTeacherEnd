#ifndef PHONENUMBERCHANGEDLG_H
#define PHONENUMBERCHANGEDLG_H

#include <QDialog>
#include "DBHelper.h"

namespace Ui {
class CPhoneNumberChangeDlg;
}

class CPhoneNumberChangeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CPhoneNumberChangeDlg(QWidget *parent = nullptr);
    ~CPhoneNumberChangeDlg();
    QString m_acount;
private:
    Ui::CPhoneNumberChangeDlg *ui;
};

#endif // PHONENUMBERCHANGEDLG_H
