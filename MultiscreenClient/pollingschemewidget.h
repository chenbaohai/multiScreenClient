#ifndef POLLINGSCHEMEWIDGET_H
#define POLLINGSCHEMEWIDGET_H

#include <QWidget>
#include <QModelIndex>
#include "schemeitem.h"
#include "group.h"
#include <QTreeWidgetItem>
#include "playscreen.h"

namespace Ui {
    class PollingSchemeWidget;
}

class PollingSchemeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PollingSchemeWidget(QWidget *parent = 0);
    ~PollingSchemeWidget();

    SchemeItem* msgUiToVar(SchemeItem*);
    void getWholeGroupList(GroupList);
    void initWidgetLayout();
    void changeScreenLayout(QList<BaseWidget*> *);
    bool compareEqual(PlayScreen*,PlayScreen*);
    void assignment(PlayScreen*,PlayScreen*);
protected:
    void showEvent(QShowEvent *);

signals:
    void sendCirculateSig(QString,bool);
    void sendPollingSchemeSig(int, QString);
public slots:
    void sendPollingSchemeSlot(int, QString);
    void createSchemeSlot();
    void saveSchemeSlot();
    void deleteSchemeSlot();
    void addGroupListSlot();
    void pressPollingSlot(QTreeWidgetItem*, int);
    void beginPollingScheme();
    void paintScreen(BaseWidget *);
    void configChangeSlot();
private slots:


    void on_pollingTreeWidget_doubleClicked(const QModelIndex &index);

    void on_saveSchemeBtn_clicked();

    void clickSlot(const QModelIndex &index);

private:
    GroupList   m_groupList;
    GroupList   m_curGroupList;
    GroupList   m_wholeGroupList;
    int         m_index;
    int        m_createFlag;
    SchemeItem  *m_pCurItem;
    Ui::PollingSchemeWidget *ui;
};

#endif // POLLINGSCHEMEWIDGET_H
