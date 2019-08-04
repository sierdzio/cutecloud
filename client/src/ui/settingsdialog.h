#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

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

private slots:
    void on_buttonBox_accepted();
    void on_storageDirPushButton_clicked();
    void on_cloudUserPushButton_clicked();
    void on_serverUrlLineEdit_editingFinished();

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
