#include "walllayout.h"
#include "ui_walllayout.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QUrl>
#include <qdom.h>
#include <QFile>



WallLayout::WallLayout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WallLayout)
{
    ui->setupUi(this);
    m_curWidget=NULL;
    m_splicing=false;
    m_doubleClicked=false;
    m_layout=NULL; 
    this->setAcceptDrops(true);
    setMouseTracking(true);

}

WallLayout::~WallLayout()
{
    delete ui;
}

void WallLayout::createLayout(int row, int col)
{    
    reCreateLayout();
    qDeleteAll(m_laywidgets);
    m_laywidgets.clear();
    for(int i=0;i<row;i++)
    {
        for(int j=0; j<col; j++)
        {
            SmallScreen *smallwall = new SmallScreen();
            smallwall->setMinimumSize(40,40);
            connect(smallwall,SIGNAL(selectedSig(SmallScreen*)),this,SLOT(selectedSlot(SmallScreen*)));
            smallwall->setRowCol(i,j);
            m_layout->addWidget(smallwall,i,j,1,1);
            smallwall->setDisplayid(QString::number(j+i*row+1));
            m_laywidgets.append(smallwall);
        }
    } 
}

void WallLayout::mousePressEvent(QMouseEvent *e)
{
    m_curindex=-1;
    m_moved=false;
    m_draged=false;
    if(m_splicing)        
        m_rectfrm.show();
    m_startPoint=e->pos();
    m_curindex=getWidgetIndexByPosition(e->pos());
    this->update();
}

void WallLayout::mouseMoveEvent(QMouseEvent *e)
{    
    if(m_splicing)
    {
        m_endPoint=e->pos();

        QPoint gPointX;
        if (m_endPoint.x()>=m_startPoint.x())
        {
            if(m_endPoint.y()>=m_startPoint.y())
                gPointX =  mapToGlobal(m_startPoint);
            else
                gPointX =  mapToGlobal(QPoint(m_startPoint.x(),m_endPoint.y()));
        }
        else
        {
            if(m_endPoint.y()>=m_startPoint.y())
                gPointX =  mapToGlobal(QPoint(m_endPoint.x(),m_startPoint.y()));
            else
                gPointX =  mapToGlobal(m_endPoint);
        }

         m_rectfrm.setGeometry(QRect(gPointX,QSize(qAbs(m_endPoint.x()-m_startPoint.x()),qAbs(m_endPoint.y()-m_startPoint.y()))));

         QPoint topPoint=mapFromGlobal(gPointX);
         QRect rect(topPoint,m_rectfrm.geometry().size());
         m_selrect=rect;
    }
    else
    {
        if (e->buttons() & Qt::LeftButton)
        {
            int distance = (e->pos() - m_startPoint).manhattanLength();
            if (distance >= QApplication::startDragDistance())
            {
                m_draged=true;
//                this->setCursor(Qt::DragCopyCursor);
            }
        }
//        this->setCursor(Qt::CrossCursor);
    }
}

void WallLayout::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_splicing)
    {
        m_rectfrm.setGeometry(0,0,0,0);
        m_rectfrm.hide();
        m_endPoint=e->pos();        
        if(m_selrect.width()>5 || m_selrect.height()>5)
            calucateSplicingRect();
    }
    else
    {
        if(!m_draged) return;
        int selectIndex=getWidgetIndexByPosition(e->pos());
        this->setCursor(Qt::ArrowCursor);
//        if(selectIndex!=-1 && selectIndex!=m_curindex)
//        {
//            swap(selectIndex,m_curindex);
////            m_laywidgets.swap(m_curindex,selectIndex);
////            reLayout();
//        }
    }

}

void WallLayout::paintEvent(QPaintEvent *)
{ 
    if(m_curWidget)
    {
        QPainter painter(this);
        painter.setPen(QPen(Qt::red,2,Qt::SolidLine,Qt::RoundCap));
        painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
        painter.drawRect(m_curWidget->x(),
                         m_curWidget->y(),
                         m_curWidget->width(),
                         m_curWidget->height());
    }
}

void WallLayout::calucateSplicingRect()
{ 
    m_indexs.clear();
    for(int i=0;i<m_laywidgets.count();i++)
    { 
        SmallScreen *widget=qobject_cast<SmallScreen *>(m_laywidgets.at(i));
        if (!widget->used()) continue;





//        QList<QPoint> points;
//        points.append(QPoint(widget->geometry().topLeft()));
//        points.append(QPoint(widget->geometry().topRight()));
//        points.append(QPoint(widget->geometry().bottomLeft()));
//        points.append(QPoint(widget->geometry().bottomRight()));


//        foreach(QPoint point,points)
//        {
//            if(m_rectfrm.geometry().contains(point))
//            {
//                m_indexs.append(i);
//                qDebug()<<"                     CONTAINERS:"<<i;
//                break;
//            }
//        }

        //通过widget的上下、左右条边是否有其中的2条坐落在选择框中

        int widgetLeft=widget->geometry().x();
        int widgetRight=widget->geometry().x()+widget->geometry().width();
        int widgetTop=widget->geometry().y();
        int widgetBottom=widget->geometry().y()+widget->geometry().height();

        int rectTop=m_selrect.y();
        int rectBottom=m_selrect.bottomLeft().y();

        if((widgetLeft>m_selrect.x() && widgetLeft<m_selrect.topRight().x()
            || widgetRight>m_selrect.x()&&widgetRight<m_selrect.topRight().x()
            || widgetLeft<m_selrect.x() && widgetRight>m_selrect.topRight().x())
            &&
            (rectTop>widgetTop && rectTop<widgetBottom
             || rectBottom>widgetTop && rectBottom<widgetBottom
             || rectTop<widgetTop && rectBottom>widgetBottom)
           )
        {
//            if(widget!=m_curWidget)
            {
//                qDebug()<<"                     CONTAINERS:"<<i;
                m_indexs.append(i);
            }
        }
    }
    m_selrect.setSize(QSize(0,0));
    if(splicing())
        reLayout();
}

