#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "filelistdto.h"

#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent) :
                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&mManager, &QNetworkAccessManager::finished,
            this, &MainWindow::replyFinished);

    mManager.get(QNetworkRequest(
        QUrl(mServer + sep + QStringLiteral("api/filelist?cbor=1"))));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    if (reply == nullptr)
        return;

    qDebug() << "REPLY:" << reply->readAll();
}
