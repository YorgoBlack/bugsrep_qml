#include "bugstreeitem.h"
#include <QtXml>
#include <QDebug>

BugsTreeItem::BugsTreeItem(QObject *parent) : QObject(parent), myTyp(BugsTreeItemTypes::devicetype)
{
}

BugsTreeItem::BugsTreeItem(const BugsTreeItem &other) : QObject(0)
{
    myText = other.myText;
    myTyp = other.myTyp;
}

BugsTreeItem::BugsTreeItem(QDomNode node) : QObject(0)
{
    QString n = node.attributes().namedItem("Name").nodeValue();
    QString typname = node.nodeName();
    myText = n;
    myTyp = BugsTreeItemTypes::unknown;
    if( typname == "devicetype") {
        myTyp = BugsTreeItemTypes::devicetype;
    } else if( typname == "symptom") {
        myTyp = BugsTreeItemTypes::symptom;
    } else if( typname == "defect") {
        myTyp = BugsTreeItemTypes::defect;
    } else if( typname == "correction") {
        myTyp = BugsTreeItemTypes::correction;
    }  else if( typname == "camedept") {
        myTyp = BugsTreeItemTypes::camedept;
    }
}

BugsTreeItem::BugsTreeItem(QString text, QString typname) : QObject(0)
{
    myText = text;
    myTyp = BugsTreeItemTypes::unknown;
    if( typname == "devicetype") {
        myTyp = BugsTreeItemTypes::devicetype;
    } else if( typname == "symptom") {
        myTyp = BugsTreeItemTypes::symptom;
    } else if( typname == "defect") {
        myTyp = BugsTreeItemTypes::defect;
    } else if( typname == "correction") {
        myTyp = BugsTreeItemTypes::correction;
    }  else if( typname == "camedept") {
        myTyp = BugsTreeItemTypes::camedept;
    }
}

BugsTreeItem::~BugsTreeItem()
{
}

QString BugsTreeItem::text()
{
    return myText;
}

void BugsTreeItem::setText(QString text)
{
    myText = text;
    emit textChanged();
}

int BugsTreeItem::typ()
{
    return myTyp;
}

QVariant BugsTreeItem::asQVariant() {
    QVariant dummy;
    dummy.setValue(this);
    return dummy;
}
