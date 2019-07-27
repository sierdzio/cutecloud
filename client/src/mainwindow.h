#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>

namespace Ui {
class MainWindow;
}

class QNetworkReply;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void replyFinished(QNetworkReply *reply);

private:
    const QString mServer = QStringLiteral("http://localhost:3000");
    const QString sep = QStringLiteral("/");

    Ui::MainWindow *ui;
    QNetworkAccessManager mManager;
};

#endif // MAINWINDOW_H
