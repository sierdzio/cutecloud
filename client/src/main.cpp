#include <QApplication>
#include <QLoggingCategory>

#include "mlog.h"

#include "mainwindow.h"

Q_LOGGING_CATEGORY(coreMain, "core.main")

int main(int argc, char *argv[]) {
    MLog::instance();

    QApplication app(argc, argv);
    app.setApplicationVersion(ClientAppVersion);
    app.setOrganizationName(CompanyName);
    app.setOrganizationDomain(CompanyDomain);
    app.setApplicationName(ClientAppName);

    qCInfo(coreMain) << "\nName:" << app.applicationName()
                     << "\nOrganisation:" << app.organizationName()
                     << "\nDomain:" << app.organizationDomain()
                     << "\nVersion:" << app.applicationVersion()
                     << "\nSHA:" << GitCommit
                     << "\nBuild date:" << BuildDate;

    MainWindow w;
    w.show();

    return app.exec();
}
