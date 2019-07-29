#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "filelistdto.h"

#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent) :
                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(5);
    ui->treeWidget->setHeaderLabels({
        tr("Name"), tr("Created"), tr("Modified"), tr("Size"), tr("Type")
    });

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
    const FileListDto dto(FileListDto::fromCbor(data));

    qDebug() << "REPLY:" << data;

    ui->userLabel->setText(dto.user());
    ui->directoryLabel->setText(dto.directory());

    const QString format(QStringLiteral("yyyy-MM-dd HH:mm"));

    QList<QTreeWidgetItem *> items;
    const auto &files = dto.files();
    for (const auto &file : files) {
        const QStringList values = {
            file.name, file.created.toString(format),
            file.modified.toString(format), QString::number(file.size),
            (file.isDirectory ? QStringLiteral("Dir") : QStringLiteral("File"))
        };
        items.append(new QTreeWidgetItem(static_cast<QTreeWidget*>(nullptr),
                                         values, 0));
    }

    ui->treeWidget->insertTopLevelItems(0, items);
}

void MainWindow::on_connectPushButton_clicked()
{
    mManager.get(QNetworkRequest(
        QUrl(ui->serverLineEdit->text() + sep + QStringLiteral("api/filelist?cbor=1"))));

}
