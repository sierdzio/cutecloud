#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "models/filelistmodel.h"

#include <QNetworkReply>
#include <QTimer>

#include <QTemporaryFile>
#include <QDesktopServices>

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

    QTimer::singleShot(10, this, [=]() {
        ui->treeView->header()->resizeSection(0, int(ui->treeView->width() * .4));
    });
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < mTempFiles.size(); ++i) {
        QFile::remove(mTempFiles.at(0));
    }

    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    if (reply == nullptr)
        return;

    const QByteArray data(reply->readAll());
    const QString filesUrl(sep + filesPrefix);
    qDebug() << "REPLY:" << reply->url();

    if (reply->url().path().startsWith(filesUrl)) {
        QTemporaryFile file;
        if (file.open()) {
            file.setAutoRemove(false);
            file.write(data);
            const QString fileName(file.fileName());
            mTempFiles.append(fileName);
            file.close();
            qInfo() << "Opening" << fileName;
            QDesktopServices::openUrl(fileName);
        } else {
            qWarning() << "File could not be opened!";
        }
    } else {
        mModel->setFileList(FileListDto::fromCbor(data));
        ui->userLabel->setText(mModel->fileList().user());
        ui->directoryLabel->setText(mModel->fileList().directory());
        ui->backPushButton->setEnabled(!ui->directoryLabel->text().isEmpty());
    }
}

void MainWindow::entryDoubleClicked(const QModelIndex &index)
{
    const FileInfo &info = mModel->fileInfo(index.row());
    if (info.isDirectory) {
        qDebug() << "Directory double clicked - open!";
        mManager.get(QNetworkRequest(
            QUrl(ui->serverLineEdit->text() + sep + mModel->fileList().apiPath()
                 + sep + mModel->fileList().directory()
                 + sep + info.name + proto)));
    } else {
        const QString path(ui->serverLineEdit->text() + sep
                           + filesPrefix + sep + mModel->fileList().apiPath() + sep
                           + info.name);
        qDebug() << "File double clicked - download and open!" << path;
        mManager.get(QNetworkRequest(QUrl(path)));
    }
}

void MainWindow::on_connectPushButton_clicked()
{
    mManager.get(QNetworkRequest(
        QUrl(ui->serverLineEdit->text() + sep + mModel->fileList().apiPath()
             + proto)));
}

void MainWindow::on_backPushButton_clicked()
{
    const QStringList path(ui->directoryLabel->text().split(sep));
    const QString backPath(path.mid(0, path.length() - 1).join(sep));
    const QString url(ui->serverLineEdit->text() + sep + mModel->fileList().apiPath()
                      + sep + backPath + proto);
    qDebug() << "Back URL" << url << "initial path:" << path;
    mManager.get(QNetworkRequest(QUrl(url)));
}
