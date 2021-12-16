#include "secdialog.h"
#include "ui_secdialog.h"
#include "editdialog.h"
#include "settingswidget.h"
#include "ui_editdialog.h"
#include "editdialog.h"

#include <QtSql>


SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery qry1;
    qry1.prepare("SELECT Name FROM Profiles");
    qry1.exec();
    model->setQuery(qry1);
    ui->comboBox->setModel(model);

}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_2_clicked()
{
    //add
    EditDialog ed;
    ed.setModal(true);
    ed.exec();
}


void SecDialog::on_pushButton_clicked()
{
    //edit
    EditDialog ed;
    ed.setModal(true);
    ed.exec();
}
void SecDialog::on_comboBox_currentIndexChanged(const QString &arg1,Ui::EditDialog *ui)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Profiles WHERE Name = '"+arg1+"'");
    qry.exec();
    while(qry.next())
    {
        ui->lineEdit->setText(qry.value(0).toString());
        ui->lineEdit_2->setText(qry.value(1).toString());
        ui->lineEdit_3->setText(qry.value(2).toString());
        ui->lineEdit_4->setText(qry.value(3).toString());
    };
}



