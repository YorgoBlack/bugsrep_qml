#include <QDir>
#include <QStandardPaths>
#include <QDateTime>

#include <QDebug>

#include "appconfig.h"

AppConfig::AppConfig(QObject *parent) : QObject(parent)
{
    QString path;

    settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "OWEN/BugsApp", "settings");
    settings->setIniCodec( "UTF-8" );
    path = QFileInfo( settings->fileName() ).dir().path() + "/bugsconfig.xml";

    if( settings->value("BugsConfigPath").isNull() ) {
        setDefaultBugsTree(path);
    }
    else {
        tryLoadBugsTree(settings->value("BugsConfigPath").toString() );
    }
    path = settings->value("BugsConfigPath", path).toString();
    settings->setValue("BugsConfigPath", path);

    path = settings->value("BugsRepPath", QStandardPaths::writableLocation(QStandardPaths::HomeLocation)).toString();
    settings->setValue("BugsRepPath", path);

    connect(&bugsTree,SIGNAL(modelUpdated(QDomDocument,int&)), this, SLOT(updateModel(QDomDocument,int&)));

}

bool AppConfig::setDefaultBugsTree(QString filepath) {
    QDomDocument doc;
    QString errMsg;
    int errline,errcolumn;

    QFile file(":/BugsConfig.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    if( !doc.setContent(&file,&errMsg,&errline,&errcolumn) ) {
        return false;
    }

    QFile ofile(filepath);
    if (!ofile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream stream(&ofile);
    stream.setCodec("UTF-8");
    stream << doc.toString();
    ofile.close();
    file.close();

    bugsTree.setContent(doc);

    return true;
}

void AppConfig::saveBugsToFile(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text) ) {
        emit alertMsg("Ошибка записи в файл " + filename + ":" + file.errorString());
        return;
    }

    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    bugsTree.doc().save(stream,4);
    file.close();

}

void AppConfig::loadBugsFromFile(QString filename) {
    QDomDocument doc;
    QString errMsg;
    int errline,errcolumn;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    }
    if( !doc.setContent(file.readAll(),&errMsg,&errline,&errcolumn) ) {
        qDebug() << errMsg << ", row:" << errline << ", column:" << errcolumn;
    }
    file.close();

    file.setFileName(settings->value("BugsConfigPath").toString());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream << doc.toString();
    file.close();
    qDebug() << "load from file";

    bugsTree.setContent(doc);
    emit modelSaved();

}

bool AppConfig::tryLoadBugsTree(QString filepath) {
    QDomDocument doc;
    QString errMsg;
    int errline,errcolumn;

    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setDefaultBugsTree(filepath);
        return false;
    }
    if( !doc.setContent(file.readAll(),&errMsg,&errline,&errcolumn) ) {
        qDebug() << errMsg << ", row:" << errline << ", column:" << errcolumn;
        bugsTree.empty();
        return false;
    }
    file.close();
    settings->setValue("BugsConfigPath", filepath);
    bugsTree.setContent(doc);
    emit modelSaved();
    return true;
}

bool AppConfig::checkBugsRepLocation(QString filepath) {
    QFile file(filepath);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        return false;
    }
    file.close();
    return true;
}

void AppConfig::updateModel(QDomDocument doc, int& result) {
// save
    QString path = settings->value("BugsConfigPath").toString();
    qDebug() << "saving model to file " + path;
    result = 1;
    QFile file( path );
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "error write file";
        return;
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    doc.save(stream,4);
    file.close();

    emit modelSaved();

    result = 0;
}

void AppConfig::writeToReport(QString deviceId, QString deviceType, QString symptom, QString defect, QString correction, QString camedept, QString comments) {

    QString header;
    QString repfile = settings->value("BugsRepPath").toString() + "/" + deviceType + ".csv";
    QFileInfo fi(repfile);
    if( !fi.exists() ) {
        header = QString::fromUtf8("Дата") + ";" +QString::fromUtf8("Время") + ";" + QString::fromUtf8("Источник") + ";";
        header +=  QString::fromUtf8("ID") + ";" + QString::fromUtf8("Проявление") + ";" + QString::fromUtf8("Причина") + ";" + QString::fromUtf8("Устранение");
        header += ";" + QString::fromUtf8("Комментарии");
    }
    else {
        header = "";
    }

    QFile file( repfile );
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << "error write report";
        emit alertMsg(QString("Ошибка записи в файл " + repfile));
        return;
    }

    QTextStream stream(&file);
    stream.setCodec("Windows-1251");

    QString line = (QDateTime::currentDateTime()).toString("d.M.yyyy") + ";" + (QDateTime::currentDateTime()).toString("h:m:s") + ";";
    line +=  camedept  + ";" + deviceId + ";" + symptom + ";";
    line +=  defect + ";" + correction + ";" + comments;
    if( header != "") {
        qDebug() << header;
        stream << "sep=;" << "\n";
        stream << header << "\n";
    }
    qDebug() << line;
    stream << line << "\n";
    file.close();
}
