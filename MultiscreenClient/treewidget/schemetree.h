#ifndef SCHEMETREE_H
#define SCHEMETREE_H

#include "basetreewidget.h"
//#include "scheme.h"
#include "schemeitem.h"
#include "schemexml.h"
typedef QList<SchemeItem*> SchemeList;

class SchemeTree : public BaseTreeWidget
{
    Q_OBJECT
public:
    explicit SchemeTree(QWidget *parent = 0);
    ~SchemeTree();


    virtual void buildUpTree();
    virtual void clearTreeInfo();
    void modifyItemToTree(SchemeItem*, int);
    void addItemToTree(SchemeItem*);
    bool deleteScheme(SchemeItem*, int);
    bool saveSchemeXml();
    SchemeList getSchemeList();
    SchemeItem* getScheme(int);
    bool testSchemeName(QString, int);
signals:
    void sendSchemeXmlSig(int, QString);
protected:
    void customContextMenuRequested(const QPoint &pos);

private:
    void fillTreeByScheme(QTreeWidgetItem*, SchemeItem*);
    void createTopTree();
    void append(SchemeItem*);
private:
    SchemeList m_schemeTreeList;
    QTreeWidgetItem* m_pItem;
    SchemeXml *m_schemeXml;
};

#endif // SCHEMETREE_H
