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
    void entryDoubleClicked(const QModelIndex &index);
    void on_connectPushButton_clicked();

    void on_backPushButton_clicked();

private:
    const QString sep = QStringLiteral("/");
    const QString filesPrefix = QStringLiteral("files");
    const QString proto = QStringLiteral("?cbor=1");

    Ui::MainWindow *ui;
    QPointer<FileListModel> mModel;

    QNetworkAccessManager mManager;
    QStringList mTempFiles;
};

#endif // MAINWINDOW_H
