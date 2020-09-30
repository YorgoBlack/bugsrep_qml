#include <QtXml>
#include <QDebug>
#include "treeitem.h"
#include "dommodel.h"
#include "bugstreeitem.h"

 DomModel::DomModel(QObject *parent)
     : QAbstractItemModel(parent)
 {
    QStringList roles = {"device","defect"};
    for(int i=0; i<roles.count(); i++)  {
        m_roleNameMapping[Qt::UserRole + 1 + i] = roles[i].toUtf8();
    }
    empty();
 }


 DomModel::~DomModel()
 {
     delete rootItem;
 }

 void DomModel::setContent(QDomDocument doc) {

     document = doc;
     QDomNode r = doc.namedItem("root").firstChild();
     if( rootItem ) {
        if( rootItem->childCount() > 0 ) {
            emit this->beginRemoveRows(QModelIndex(),0,rootItem->childCount());
        }
        else {
            emit this->beginRemoveRows(QModelIndex(),0,0);
        }
        emit this->endRemoveRows();
     }

     rootItem = new TreeItem(r, newBugItem(r), 0);
     setupModelData(rootItem);

     emit this->beginInsertRows(QModelIndex(),0,rootItem->childCount());
     emit this->endInsertRows();

     QDomNode docroot = (rootItem->node()).parentNode();
     QDomNode camdepts = docroot.firstChild().nextSibling();

     QVariantList list;
     for(int i=0; i < camdepts.childNodes().count(); i++) {
         list << camdepts.childNodes().at(i).attributes().namedItem("Name").nodeValue();
     }
     emit updCameDepts(list);
     QVariantList list2;
     for(int i=0; i < rootItem->node().childNodes().count(); i++) {
         list2 << rootItem->node().childNodes().at(i).attributes().namedItem("Name").nodeValue();
     }

     emit updDeviceTypes(list2);

     //findall(rootItem->node(), 0);
 }

 void DomModel::empty() {
    QDomDocument doc= QDomDocument("bugs");
    QDomElement root = document.createElement("root");
    QDomElement typs = document.createElement("devicestypes");
    QDomElement depts = document.createElement("camedepts");
    doc.appendChild(root);
    root.appendChild(typs);
    root.appendChild(depts);
    QDomNode r = doc.namedItem("root").firstChild();
    rootItem = new TreeItem(r, newBugItem(r), 0);
 }

 void DomModel::setupModelData(TreeItem *parent) {
    QDomNode child = parent->node().firstChild();
    while( !child.isNull() ) {
        TreeItem *item = new TreeItem(child, newBugItem(child), parent);
        parent->appendChild(item);
        setupModelData(item);
        child = child.nextSibling();
    }
 }

 void DomModel::findall(QDomNode node, int offset) {
    qDebug() << offset << ": " << node.attributes().namedItem("Name").nodeValue();
    QDomNode child = node.firstChild();
    while(!child.isNull() ) {
        findall(child,offset + 1);
        child = child.nextSibling();
    }
 }

 QVariant DomModel::newBugItem(QDomNode node) {
     QString n = node.attributes().namedItem("Name").nodeValue();
     QString t = node.nodeName();
     BugsTreeItem *i = new BugsTreeItem(n,t);
     QVariant v;
     v.setValue(i);
     return v;
 }


 QHash<int, QByteArray> DomModel::roleNames() const
 {
     return m_roleNameMapping;
 }


 int DomModel::columnCount(const QModelIndex &/*parent*/) const
 {
     return m_roleNameMapping.size();
 }

 QVariant DomModel::data(const QModelIndex &index, int role) const
 {
    if (!index.isValid()) {
         return "";
    }
    if ( !m_roleNameMapping.contains(role) ) {
         return "";
    }

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    //qDebug() << index.row() << " " << index.column();

    if( m_roleNameMapping[role] == "device") {
        return item->data(0);
    }
    else if( m_roleNameMapping[role] == "defect") {
        BugsTreeItem *bug = new BugsTreeItem( item->node() );
        if( bug->typ() == 3 ) {
            return item->child(0)->data(0);
        }
        else {
            return QVariant();
        }
    }
    else {
        return QVariant();
    }


 }

 void DomModel::editTreeItem(const QModelIndex &index, QString text, int typ) {
     int result;


     TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
     QVariant v = item->data(0);
     BugsTreeItem *t = qvariant_cast<BugsTreeItem*> (v);

     qDebug() << t->typ();
     if( typ == 4 ) {
         item = item->child(0);
         t = qvariant_cast<BugsTreeItem*> (item->data(0));
     }

     qDebug() << t->text();

     t->setText(text);
     item->node().attributes().namedItem("Name").setNodeValue(text);

     emit modelUpdated(document, result);
     emit this->dataChanged(index,index);

 }

 bool DomModel::setValue(const QModelIndex &index, const QVariant &value) {

     TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
     QDomNode node = item->node();
     QDomElement e = document.createElement(node.nodeName());
     int result;

     qDebug() << "setValue";
     e.setAttribute("Name",value.toString());
     node.parentNode().replaceChild(e,node);

     emit modelUpdated(document, result);
     emit this->dataChanged(QModelIndex(),QModelIndex());

     return result == 0;
 }


 Qt::ItemFlags DomModel::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return Qt::ItemIsEnabled;

     return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 }

 QVariant DomModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
 {
     if (orientation == Qt::Horizontal && m_roleNameMapping.contains(role) ) {
         switch (section) {
             case 0:
                 return tr("Name");
             case 1:
                 return tr("Attributes");
             case 2:
                 return tr("Value");
             default:
                 return QVariant();
         }
     }

     return QVariant();
 }

 QModelIndex DomModel::index(int row, int column, const QModelIndex &parent)
             const
 {
     if (!hasIndex(row, column, parent))
         return QModelIndex();

     TreeItem *parentItem;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<TreeItem*>(parent.internalPointer());

     TreeItem *childItem = parentItem->child(row);
     if (childItem) {
         //qDebug() << childItem->node().attributes().namedItem("Name").nodeValue() << " r:c " << row << " " << column;
         return createIndex(row, column, childItem);
     }
     else
         return QModelIndex();
 }

 QModelIndex DomModel::parent(const QModelIndex &index) const
 {
     if (!index.isValid())
         return QModelIndex();

     TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
     TreeItem *parentItem = childItem->parentItem();

     if (parentItem == rootItem)
         return QModelIndex();

     //qDebug() << parentItem->node().attributes().namedItem("Name").nodeValue() << " row " << parentItem->row();
     return createIndex(parentItem->row(), 0, parentItem);
 }

 int DomModel::rowCount(const QModelIndex &parent) const
 {
     TreeItem *parentItem;

     if (!parent.isValid())
         parentItem = rootItem;
     else
         parentItem = static_cast<TreeItem*>(parent.internalPointer());

     int cnt = parentItem->node().nodeName() == "defect" ? 0 : parentItem->node().childNodes().count();

     //qDebug() << parentItem->node().attributes().namedItem("Name").nodeValue() << " row count " << cnt;

     return cnt;
 }

 QVariantList DomModel::getCamedepts() {
    QVariantList list;
    QDomNode docroot = (rootItem->node()).parentNode();
    QDomNode root = docroot.firstChild().nextSibling();
    for(int i=0; i<root.childNodes().count(); i++) {
        QDomNode node = root.childNodes().at(i);
        list.append(node.attributes().namedItem("Name").nodeValue());
    }
    return list;
 }

 QVariantList DomModel::getDevicesTypes() {
     QVariantList list;
     QDomNode root = rootItem->node();
     for(int i=0; i<root.childNodes().count(); i++) {
        QDomNode node = root.childNodes().at(i);
        list.append(node.attributes().namedItem("Name").nodeValue());
     }
     return list;
 }

 QVariantList DomModel::getSymptoms(int devicetype) {

     if( devicetype < 0 ) {
         return QVariantList({""});
     }

     QVariantList list;
     QDomNode root = rootItem->node();
     list.append("");

     if( root.childNodes().count() > devicetype ) {
         QDomNode symptoms = root.childNodes().at(devicetype);

         for(int i=0; i<symptoms.childNodes().count(); i++) {
            QDomNode node = symptoms.childNodes().at(i);
            list.append(node.attributes().namedItem("Name").nodeValue());
        }
     }
     return list;
 }

 QVariantList DomModel::getDefects(int devicetype, int symptom) {

    if( devicetype < 0 || symptom < 1 ) {
        return QVariantList({""});
    }

    QVariantList list;
    QDomNode root = rootItem->node();
    if( root.childNodes().count() > devicetype  ) {
        QDomNode symptoms = root.childNodes().at(devicetype);
        symptom--;
        if( symptoms.childNodes().count() > symptom ) {
            QDomNode defects = symptoms.childNodes().at(symptom);
            list.append("");
            for(int i=0; i<defects.childNodes().count(); i++) {
               QDomNode node = defects.childNodes().at(i);
               list.append(node.attributes().namedItem("Name").nodeValue());
           }
        }
    }
    return list;
}
QVariantList DomModel::getCorrection(int devicetype, int symptom, int defect) {

     if( devicetype < 0 || symptom < 1  || defect < 1) {
         return QVariantList({""});
     }
     QVariantList list;
     QDomNode root = rootItem->node();
     if( root.childNodes().count() > devicetype  ) {
         QDomNode symptoms = root.childNodes().at(devicetype);
         symptom--;
         if( symptoms.childNodes().count() > symptom ) {
             QDomNode defects = symptoms.childNodes().at(symptom);
             defect--;
             if( defects.childNodes().count() > defect ) {
                 QDomNode node = defects.childNodes().at(defect);
                 node = node.firstChild();
                 list.append(node.attributes().namedItem("Name").nodeValue());
             }
        }
     }

    return list;
}

