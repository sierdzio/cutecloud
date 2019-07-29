#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "models/filelistmodel.h"

#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mModel = new FileListModel(this);

    ui->treeView->setModel(mModel);

    connect(&mManager, &QNetworkAccessManager::finished,
            this, &MainWindow::replyFinished);

    connect(ui->treeView, &QTreeView::doubleClicked,
            this, &MainWindow::entryDoubleClicked);
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

void MainWindow::entryDoubleClicked(const QModelIndex &index)
{
    const FileInfo &info = mModel->fileInfo(index.row());
    if (info.isDirectory) {
        qDebug() << "Directory double clicked - open!";
        mManager.get(QNetworkRequest(
            QUrl(ui->serverLineEdit->text() + sep + mModel->fileList().path()
                 + sep + info.name + proto)));
    } else {
        qDebug() << "File double clicked - download and open!";
    }
}

void MainWindow::on_connectPushButton_clicked()
{
    mManager.get(QNetworkRequest(
        QUrl(ui->serverLineEdit->text() + sep + mModel->fileList().path()
             + proto)));
}
