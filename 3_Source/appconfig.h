#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QGuiApplication>
#include <QApplication>

#include "dommodels/dommodel.h"

class AppConfig : public QObject
{
    Q_OBJECT

public:
    AppConfig(QObject *parent = 0);

    bool setDefaultBugsTree(QString filepath);
    Q_INVOKABLE bool tryLoadBugsTree(QString filepath);
    Q_INVOKABLE bool checkBugsRepLocation(QString filepath);

    Q_INVOKABLE QString bugsConfigPath() { return settings->value("BugsConfigPath").toString(); }
    Q_INVOKABLE QString bugsRepPath() { return settings->value("BugsRepPath").toString(); }
    Q_INVOKABLE void setBugsRepPath(QString path) { qDebug() << "rep:" << path; settings->setValue("BugsRepPath", path); }

    Q_INVOKABLE void saveBugsToFile(QString filename);
    Q_INVOKABLE void loadBugsFromFile(QString filename);

    Q_INVOKABLE void writeToReport(QString deviceId, QString deviceType, QString symptom, QString defect, QString correction, QString camedept, QString comments);

    Q_INVOKABLE QString getVersion() {return QApplication::applicationVersion();}

    DomModel bugsTree;


signals:
    void modelSaved();
    void alertMsg(QString msg);

public slots:
    void updateModel(QDomDocument doc, int &result);

private:
    QSettings *settings;
    QString author;

};


#endif // APPCONFIG_H
