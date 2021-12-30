#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class EditDialog;
}
namespace kemai::app {
class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = nullptr);
    ~EditDialog();
    Ui::EditDialog *ui;
    void getValues();
    QString name;
public slots:
    void recieveKey(QString key);

private slots:
    void on_pushButton_clicked();

private:
    
};
}
#endif // EDITDIALOG_H
