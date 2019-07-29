#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPointer>
#include <QMainWindow>
#include <QNetworkAccessManager>

namespace Ui {
class MainWindow;
}

class QNetworkReply;
class FileListModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void replyFinished(QNetworkReply *reply);
    void on_connectPushButton_clicked();

private:
    const QString sep = QStringLiteral("/");

    Ui::MainWindow *ui;
    QPointer<FileListModel> mModel;

    QNetworkAccessManager mManager;
};

#endif // MAINWINDOW_H
