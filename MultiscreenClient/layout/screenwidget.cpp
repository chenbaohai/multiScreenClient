#include "screenwidget.h"
#include "ui_screenwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>
#include "windows.h"


ScreenWidget::ScreenWidget(QWidget *parent) :
    QWidget(parent),
    m_Row(-1),
    m_Column(-1),
    m_RowSpan(1),
    m_ColumnSpan(1),
    m_isUsing(true),
    m_isSelected(false),
    m_isMerged(false),
    m_curMode(false),
    m_disPlayInfo(NULL),
    ui(new Ui::ScreenWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    setMouseTracking(true);
    m_handle=NULL;
    m_timerid=0;

//    this->setAutoFillBackground(true);
//    QPalette p = this->palette();
//    p.setBrush(QPalette::Window,Qt::black);
//    this->setPalette(p);

    m_pixmap=NULL;

}

ScreenWidget::ScreenWidget(int originalRow, int originalColumn, QWidget *parent):
    QWidget(parent),
    m_Row(-1),
    m_Column(-1),
    m_RowSpan(1),
    m_ColumnSpan(1),
    m_isUsing(true),
    m_isSelected(false),
    m_disPlayInfo(NULL),
    m_OutputID(""),
     ui(new Ui::ScreenWidget)
{
    ui->setupUi(this);
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
    m_originalRow = originalRow;
    m_originalColumn= originalColumn;
    m_Row = originalRow;
    m_Column = originalColumn;
}

ScreenWidget::~ScreenWidget()
{
    delete ui;
    if(m_disPlayInfo!=NULL){
        delete m_disPlayInfo;
        m_disPlayInfo = NULL;
    }

}

int ScreenWidget::row()
{
    return m_Row;
}

int ScreenWidget::column()
{
    return m_Column;
}

int ScreenWidget::originalRow()
{
    return m_originalRow;
}

int ScreenWidget::originalColumn()
{
    return m_originalColumn;
}

void ScreenWidget::setRow(int row)
{
    m_Row = row;
}

void ScreenWidget::setColumn(int column)
{
    m_Column = column;
}

int ScreenWidget::SpanRow()
{
    return m_RowSpan ;
}

int ScreenWidget::SpanColumn()
{
    return m_ColumnSpan;
}

void ScreenWidget::setSpanRow(int rowcount)
{
    m_RowSpan = rowcount;
}

void ScreenWidget::setSpanColumn(int columncount)
{
    m_ColumnSpan = columncount;
}

bool ScreenWidget::isUsing()
{
    return m_isUsing;
}

bool ScreenWidget::isMerge()
{
    return m_isMerged;
}

bool ScreenWidget::isSelected()
{
    return  m_isSelected;
}

void ScreenWidget::MergeFlag(bool is)
{
    m_isMerged = is;
}

void ScreenWidget::UsingFlag(bool flag)
{
        this->setHidden(!flag);
    m_isUsing = flag;
}

void ScreenWidget::setSelected(bool is)
{
        m_isSelected =is;
//        update();
}

void ScreenWidget::setCurMode(bool is)
{
    m_curMode = is;
}

QString ScreenWidget::outputId()
{
    return  m_OutputID;
}

void ScreenWidget::setOutPutId(QString  outid)
{
    m_OutputID = outid;
}

DisPlayInfo *ScreenWidget::disPlayInfo()
{
    return m_disPlayInfo;
}

void ScreenWidget::setDisPlayInfo(DisPlayInfo * info)
{
    m_disPlayInfo = info;
}

  ScreenWidget* ScreenWidget::clone()
{
//    stopCapture(m_timerid);
//    ScreenWidget*  widget = new ScreenWidget;
//    DisPlayInfo* info = new DisPlayInfo;
//    widget->setDisPlayInfo(info);
////    widget->setGrabHandle(m_handle);
//    return widget;
}

QList<ScreenWidget *>* ScreenWidget::ContainScreenList()
{
    return &m_ContainWidgetList;
}

void ScreenWidget::paintEvent(QPaintEvent *e)
{  
    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing,true);
    QLinearGradient linearGradient(rect().width(),rect().height(),0,0);

    linearGradient.setSpread(QGradient::RepeatSpread);
    linearGradient.setColorAt(0.0, Qt::lightGray);
    linearGradient.setColorAt(0.2, Qt::lightGray);
    linearGradient.setColorAt(0.8, Qt::lightGray);
    linearGradient.setColorAt(1.0, Qt::lightGray);
    paint.setBrush(QBrush(linearGradient));
    paint.drawRect(rect());


