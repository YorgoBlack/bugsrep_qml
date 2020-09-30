
#include <QStringList>
#include <QDebug>

#include "treeitem.h"

//! [0]
TreeItem::TreeItem(QDomNode &node, const QVariant data, TreeItem *parent)
{
    m_parentItem = parent;
    m_itemData = data;
    m_node = node;
}
//! [0]

//! [1]
TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}
//! [1]

//! [2]
void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}
//! [2]

//! [3]
TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}
//! [3]

//! [4]
int TreeItem::childCount() const
{
    return m_childItems.isEmpty() ? 0 :  m_childItems.count();
}
//! [4]

//! [5]
int TreeItem::columnCount() const
{
    return 1;
    //return m_itemData.count();
}
//! [5]

//! [6]
QVariant TreeItem::data(int column) const
{
    return m_itemData;
    //return m_itemData.value(column);
}
//! [6]

//! [7]
TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}
//! [7]

//! [8]
int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
//! [8]

void TreeItem::removeChild(int row) {
    if( row < childCount() ) {
        m_childItems.removeAt(row);
    }
}