int DomModel::addDevicesType(int pos, QString text) {
    int result;
    QDomElement d = document.createElement("devicetype");
    d.setAttribute("Name",  text);
    emit this->beginInsertRows(QModelIndex(),rootItem->childCount(),rootItem->childCount());
    rootItem->appendChild( new TreeItem(d, newBugItem(d), rootItem) );
    rootItem->node().appendChild(d);
    emit this->endInsertRows();

    emit modelUpdated(document, result);
    emit updDeviceTypes( getDevicesTypes() );

    return result;
}

int DomModel::addSymptom(int devicetype, int pos, QString text, const QModelIndex &index) {
    int result;
    TreeItem *item = NULL;
    QDomElement d = document.createElement("symptom");
    d.setAttribute("Name",  text);
    if( devicetype == -1 ) {
        item = static_cast<TreeItem*>(index.internalPointer());
        devicetype = item->row();
    } else if( devicetype < rootItem->childCount() ) {
        item = rootItem->child(devicetype);
    }
    if( item != NULL ) {
        emit this->beginInsertRows( createIndex(devicetype,0,item),item->childCount(),item->childCount());
        item->appendChild( new TreeItem(d, newBugItem(d), item) );
        item->node().appendChild(d);
        emit this->endInsertRows();
        emit modelUpdated(document, result);

        QVariantList list;
        list.append("");
        for(int i=0; i<item->node().childNodes().count(); i++) {
            QDomNode node = item->node().childNodes().at(i);
            list.append(node.attributes().namedItem("Name").nodeValue());
        }

        emit updSymptoms( list );
    }
    return result;
}

