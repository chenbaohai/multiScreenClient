#include "smallscreen.h"
#include "ui_smallscreen.h"

#include <QPainter>
#include <QDebug>
#include "QDragEnterEvent"
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QMouseEvent>


SmallScreen::SmallScreen(QWidget *parent) :
    QWidget(parent), 
    ui(new Ui::SmallScreen)
{
    ui->setupUi(this);
    m_col=0;m_row=0;m_colspan=1;m_rowspan=1;
    m_baserow=m_basecol=-1;
    m_Used=true;    
    this->setAcceptDrops(true);
    this->setMouseTracking(true);
    m_displayid="";  
    m_hlayout=new QHBoxLayout(this);
    this->setLayout(m_hlayout);
    m_windowLayout=new WindowLayoutWidget;
    m_hlayout->addWidget(m_windowLayout);
    setWindowLayout(2,2);
}

SmallScreen::~SmallScreen()
{
    delete ui;
}

void SmallScreen::paintEvent(QPaintEvent *)
{
    if(m_displayid=="") return;
            QPainter painter(this);

    painter.setBrush(QBrush(Qt::lightGray));
    painter.drawRect(this->rect());

    painter.setPen(QColor(Qt::red));
    painter.drawText(this->rect(),Qt::AlignCenter,m_displayid);

//    QPainter paint(this);
//    paint.setRenderHint(QPainter::Antialiasing,true);
//    QLinearGradient linearGradient(rect().width(),rect().height(),0,0);
//    linearGradient.setSpread(QGradient::RepeatSpread);
//    linearGradient.setColorAt(0.0, Qt::lightGray);
//    linearGradient.setColorAt(0.2, Qt::lightGray);
//    linearGradient.setColorAt(0.8, Qt::lightGray);
//    linearGradient.setColorAt(1.0, Qt::lightGray);
//    paint.setBrush(QBrush(linearGradient));
//    paint.drawRect(rect());

}

void SmallScreen::setSpan(int rowspan, int colspan)
{
    m_rowspan=rowspan;
    m_colspan=colspan;
}

void SmallScreen::setRowCol(int row, int col)
{
    if(m_baserow==-1)
    {
        m_baserow=row;
        m_basecol=col;
    }
    m_row=row;
    m_col=col;
}



void SmallScreen::append(SmallScreen *w)
{
    this->m_widgets.append(w);
}

bool SmallScreen::append(QVector <SmallScreen *> value)
{
    if(!getLayoutArea(value)) return false;
    this->m_operates.append(value);
    return true;
}


bool SmallScreen::clear()
{
    bool bRslt=false;
    int index=m_operates.count();    
    if(index==0)
    {
        qDebug()<<"SmallScreen::clear() Failure";
        return false;
    }
    QVector<SmallScreen *> widgets= m_operates.at(index-1);
    foreach(SmallScreen *w,widgets)
    {
        w->setUsed(true);
        qDebug()<<"      "<<w->displayid();
        bRslt=true;
    }

    qDebug()<<"   remove before";
    foreach(LayoutArea area,this->m_layoutArea)
    {
        qDebug()<<"     area"<<area.row<<area.col<<area.rowspan<<area.colspan;
    }

    m_operates.remove(index-1);
    if(m_operates.count()==0)
    {
        this->m_rowspan=1;
        this->m_colspan=1;
        this->m_row=m_baserow;
        this->m_col=m_basecol;
    }
    else
    {
        LayoutArea area=m_layoutArea.at(index-2);
        this->m_rowspan=area.rowspan;
        this->m_colspan=area.colspan;
        this->m_row=area.row;
        this->m_col=area.col;        
    }
    m_layoutArea.remove(index-1);

    qDebug()<<"   remove after";
    foreach(LayoutArea area,this->m_layoutArea)
    {
        qDebug()<<"     area"<<area.row<<area.col<<area.rowspan<<area.colspan;
    }

    qDebug()<<"SmallScreen::clear()"<<this->displayid()<<this->m_row<<this->m_col<<this->m_rowspan<<this->m_colspan<<"m_operates.count:"<<m_operates.count();
    return bRslt;
}

void SmallScreen::setUsed(bool value)
{
    this->setVisible(value);
    m_Used=value;
}

bool SmallScreen::used()
{
    return this->m_Used;
}

