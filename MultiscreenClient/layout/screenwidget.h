#ifndef SCREENWIDGET_H
#define SCREENWIDGET_H

#include <QWidget>
#include "rectangle.h"
#include "displayinfo.h"


namespace Ui {
class ScreenWidget;
}

class ScreenWidget : public QWidget
{
    Q_OBJECT
    
public:
    ScreenWidget(QWidget *parent = 0);
    ScreenWidget(int originalRow,int originalColumn, QWidget *parent = 0);
    ~ScreenWidget();
    int row();
    int column();
    int originalRow();
    int originalColumn();
    void setRow(int);
    void setColumn(int);
    int SpanRow();
    int SpanColumn();
    void setSpanRow(int);
    void setSpanColumn(int);
    bool isUsing();
    bool isMerge();
    bool isSelected();
    void MergeFlag(bool);
    void UsingFlag(bool);
    void setSelected(bool);
    void setCurMode(bool);
    QString outputId();
    void setOutPutId(QString);
    DisPlayInfo* disPlayInfo();
    void setDisPlayInfo(DisPlayInfo*);
    virtual ScreenWidget*  clone();
    QList<ScreenWidget* > * ContainScreenList();
    void setGrabHandle(HWND value);
    HWND grabHandle();
    void fixPosition();
    void returnToMainScreen();
protected:
    void mouseDoubleClickEvent(QMouseEvent * e);

    void paintEvent(QPaintEvent *);

    void enterEvent(QEvent *);
    void resizeEvent(QResizeEvent *);

    bool m_isSelected;

public slots:
    void changeMode(bool);

private slots:
    void captureSlot(QPixmap *);

signals:
    void changeSpanSignal(ScreenWidget* widget);
    void mouseEnterSig(ScreenWidget* widget);

private:
    int m_Row;
    int m_Column;
    int m_originalRow;
    int m_originalColumn;
    int m_RowSpan;
    int m_ColumnSpan;
    bool m_isUsing;
    QString m_OutputID;   //当前屏的输出口id
    bool m_isMerged;
    bool m_curMode;
    DisPlayInfo* m_disPlayInfo;
    QList<ScreenWidget* > m_ContainWidgetList;
    Ui::ScreenWidget *ui;
    HWND m_handle;
    QPixmap *m_pixmap;
    int m_timerid;

};

#endif // SCREENWIDGET_H