int DomModel::addDefect(int devicetype, int symptom, int pos, QString text, QString text_correction, const QModelIndex &index) {
    int result;
    TreeItem *item = NULL;
    QDomElement d = document.createElement("defect");
    d.setAttribute("Name",  text);
    QDomElement corr = document.createElement("correction");
    corr.setAttribute("Name",  text_correction);

    qDebug() << "add defect" << devicetype << symptom;
    if( devicetype == -1 || symptom == -1 ) {
        item = static_cast<TreeItem*>(index.internalPointer());
        devicetype = item->row();
    }
    else if( devicetype < rootItem->childCount() ) {
        if( symptom < rootItem->child(devicetype)->childCount() ) {
            item = rootItem->child(devicetype)->child(symptom);
        }
    }
    if( item != NULL ) {

        emit this->beginInsertRows( createIndex(devicetype,0,item),item->childCount(),item->childCount());

        TreeItem *item_def = new TreeItem(d, newBugItem(d), item);
        item->appendChild( item_def );
        item_def->appendChild( new TreeItem(corr, newBugItem(corr), item_def) );
        item->node().appendChild(d);
        item_def->node().appendChild(corr);

        emit this->endInsertRows();
        emit modelUpdated(document, result);

        QVariantList list;
        list.append("");
        for(int i=0; i<item->node().childNodes().count(); i++) {
            QDomNode node = item->node().childNodes().at(i);
            list.append(node.attributes().namedItem("Name").nodeValue());
        }
        emit updDefects( list );
    }

    return result;
}


int DomModel::addCamedepts(int pos, QString text) {
    int result;
    QDomNode docroot = (rootItem->node()).parentNode();
    QDomNode root = docroot.firstChild().nextSibling();

    QDomElement d = document.createElement("camedept");
    d.setAttribute("Name",  text);

    root.appendChild(d);

    emit modelUpdated(document, result);
    return result;
}


void DomModel::delTreeItem(const QModelIndex &index) {
    int result;

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    if( item != NULL ) {
        TreeItem *parent = item->parentItem();

        if(  parent != NULL ) {
            QModelIndex index = parent == rootItem ? QModelIndex() : createIndex(parent->row(),0,parent);
            qDebug() << "r " << item->row();
            emit beginRemoveRows(index, item->row(), item->row());
            qDebug() << parent->node().attributes().namedItem("Name").nodeValue();
            qDebug() << item->node().attributes().namedItem("Name").nodeValue();
            parent->node().removeChild( item->node() );
            parent->removeChild( item->row() );
            emit endRemoveRows();
            emit modelUpdated(document, result);
            emit dataChanged(QModelIndex(),QModelIndex());
            emit updDeviceTypes( getDevicesTypes() );
        }
    }

}

void DomModel::delCamedepts(int pos) {
    int result;
    QDomNode docroot = (rootItem->node()).parentNode();
    QDomNode root = docroot.firstChild().nextSibling();

    if( pos < root.childNodes().count() ) {
        QDomNode node = root.childNodes().at(pos);
        root.removeChild(node);

        QVariantList list;
        for(int i=0; i< root.childNodes().count(); i++) {
            list << root.childNodes().at(i).attributes().namedItem("Name").nodeValue();
        }

        emit modelUpdated(document, result);
        emit updCameDepts(list);
    }
}

QDomNode DomModel::rootNode() {
    return rootItem->node();
}
