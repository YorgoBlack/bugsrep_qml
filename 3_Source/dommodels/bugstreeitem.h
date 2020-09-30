#ifndef BUGSTREEITEM_H
#define BUGSTREEITEM_H

#include <QObject>
#include <QDomNode>

enum BugsTreeItemTypes
    { unknown = 0, devicetype, symptom, defect, correction, camedept };



class BugsTreeItem : public QObject
{
    Q_OBJECT


    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int typ READ typ NOTIFY typChanged)

public:

    explicit BugsTreeItem(QObject *parent = 0);
    BugsTreeItem(const BugsTreeItem &other);
    BugsTreeItem(QString text, QString typname);
    BugsTreeItem(QDomNode node);
    ~BugsTreeItem();

    QString text();
    void setText(QString text);

    int typ();

    QVariant asQVariant();

signals:
    void textChanged();
    void typChanged();

private:
    QString myText;
    BugsTreeItemTypes myTyp;
};

Q_DECLARE_METATYPE(BugsTreeItem)

#endif // BUGSTREEITEM