int SmallScreen::row()
{
    return this->m_row;
}

int SmallScreen::col()
{
    return this->m_col;
}

int SmallScreen::rowspan()
{
    return this->m_rowspan;
}

int SmallScreen::colspan()
{
    return this->m_colspan;
}


void SmallScreen::dragEnterEvent(QDragEnterEvent *event)
{
//    this->setBackgroundRole(QPalette::Highlight);
    event->acceptProposedAction();
//    emit selectedSig(this);
}

void SmallScreen::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    QString app;
    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();
        for (int i = 0; i < urlList.size() && i < 32; ++i) {
            QString url = urlList.at(i).path();
            app += url;
        }
        app=app.remove(0,1);
        app.replace('/','\\');
    }

}


void SmallScreen::enterEvent(QEvent *)
{
    emit selectedSig(this);
}

void SmallScreen::setDisplayid(QString id)
{
    m_displayid=id;

}

QString SmallScreen::displayid()
{
    return m_displayid;
}

bool SmallScreen::getLayoutArea(QVector<SmallScreen *> widgets)
{

    //取得最小的、最大的边距

    bool bRslt=true;
//    int iMaxCol=-1;
//    int iMinrow=-1;

    int iRow=-1;
    int iCol=-1;

    int iRow1=-1;
    int iCol1=-1;


    int colspan=-1;
    int rowspan=-1;
    SmallScreen * w_min=NULL;
    SmallScreen * w_max=NULL;
    foreach(SmallScreen * w,widgets)
    {
        if(colspan==-1)
        {
            colspan=w->colspan();
            rowspan=w->rowspan();

            iRow=w->row()+w->rowspan();
            iCol=w->col()+w->colspan();

            iRow1=w->row()+w->rowspan();
            iCol1=w->col()+w->colspan();
            w_min=w;
            w_max=w;
        }
        else
        {
            colspan=w->colspan()>colspan?w->colspan():colspan;
            rowspan=w->rowspan()>rowspan?w->rowspan():rowspan;

            if(w->col()+w->colspan()>=iCol && w->row()+w->rowspan()>=iRow)
            {
                w_max=w;
                iCol=w->col()+w->colspan();
                iRow=w->row()+w->rowspan();
            }
            else if(w->col()+w->colspan()<iCol1 && w->row()+w->rowspan()<iRow1)
            {
                w_min=w;
                iCol1=w->col()+w->colspan();
                iRow1=w->row()+w->rowspan();
            }
        }
    }
    if(w_min==w_max) return false;

    SmallScreen *first=w_min;//(SmallScreen *)widgets.at(0);
    SmallScreen *second=w_max;//(SmallScreen *)widgets.at(widgets.count()-1);
    int minrow=first->row();
    int mincol=first->col();

    int maxrow=second->row();
    int maxcol=second->col();

    int lastrowspan=second->rowspan()+maxrow-minrow;
    int lastcolspan=second->colspan()+maxcol-mincol;

    if(lastrowspan<rowspan)
    {
        lastrowspan=rowspan;
        return false;
    }
    if(lastcolspan<colspan)
    {
        lastcolspan=colspan;
        return false;
    }

    foreach(SmallScreen * w,widgets)
    {
        if(w==this)
            continue;
        w->setUsed(false);
    }

    m_rowspan=lastrowspan;//second->row()-first->row()+1;
    m_colspan=lastcolspan;//second->col()-first->col()+1;

    m_row=minrow;
    m_col=mincol;
    qDebug()<<"after spicing"<<this->m_displayid<<m_row<<m_col<<m_rowspan<<m_colspan<<"displayid:"<<w_min->displayid()<<w_max->displayid();
    LayoutArea area(m_row,m_col,m_rowspan,m_colspan);
    m_layoutArea.append(area);
    return bRslt;
}

void SmallScreen::mouseReleaseEvent(QMouseEvent *event)
{ 
    QWidget::mouseReleaseEvent(event);
}

void SmallScreen::mousePressEvent(QMouseEvent *event)
{

}


//void SmallScreen::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    qDebug()<<"SmallScreen::dbclick";
//    QWidget::mouseDoubleClickEvent(event);
//}

void SmallScreen::setWindowLayout(int irow, int icol)
{
    m_windowLayout->ruleChangeLayout(irow,icol);
}



