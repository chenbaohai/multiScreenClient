#ifndef SMALLSCREEN_H
#define SMALLSCREEN_H

#include <QWidget>
#include "layoutarea.h"
#include "windowlayout.h"
#include <QHBoxLayout>

namespace Ui {
    class SmallScreen;
}


class SmallScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SmallScreen(QWidget *parent = 0);
    ~SmallScreen();
    void setSpan(int rowspan,int colspan);
    void setRowCol(int row,int col);
    void setUsed(bool value);
    void append(SmallScreen *);
    bool append(QVector <SmallScreen *> value);
    bool clear();
    bool used();

    int row();
    int col();
    int rowspan();
    int colspan();

    void setDisplayid(QString id);
    QString displayid();

    void setWindowLayout(int irow,int icol);

signals:
    void selectedSig(SmallScreen *);
protected:
    void paintEvent(QPaintEvent *);    
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);

    void enterEvent(QEvent *);
    void mouseReleaseEvent(QMouseEvent *);


    void mousePressEvent(QMouseEvent *);
//    void mouseDoubleClickEvent(QMouseEvent *);


private:
    Ui::SmallScreen *ui;    

    int m_col,m_row,m_colspan,m_rowspan;

    bool m_Used;

    QPixmap m_pixmap;
    QString m_displayid;

    int m_baserow;
    int m_basecol;
    QPoint m_globalPos;

    QHBoxLayout *m_hlayout;
    WindowLayoutWidget *m_windowLayout;

    QVector<SmallScreen *> m_widgets;
    QVector< QVector<SmallScreen *> > m_operates;
    QVector<LayoutArea> m_layoutArea;
private:

    bool getLayoutArea(QVector<SmallScreen *>);

    const QPoint & mapToRemoteGlobal(const QPoint& pos);

private:
    bool m_start; 

};


#endif // SMALLSCREEN_H
