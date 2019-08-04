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

// TODO: move to global header
#if !defined(CHECK)
//#if defined(DEBUG_BUILD)
#define CHECK(condition) if (!condition) qFatal("Check failed!")
//#else
//#define CHECK(condition) condition
//#endif
#endif

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void replyFinished(QNetworkReply *reply);
    void entryDoubleClicked(const QModelIndex &index);
    void configChanged(const bool configChanged);

    // TODO: do not use connectSlotsByName()!
    void on_connectPushButton_clicked();
    void on_backPushButton_clicked();
    void on_actionConfigure_Cutecloud_client_triggered();
    void on_actionAbout_Qt_triggered();

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
