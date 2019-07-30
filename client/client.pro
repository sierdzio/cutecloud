
include(../milo/mlog/mlog.pri)
include(../milo/mconfig/mconfig.pri)
include(../api/api.pri)

TEMPLATE = app

QT = core gui network widgets

HEADERS += src/mainwindow.h src/models/filelistmodel.h

SOURCES += src/main.cpp src/mainwindow.cpp src/models/filelistmodel.cpp

FORMS += src/mainwindow.ui

CONFIG += ltcg c++14

# Provide version number to application
COMMIT = $$system(git rev-parse --short HEAD)

VERSION=0.0.1

HOST_MACHINE = $$[QMAKE_SPEC]
contains (HOST_MACHINE, .*win32.*) {
    BUILD_DATE=$$system(powershell -Command "Get-Date -format yyyy-MM-dd")
} else {
    BUILD_DATE = $$system(date +%Y-%m-%d)
}

APP_VERSION = "$$VERSION"
APP_NAME = "cutecloud-client-test-wasm"
COMPANY_NAME = "Cutecloud"
COMPANY_DOMAIN = "sierdzio.com"

# add defines
DEFINES += ClientAppVersion='"\\\"$$APP_VERSION\\\""'
DEFINES += ClientAppName='"\\\"$$APP_NAME\\\""'
DEFINES += CompanyName='"\\\"$$COMPANY_NAME\\\""'
DEFINES += CompanyDomain='"\\\"$$COMPANY_DOMAIN\\\""'
DEFINES += BuildDate=\\\"$$BUILD_DATE\\\"
DEFINES += GitCommit=\\\"$$COMMIT\\\"
