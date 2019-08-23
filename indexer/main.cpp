#include <QCoreApplication>
#include <QLoggingCategory>
#include <QCommandLineParser>
#include <QElapsedTimer>

#include "mlog.h"

#include "fileindex.h"

Q_LOGGING_CATEGORY(coreMain, "core.main")

#define cTr QCoreApplication::translate

int main(int argc, char *argv[]) {
    MLog::instance();

    QCoreApplication app(argc, argv);
    app.setApplicationVersion(IndexerAppVersion);
    app.setOrganizationName(CompanyName);
    app.setOrganizationDomain(CompanyDomain);
    app.setApplicationName(IndexerAppName);

    //qCInfo(coreMain) << "\nName:" << app.applicationName()
    //                 << "\nOrganisation:" << app.organizationName()
    //                 << "\nDomain:" << app.organizationDomain()
    //                 << "\nVersion:" << app.applicationVersion()
    //                 << "\nSHA:" << GitCommit
    //                 << "\nBuild date:" << BuildDate;

    const QLatin1String target("path");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();
    const auto ctx = "main";
    parser.addPositionalArgument(target, cTr(ctx, "Directory to index"));
    parser.process(app);

    const QStringList args = parser.positionalArguments();

    if (args.isEmpty()) {
        qFatal("You have to specify a path!");
    }

    const QString path(args.at(0));

    {
        qInfo() << "Checking meta data only" << path;
        QElapsedTimer timer;
        timer.start();
        const auto indexes = FileIndex::directory(
            path, FileIndex::Mode::MetaDataIndex);
        qInfo() << "Meta data check took" << timer.elapsed() << "milliseconds";
        qInfo().noquote() << FileIndex::toString(indexes);
    }

    {
        qInfo() << "Checking file data only" << path;
        QElapsedTimer timer;
        timer.start();
        const auto indexes = FileIndex::directory(
            path, FileIndex::Mode::FileContentsIndex);
        qInfo() << "File contents check took" << timer.elapsed()
                << "milliseconds";
        qInfo().noquote() << FileIndex::toString(indexes);
    }

    qInfo() << "Done, bye!";

    return 0; //app.exec();
}
