#ifndef SECDIALOG_H
#define SECDIALOG_H


#include "editdialog.h"

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

    void on_comboBox_currentIndexChanged(const QString &arg1,Ui::EditDialog *ui);

private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
