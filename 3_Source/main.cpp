#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtQuick>
#include <QMessageBox>
#include <QException>

#include "dommodels/bugstreeitem.h"
#include "appconfig.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationVersion(QString(APP_VERSION));

    try {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    AppConfig appConfig(&engine);

    qmlRegisterType<BugsTreeItem>("yorgo.com", 1, 0, "BugsTreeItem");
    engine.rootContext()->setContextProperty("AppSettings", &appConfig);
    engine.rootContext()->setContextProperty("BugsTreeModel", &appConfig.bugsTree);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));



    return app.exec();
    }
    catch(QException e) {
        QMessageBox::critical(NULL, "title", e.what());
    }
}


