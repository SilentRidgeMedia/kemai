#include "editdialog.h"
#include "ui_editdialog.h"
#include "QFile"
#include "QString"
#include "QTextStream"
#include "QDataStream"
#include "activitywidget.h"
#include "settingswidget.h"
#include "ui_settingswidget.h"

#include <QtSql>
#include<QString>

QString key;
using namespace kemai::app;

QString name;

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
}

EditDialog::~EditDialog()
{
    delete ui;
}


void EditDialog::on_pushButton_clicked()
{
    //save
    QString name,host,username,token;
    name=ui->lineEdit->text();
    host=ui->lineEdit_2->text();
    username=ui->lineEdit_3->text();
    token=ui->lineEdit_4->text();

    QSqlQuery quer;
    quer.prepare( "INSERT INTO Profiles (Name, Username, Token, Host) VALUES (:Name, :Username, :Token, :Host)" );
    quer.bindValue(":Name", name);
    quer.bindValue(":Username", username);
    quer.bindValue(":Token", token);
    quer.bindValue(":Host", host);
    if( !quer.exec() )
        qDebug() << quer.lastError();
    else
        qDebug( "Inserted!" );
    SettingsWidget stw;
    stw.populatingComboBox();
    close();

}
/*void EditDialog::recieveKey(QString key)
{
    QString name = key;
}*/
void EditDialog::getValues(QString name)
{
    QSqlQuery qry;
    qry.prepare("select * from Profiles where Name = '"+name+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit->setText(name);
            ui->lineEdit_2->setText(qry.value(3).toString());
            ui->lineEdit_3->setText(qry.value(1).toString());
            ui->lineEdit_4->setText(qry.value(2).toString());
        }
    }
    else
        qDebug() << qry.lastError();
    qDebug("here!"+name.toLatin1());
}