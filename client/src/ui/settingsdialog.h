#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "configs/config.h"

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

signals:
    void finished(const bool configChanged) const;

protected:
    void showEvent(QShowEvent *event) final;

private slots:
    void on_buttonBox_accepted();
    void on_storageDirPushButton_clicked();
    void on_serverUrlLineEdit_editingFinished();
    void on_serverPushButton_clicked();

private:
    Ui::SettingsDialog *ui;
    Config mConfig;
};

#endif // SETTINGSDIALOG_H
