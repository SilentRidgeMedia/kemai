#include "editdialog.h"
#include "ui_editdialog.h"
#include "QFile"
#include "QString"
#include "QTextStream"
#include "QDataStream"
#include "activitywidget.h"
#include "secdialog.h"

#include <QtSql>


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
}