//    if(!m_curMode)
//    {
//        return;
//    }
//    if(!m_isSelected)
//    {
//        linearGradient.setSpread(QGradient::RepeatSpread);
//        linearGradient.setColorAt(0.0, Qt::lightGray);
//        linearGradient.setColorAt(0.2, Qt::lightGray);
//        linearGradient.setColorAt(0.8, Qt::lightGray);
//        linearGradient.setColorAt(1.0, Qt::lightGray);
//        paint.setBrush(QBrush(linearGradient));
//        paint.drawRect(rect());
//    }else{
//        linearGradient.setSpread(QGradient::RepeatSpread);
//        linearGradient.setColorAt(0.0, QColor(77,197,244));
//        linearGradient.setColorAt(0.2, QColor(77,197,244));
//        linearGradient.setColorAt(0.8, QColor(77,197,244));
//        linearGradient.setColorAt(1.0, QColor(77,197,244));
//        paint.setBrush(QBrush(linearGradient));
//        paint.drawRect(rect());
//    }
}

void ScreenWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if(!m_curMode)
    {
        qDebug()<<"ScreenWidget::mouseDoubleClickEvent";
        return QWidget::mouseDoubleClickEvent(e);
    }
    ScreenWidget* widget;
      int count = m_ContainWidgetList.count();
      if(count ==0){
          return;
      }
      for(int i=0;i<count;i++){
         widget= m_ContainWidgetList.at(i);
         widget->UsingFlag(true);
      }
      m_ContainWidgetList.clear();
      emit changeSpanSignal(this);
}

void ScreenWidget::changeMode(bool is)
{
    m_curMode = is ;
}

void ScreenWidget::enterEvent(QEvent *)
{
    emit mouseEnterSig(this);
}

void ScreenWidget::setGrabHandle(HWND value)
{
//    m_handle=value;
//    startCapture();
}

void ScreenWidget::resizeEvent(QResizeEvent *)
{
//    if(!m_handle) return;
//    int x=this->disPlayInfo()->getDisPlayRect().x();
//    int y=this->disPlayInfo()->getDisPlayRect().y();
//    int w=this->disPlayInfo()->getDisPlayRect().width();
//    int h=this->disPlayInfo()->getDisPlayRect().height();
}

void ScreenWidget::fixPosition()
{

    if(m_handle)
    {
        int x=0;
        int y=0;
        int w=this->disPlayInfo()->getDisPlayRect().width();
        int h=this->disPlayInfo()->getDisPlayRect().height();
        if(this->isUsing())
        {
            x=this->disPlayInfo()->getDisPlayRect().x();
            y=this->disPlayInfo()->getDisPlayRect().y();
        }        
        MoveWindow(this->m_handle,x,y,w,h,true);
        if(this->isUsing())
        {
            ShowWindow(m_handle,SW_SHOW);
        }
        else
            ShowWindow(m_handle,SW_HIDE);
        qDebug()<<"ScreenWidget::fixPosition->"<<this->disPlayInfo()->getDisPlayRect()<<x<<y<<w<<h<<m_handle<<this<<this->isUsing();
    }

//    if(this->isUsing())
//    {
////        this->resizeEvent(NULL);
//        if(this->m_handle!=NULL)
//            startCapture();
//    }
//    else
//    {
//        if(m_timerid!=0)
//            stopCapture(m_timerid);
//        m_timerid=0;
//    }
}

void ScreenWidget::captureSlot(QPixmap *value)
{    
    m_pixmap=value;
    this->update();
}





HWND ScreenWidget::grabHandle()
{
    return this->m_handle;
}

void ScreenWidget::returnToMainScreen()
{
//    qDebug()<<"ScreenWidget::returnToMainScreen:"<<this->m_handle<<this;
//    if(this->m_handle)
//    {
//        MoveWindow(m_handle,0,0,this->geometry().width(),this->geometry().height(),true);
//        ShowWindow(m_handle,SW_SHOWMINIMIZED);
//    }
//    this->m_handle=NULL;
//    stopCapture(m_timerid);
//    m_pixmap=NULL;
//    update();
}