void WallLayout::setSplicing(bool value)
{
    m_splicing=value;  
}

void WallLayout::reLayout()
{    
    reCreateLayout();
    for(int i=0;i<m_laywidgets.count();i++)
    {
        SmallScreen *w=qobject_cast<SmallScreen *>(m_laywidgets.at(i));
        if(!w->used())
            continue;
        m_layout->addWidget(w,w->row(),w->col(),w->rowspan(),w->colspan());
//        qDebug()<<"WallLayout::reLayout"<<w->displayid()<<w->row()<<w->col()<<w->rowspan()<<w->colspan();
    }

    this->update();
}

bool WallLayout::splicing()
{
    if(m_indexs.count()<=1) return false;
    SmallScreen *cur=qobject_cast<SmallScreen *>(m_curWidget);

    QVector<SmallScreen *> widgets;
    for(int i=0;i<m_indexs.count();i++)
    {
        int index=m_indexs.at(i);
        SmallScreen *w=qobject_cast<SmallScreen *>(m_laywidgets.at(index));
        widgets.append(w);

    }
    return cur->append(widgets);
}

bool WallLayout::unsplicing()
{
    SmallScreen *cur=qobject_cast<SmallScreen *>(m_curWidget);
    return cur->clear();
}

void WallLayout::clear()
{
    m_indexs.clear();
}

void WallLayout::changeIndex(int first, int second)
{
    m_laywidgets.swap(first,second);
}

void WallLayout::mouseDoubleClickEvent(QMouseEvent *e)
{
    qDebug()<<"WallLayout::mouseDoubleClickEvent";
    if(!m_splicing)
    {
        if(e->button() == Qt::LeftButton)
        {
            if(!m_doubleClicked)
                singleWidgetMaximized();
            else
                showAllWidget();
        }
        return;
    }
    if(!m_curWidget) return;
    if(unsplicing())
        reLayout();
}

void WallLayout::dragEnterEvent(QDragEnterEvent *event)
{
//    event->acceptProposedAction();
}

void WallLayout::dropEvent(QDropEvent *event)
{
}

int WallLayout::getWidgetIndexByPosition(QPoint pos)
{
    for(int i=0; i<m_laywidgets.count(); i++)
    {
        SmallScreen *wall=qobject_cast<SmallScreen *>(m_laywidgets.at(i));
        if (!wall->used()) continue;
       if(wall->geometry().contains(pos))
       {
           m_curWidget=wall;
           return i;
       }
    }
}

bool WallLayout::swap1(int firstindex, int secondindex,bool span)
{
    int row=0,col=0;
    int rowspan=0,colspan=0;
    SmallScreen *first=qobject_cast<SmallScreen *>(m_laywidgets.at(firstindex));
    SmallScreen *second=qobject_cast<SmallScreen *>(m_laywidgets.at(secondindex));
    //swap...
    row=first->row();
    col=first->col();
    first->setRowCol(second->row(),second->col());
    second->setRowCol(row,col);

    if(span)
    {
        rowspan=first->rowspan();
        colspan=first->colspan();
        first->setSpan(second->rowspan(),second->colspan());
        second->setSpan(rowspan,colspan);
    }

    m_laywidgets.swap(firstindex,secondindex);
    return true;
}


void WallLayout::timerEvent(QTimerEvent *)
{
    qDebug()<<"timerEvent";
}

void WallLayout::reCreateLayout()
{
    m_curWidget=NULL;
    if(m_layout)
    {
        delete m_layout;
        m_layout=NULL;
    }

    m_layout=new QGridLayout(this);
    m_layout->setContentsMargins(1, 1, 1, 1);  m_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    m_layout->setSpacing(1);
    m_layout->setMargin(5); 
    m_layout->setContentsMargins(1, 1, 1, 1);
    m_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);

    this->setLayout(m_layout);
}

void WallLayout::selectedSlot(SmallScreen *value)
{
    this->m_curWidget=value;
    this->update();
}

void WallLayout::swap(int index1, int index2)
{
    SmallScreen *w1=(SmallScreen *)m_laywidgets.at(index1);
    SmallScreen *w2=(SmallScreen *)m_laywidgets.at(index2);
    QString displayid=w1->displayid();
    w1->setDisplayid(w2->displayid());
    w2->setDisplayid(displayid);

}

void WallLayout::singleWidgetMaximized()
{
    QT_TRY
    {
        Q_CHECK_PTR(m_curWidget);

       for(int i=0; i<m_laywidgets.count(); i++)
       {
           QWidget *widget = m_laywidgets[i];
           if(widget != m_curWidget)
               widget->hide();
           else
           {
               m_doubleClicked = true;
               update();
           }
       }
    }QT_CATCH(...)
    {
        return;
    }
}

void WallLayout::showAllWidget()
{
    int count = m_laywidgets.count();
    for(int i=0; i<count; i++)
    {
        SmallScreen *widget=(SmallScreen *)m_laywidgets.at(0);
        if (!widget->used()) continue;
        m_laywidgets[i]->show();
        update();
    }
    m_doubleClicked = false;
}


