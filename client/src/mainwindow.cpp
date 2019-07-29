#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "models/filelistmodel.h"

#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent) :
                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mModel = new FileListModel(this);

    ui->treeView->setModel(mModel);
//    ui->treeView->setHeaderLabels({
//        tr("Name"), tr("Created"), tr("Modified"), tr("Size"), tr("Type")
//    });

    connect(&mManager, &QNetworkAccessManager::finished,
            this, &MainWindow::replyFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    if (reply == nullptr)
        return;

    const QByteArray data(reply->readAll());
    mModel->setFileList(FileListDto::fromCbor(data));

    qDebug() << "REPLY:" << data;

    ui->userLabel->setText(mModel->fileList().user());
    ui->directoryLabel->setText(mModel->fileList().directory());
}

void MainWindow::on_connectPushButton_clicked()
{
    mManager.get(QNetworkRequest(
        QUrl(ui->serverLineEdit->text() + sep + QStringLiteral("api/filelist?cbor=1"))));

}
