#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

namespace Ui {
class BaseWidget;
}

class BaseWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit BaseWidget(QWidget *parent = 0);
    ~BaseWidget();

    int row();
    int column();
    void setRow(int);
    void setColumn(int);
    int SpanRow();
    int SpanColumn();
    void setSpanRow(int);
    void setSpanColumn(int);
    int originalRow();
    int originalColumn();
    int originalSpanRow();
    int originalSpanColumn();
    void setOriginalRow(int);
    void setOriginalColumn(int);
    void setOriginalSpanRow(int);
    void setOriginalSpanColumn(int);
    void saveOldPos();
    void restoreOldPos();
    bool useflag();
    void setUseflag(bool);
    bool select();
    void setDoubleClick(bool);
    bool getDoubleClick();
//    bool mergeFlag();
//    void setMergeFlag(bool);
    virtual BaseWidget* clone();
    QString& displayId();
    virtual void setDisplayid(const QString& id);
    void  setSelected(bool);
    virtual void cancelDisPlayid();

    void setPaintFlag(bool flag);
    void enterEvent(QEvent *);

    QString m_displayId;
    bool m_paintFlag;
protected:
    void paintEvent(QPaintEvent *);
signals:
    void changeSpanSignal(BaseWidget*);
    void mouseEnterSig(BaseWidget*);
    void mousePressSig(BaseWidget*);
private:
    int m_Row;
    int m_Column;
    int m_RowSpan;
    int m_ColumnSpan;
    int m_originalRow;
    int m_originalColumn;
    int m_originalRowSpan;
    int m_originalColSpan;
    bool m_useFlag;
    bool m_mergeFlag;
    bool m_selected;
    bool m_doubleClickFlag;
private:
    Ui::BaseWidget *ui;
};

#endif // BASEWIDGET_H
