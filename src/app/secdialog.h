#ifndef SECDIALOG_H
#define SECDIALOG_H


#include "client/kimaiclient.h"


#include <QDialog>

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_nameBox_currentIndexChanged(const QString &arg1);

private:
    Ui::SecDialog *ui;
    void pushsettings();
};

#endif // SECDIALOG_H
