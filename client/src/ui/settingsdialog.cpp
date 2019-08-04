#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include "configs/config.h"

#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *parent) :
                                                  QDialog(parent),
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

    {
        Config config;
        // Save configuration options:
        //if (ui->storageDirPushButton->te)

        if (ui->serverUrlLineEdit->text() != config.serverUrl) {
            config.serverUrl = ui->serverUrlLineEdit->text();
            dirty = true;
        }

        config.dirty = dirty;
    }

    if (dirty) {
        qDebug() << "New config saved";
        emit finished(true);
    }
}

void SettingsDialog::on_storageDirPushButton_clicked()
{

}

void SettingsDialog::on_cloudUserPushButton_clicked()
{

}

void SettingsDialog::on_serverUrlLineEdit_editingFinished()
{

}
