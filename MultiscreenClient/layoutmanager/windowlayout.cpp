#include "windowlayout.h"
#include <QLabel>
#include <QPalette>
#include <QPen>
#include <QPainter>

#include <QApplication>

WindowLayoutWidget::WindowLayoutWidget(QWidget *parent) :
    QWidget(parent)
{
    m_index=0;
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setSpacing(1);
    m_gridLayout->setContentsMargins(1, 1, 1, 1);  m_gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    setAcceptDrops(true);
    setMouseTracking(true);
    m_dbClicked=false;
    m_rightMenu=NULL;
    m_curWidget=NULL;
    m_curIndex=0;
}

void WindowLayoutWidget::ruleChangeLayout(int row, int column)
{
    QWidget *widget = NULL;
    int allWidgetCount = m_allWidget.count();
    int index=0;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<column; j++)
        {
            if(index < allWidgetCount)
            {
                widget = m_allWidget[index++];
                widget->update();
                widget->show();      
                this->m_gridLayout->addWidget(widget, i, j, 1,1);
            }
            else
            {
                widget=new QWidget;
                m_allWidget.append(widget);
                m_gridLayout->addWidget(widget, i, j, 1,1);
            }
        }
    }
    if(row*column < allWidgetCount)
        removeUnnecessaryWidget(index);
    this->update();
}

void WindowLayoutWidget::removeUnnecessaryWidget(int index)
{
    for(int i=m_allWidget.count()-1;i>=index;i--)
    {
        QWidget *widget = m_allWidget[i];
        if(widget ==m_curWidget)
            m_curWidget = m_allWidget[0];  
        emit forceStopSignal(i,widget);
        delete widget;
        m_allWidget.removeAt(i);
        update();
    }
}

void WindowLayoutWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_dbClicked=true;
        if(!m_doubleClicked)
            singleWidgetMaximized();
        else
            showAllWidget();
    }
    qDebug()<<"WindowLayoutWidget::mouseDoubleClickEvent";
    QWidget::mouseDoubleClickEvent(e);
}

void WindowLayoutWidget::singleWidgetMaximized()
{
    QT_TRY
    {
        Q_CHECK_PTR(m_curWidget);

       for(int i=0; i<m_allWidget.count(); i++)
       {
           QWidget *widget = m_allWidget[i];
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

void WindowLayoutWidget::showAllWidget()
{
    int count = m_allWidget.count();
    for(int i=0; i<count; i++)
    {        
        m_allWidget[i]->show();
        update();
    }
    m_doubleClicked = false;
}

void WindowLayoutWidget::mousePressEvent(QMouseEvent *e)
{
    m_dbClicked=false;
    //get the mousedown widget
    QWidget *current = QWidget::childAt(e->pos());
    if(current == NULL)
        return;
    for(int i=0; i<m_allWidget.count(); i++)
    {
       QWidget *playWidget = m_allWidget[i];
       if(playWidget->geometry().contains(e->pos()))
       {
           m_curWidget = playWidget;
           m_curIndex=i;
           QWidget *selected=m_curWidget;
           emit selectedSignal(i,selected);
           update();
           break;
       }
    }
    m_startPos=e->pos();
}

int WindowLayoutWidget::appendWidget(QWidget *widget)
{     
    return m_index;
}


void WindowLayoutWidget::paintEvent(QPaintEvent *)
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

void WindowLayoutWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->formats().contains("treeitem/x-group-point-type")) //application/x-qabstractitemmodeldatalist
        event->acceptProposedAction();
    else
        event->ignore();
}

void WindowLayoutWidget::dragMoveEvent(QDragMoveEvent *event)
{
}

void WindowLayoutWidget::dropEvent(QDropEvent *event)
{
    for(int i=0; i<m_allWidget.count(); i++)
    {
       QWidget *playWidget = m_allWidget[i];
       if(playWidget->geometry().contains(event->pos()))
       {
           emit insertSignal(i);
           break;
       }
    }
}

void WindowLayoutWidget::contextMenuEvent(QContextMenuEvent * event)
{
    if (!m_rightMenu)
        return;
    if(m_rightMenu->isEmpty())
        return;

    m_rightMenu->exec(event->globalPos());
}

void WindowLayoutWidget::setRightMenu(QMenu *value)
{
    this->m_rightMenu=value;
}

void WindowLayoutWidget::mouseMoveEvent(QMouseEvent * event)
{ 
//    if (event->buttons() & Qt::LeftButton)
//    {
//        int distance = (event->pos() - m_startPos).manhattanLength();
//        if (distance >= QApplication::startDragDistance())
//            this->setCursor(Qt::DragCopyCursor);
//    }
}

void WindowLayoutWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_dbClicked) return;
//    QWidget * playWidget=NULL;
//    int selected=-1;
//    for(int i=0; i<m_allWidget.count(); i++)
//    {
//        playWidget = m_allWidget[i];
//        selected=i;
//        if(playWidget->geometry().contains(e->pos()))
//        {
//            break;
//        }
//    }
    this->setCursor(Qt::ArrowCursor); 
}


QMenu * WindowLayoutWidget::rightMenu()
{
    return this->m_rightMenu;
}

bool WindowLayoutWidget::removeByIndex(int index)
{
//    qDebug()<<"BaseWidget::removeByIndex:"<<index<<"m_allWidget.count:"<<m_allWidget.count();
    if(index<0 || index>=m_allWidget.count())
        return false;
    QWidget * playwidget=m_allWidget[index];
    return true;
}

bool WindowLayoutWidget::insertWidget(int index, QWidget *w)
{
    if(index<0 || index>=m_allWidget.count())
        return false;
    QWidget * playwidget=m_allWidget[index];
    return true;
}

QList<QWidget *> WindowLayoutWidget::allWidget()
{
    return this->m_allWidget;
}

void WindowLayoutWidget::createWidget(double num)
{
    return;
}

