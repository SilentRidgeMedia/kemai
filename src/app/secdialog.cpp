#include "secdialog.h"
#include "ui_secdialog.h"
#include "editdialog.h"
#include "ui_editdialog.h"
#include "editdialog.h"
#include "client/kimairequestfactory.h"
#include "settings.h"


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
    ui->nameBox->setModel(model);

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
void SecDialog::on_nameBox_currentIndexChanged(const QString &arg1)
{
    EditDialog etd;
    QString name = ui->nameBox->currentText();
    QSqlQuery qry;
    qry.prepare("select * from Profiles where Name = '"+name+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            etd.ui->lineEdit->setText(qry.value(0).toString());
            etd.ui->lineEdit_2->setText(qry.value(1).toString());
            etd.ui->lineEdit_3->setText(qry.value(2).toString());
            etd.ui->lineEdit_4->setText(qry.value(3).toString());
        }
    }
    else
        qDebug() << qry.lastError();
    qDebug("combo working");

}
/*void SecDialog::pushSettings()
{
    Settings settings;
    EditDialog e2d;
    settings.kemai.host = e2d.ui->lineEdit_2->text();
    settings.kemai.username = e2d.ui->lineEdit_3->text();
    settings.kemai.token = e2d.ui->lineEdit_4->text();
}*/



