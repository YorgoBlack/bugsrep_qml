#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QDomNode>

//! [0]
class TreeItem
{
public:
    explicit TreeItem(QDomNode &node, const QVariant data, TreeItem *parentItem = 0);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    void removeChild(int row);
    QVariant data(int column) const;
    int row() const;
    TreeItem *parentItem();
    QDomNode node() {return m_node;}

private:
    QList<TreeItem*> m_childItems;
    QVariant m_itemData;
    TreeItem *m_parentItem;
    QDomNode m_node;
};
//! [0]

#endif // TREEITEM_H
