#pragma once

#include "client/kimaiclient.h"

#include <QWidget>

namespace Ui {
class SettingsWidget;
}

namespace kemai::app {

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    SettingsWidget(QWidget* parent = nullptr);
    ~SettingsWidget() override;
    Ui::SettingsWidget* mUi         = nullptr;
    QString dkey;
    void populatingComboBox();
    QString k;
    

signals:
    void settingsSaved();
    void cancelled();
    void sendKey(QString key);
private:
    void loadSettings();
    void saveSettings();

    void onClientError(const QString& errorMsg);
    void onClientReply(const client::KimaiReply& reply);

    void onBtTestClicked();
    void onBtCancelClicked();
    void onBtSaveClicked();
    void on_nameBox_currentIndexChanged(const QString& arg1);
    void addUser();
    void editUser();

private:
    
    QAction* mActToggleTokenVisible = nullptr;
    // for connection testing
    QScopedPointer<client::KimaiClient> mKimaiClient;
};

} // namespace kemai::app
