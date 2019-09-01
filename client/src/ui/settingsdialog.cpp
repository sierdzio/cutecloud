#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QDir>
#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>

#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    bool dirty = false;

    const QString storage(ui->storageDirLineEdit->text());
    if (storage != mConfig.storagePath) {
        if (QFileInfo::exists(storage)) {
        mConfig.storagePath = storage;
        dirty = true;
        } else {
        // TODO: error - highlight in form!
        }
    }

    if (ui->serverUrlLineEdit->text() != mConfig.serverUrl) {
        mConfig.serverUrl = ui->serverUrlLineEdit->text();
        dirty = true;
    }

    // TODO: display user NAME but store user ID!
    if (ui->userComboBox->currentText() != mConfig.userId) {
        mConfig.userId = ui->userComboBox->currentText();
        dirty = true;
    }

    mConfig.dirty = dirty;

    if (dirty) {
        qDebug() << "New config saved";
        mConfig.save();
        emit finished(true);
    }
}

void SettingsDialog::showEvent(QShowEvent *event)
{
    mConfig.load();
    QDialog::showEvent(event);
}

void SettingsDialog::on_storageDirPushButton_clicked()
{
    const QString path(QFileDialog::getExistingDirectory(
        this, tr("Select cloud storage location"),
        QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0),
        QFileDialog::Option::ShowDirsOnly));
    ui->storageDirLineEdit->setText(path);
}

void SettingsDialog::on_serverUrlLineEdit_editingFinished()
{
    // TODO: check?
}

void SettingsDialog::on_serverPushButton_clicked()
{
    // TODO: connect
}

