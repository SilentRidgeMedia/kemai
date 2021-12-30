#include "settingswidget.h"
#include "ui_settingswidget.h"

#include "client/kimairequestfactory.h"
#include "settings.h"
#include "editdialog.h"
#include "ui_editdialog.h"

#include <QAction>
#include <QDir>
#include <QMessageBox>
#include <QTranslator>
#include <QtSql>
#include <QString>

using namespace kemai::app;
using namespace kemai::client;
using namespace kemai::core;

QString k;

SettingsWidget::SettingsWidget(QWidget* parent) : QWidget(parent), mUi(new Ui::SettingsWidget), mKimaiClient(new KimaiClient)
{
    mUi->setupUi(this);

    auto addLanguage = [cbLanguage = mUi->cbLanguage](const QString& language) {
        QLocale locale(language);
        cbLanguage->addItem(QString("%1 [%2]").arg(QLocale::languageToString(locale.language()), QLocale::countryToString(locale.country())), locale);
    };

    mActToggleTokenVisible = mUi->leToken->addAction(QIcon(":/icons/visible-off"), QLineEdit::TrailingPosition);

    // Add default en_US language
    addLanguage("en_US");

    // Add available translations
    QDir l10nDir(":/l10n");
    for (const auto& fLang : l10nDir.entryList())
    {
        QTranslator translator;
        if (translator.load(l10nDir.absoluteFilePath(fLang), "kemai", "_", ":/l10n"))
        {
            addLanguage(translator.language());
        }
    }

    connect(mKimaiClient.data(), &KimaiClient::requestError, this, &SettingsWidget::onClientError);
    connect(mKimaiClient.data(), &KimaiClient::replyReceived, this, &SettingsWidget::onClientReply);
    connect(mUi->btTest, &QPushButton::clicked, this, &SettingsWidget::onBtTestClicked);
    connect(mUi->btCancel, &QPushButton::clicked, this, &SettingsWidget::onBtCancelClicked);
    connect(mUi->btSave, &QPushButton::clicked, this, &SettingsWidget::onBtSaveClicked);
    connect(mUi->nameBox, &QComboBox::currentTextChanged, this, &SettingsWidget::on_nameBox_currentIndexChanged);
    connect(mUi->btAdd, &QPushButton::clicked, this, &SettingsWidget::addUser);
    connect(mUi->btEdit, &QPushButton::clicked, this, &SettingsWidget::editUser);
    connect(mActToggleTokenVisible, &QAction::triggered, [&]() {
        if (mUi->leToken->echoMode() == QLineEdit::Password)
        {
            mUi->leToken->setEchoMode(QLineEdit::Normal);
            mActToggleTokenVisible->setIcon(QIcon(":/icons/visible"));
        }
        else
        {
            mUi->leToken->setEchoMode(QLineEdit::Password);
            mActToggleTokenVisible->setIcon(QIcon(":/icons/visible-off"));
        }
    });

    // show dialog if language changes from settings
    connect(mUi->cbLanguage, &QComboBox::currentTextChanged, [&](const QString&) {
        auto settings = Settings::load();
        if (settings.kemai.language != mUi->cbLanguage->currentData().toLocale())
        {
            QMessageBox::warning(this, tr(""), tr("Language changed. Application restart is required."));
        }
    });

    loadSettings();
    populatingComboBox();
}

SettingsWidget::~SettingsWidget()
{
    delete mUi;
}

void SettingsWidget::onClientError(const QString& errorMsg)
{
    mUi->lbTestResult->setText(errorMsg);
}

void SettingsWidget::onClientReply(const KimaiReply& reply)
{
    if (!reply.isValid())
    {
        mUi->lbTestResult->setText(tr("Invalid reply."));
    }
    else
    {
        auto version = reply.get<KimaiVersion>();
        mUi->lbTestResult->setText(tr("Connected to Kimai %1").arg(version.kimai.toString()));
    }
}

void SettingsWidget::loadSettings()
{
    auto settings = Settings::load();
    mUi->leHost->setText(settings.kimai.host);
    mUi->leUsername->setText(settings.kimai.username);
    mUi->leToken->setText(settings.kimai.token);
    mUi->cbCloseToSystemTray->setChecked(settings.kemai.closeToSystemTray);

    auto idLanguage = mUi->cbLanguage->findData(settings.kemai.language);
    if (idLanguage >= 0)
    {
        mUi->cbLanguage->setCurrentIndex(idLanguage);
    }
}
void SettingsWidget::on_nameBox_currentIndexChanged(const QString& arg1)
{
    k = mUi->nameBox->currentText();
    emit sendKey(k);
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Profiles WHERE Name = :name");
    qry.bindValue(":name", mUi->nameBox->currentText());
    qry.exec();
    qry.next();
    mUi->leHost->setText(qry.value(3).toString());
    mUi->leUsername->setText(qry.value(1).toString());
    mUi->leToken->setText(qry.value(2).toString());
}
void SettingsWidget::saveSettings()
{
    Settings settings;
    settings.kimai.host              = mUi->leHost->text();
    settings.kimai.username          = mUi->leUsername->text();
    settings.kimai.token             = mUi->leToken->text();
    settings.kemai.closeToSystemTray = mUi->cbCloseToSystemTray->isChecked();
    settings.kemai.language          = mUi->cbLanguage->currentData().toLocale();
    Settings::save(settings);
}

void SettingsWidget::onBtTestClicked()
{
    mUi->lbTestResult->clear();

    mKimaiClient->setHost(mUi->leHost->text());
    mKimaiClient->setUsername(mUi->leUsername->text());
    mKimaiClient->setToken(mUi->leToken->text());
    mKimaiClient->sendRequest(KimaiRequestFactory::version());
}

void SettingsWidget::onBtCancelClicked()
{
    loadSettings();
    emit cancelled();
}

void SettingsWidget::onBtSaveClicked()
{
    saveSettings();
    emit settingsSaved();
}
void SettingsWidget::addUser()
{
    EditDialog eda;
    eda.setModal(true);
    eda.exec();
}
void SettingsWidget::editUser()
{
    qDebug("here!"+dkey.toLatin1());
    EditDialog ed;
    ed.setModal(true);
    ed.getValues();
    ed.exec();
}
void SettingsWidget::populatingComboBox()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery qry1;
    qry1.prepare("SELECT Name FROM Profiles");
    qry1.exec();
    model->setQuery(qry1);
    mUi->nameBox->setModel(model);
}