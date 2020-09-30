#ifndef DOMMODEL_H
 #define DOMMODEL_H

#include <QAbstractItemModel>
#include <QStandardItem>
#include <QDomDocument>
#include <QModelIndex>
#include <QVariant>
#include <QDomNode>

#include "dommodels/treeitem.h"

 class DomModel : public QAbstractItemModel
 {
     Q_OBJECT

 public:
     DomModel(QObject *parent = 0);
     ~DomModel();

     QVariant data(const QModelIndex &index, int role) const;
     Qt::ItemFlags flags(const QModelIndex &index) const;
     QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;
     QModelIndex index(int row, int column,
                       const QModelIndex &parent = QModelIndex()) const;
     QModelIndex parent(const QModelIndex &child) const;
     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     int columnCount(const QModelIndex &parent = QModelIndex()) const;
     QHash<int, QByteArray> roleNames() const override;

     void setContent(QDomDocument node);
     void empty();
     void findall(QDomNode node, int offset);

     Q_INVOKABLE bool setValue(const QModelIndex &index, const QVariant &value);

     Q_INVOKABLE QVariantList getDevicesTypes();
     Q_INVOKABLE QVariantList getSymptoms(int devicetype);
     Q_INVOKABLE QVariantList getDefects(int devicetype, int symptom);
     Q_INVOKABLE QVariantList getCorrection(int devicetype, int symptom, int defect);
     Q_INVOKABLE QVariantList getCamedepts();

     Q_INVOKABLE int addDevicesType(int pos, QString text);
     Q_INVOKABLE int addSymptom(int devicetype, int pos, QString text, const QModelIndex &index);
     Q_INVOKABLE int addDefect(int devicetype, int symptom, int pos, QString text, QString text_correction, const QModelIndex &index);
     Q_INVOKABLE int addCamedepts(int pos, QString text);

     Q_INVOKABLE void delCamedepts(int pos);
     Q_INVOKABLE void delTreeItem(const QModelIndex &index);

     Q_INVOKABLE void editTreeItem(const QModelIndex &index, QString text, int typ);

     QDomNode rootNode();

     QDomDocument doc() { return document; }

signals:
    void modelUpdated(QDomDocument doc, int &result);
    void updDeviceTypes(QVariantList list);
    void updSymptoms(QVariantList list);
    void updDefects(QVariantList list);
    void updCameDepts(QVariantList list);

 private:
    void setupModelData(TreeItem *parent);
    QVariant newBugItem(QDomNode node);

     QHash<int, QByteArray> m_roleNameMapping;
     TreeItem *rootItem;
     QDomDocument document;
 };


 #endif
