#include "layoutwidget.h"
#include "ui_layoutwidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>

LayoutWidget::LayoutWidget(QWidget *parent) :
    m_row(-1),
    m_column(-1),
    m_selectedScreen(NULL),
    m_flag(true),
    m_wndNum(0),
    QWidget(parent),
    ui(new Ui::LayoutWidget)
{
    ui->setupUi(this);

    m_GridLayout = NULL;
    setMouseTracking(true);
    m_curwidget = NULL;
}

LayoutWidget::~LayoutWidget()
{
    freeScreenList();
    if(m_GridLayout!=NULL){
        delete m_GridLayout;
    }

    delete ui;
}

void LayoutWidget::createLayout()
{
    if(m_GridLayout!= NULL)
    {
        delete m_GridLayout;
        m_GridLayout = NULL;
    }
    m_GridLayout = new QGridLayout(this);
    m_GridLayout->setContentsMargins(1, 1, 1, 1);
    m_GridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    m_GridLayout->setMargin(5);
    m_GridLayout->setSpacing(1);
    m_GridLayout->setContentsMargins(2, 2, 2, 2);
    m_GridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    setLayout(m_GridLayout);
}

void LayoutWidget::createScreen(int row, int column,BaseWidget* temp)
{
    int listCount = m_ScreenList.count();
    int screencount = 0;
    BaseWidget* widget ;
    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= column; j++)
        {
            if (screencount+1 > listCount)
            {
                widget = temp->clone();
                m_ScreenList.append(widget);
//                connect(widget,SIGNAL(changeSpanSignal(BaseWidget*)),this,SLOT(changeSpanSlot(BaseWidget*)));
            }
            else
            {
                widget = m_ScreenList.at(screencount);
            }

            widget->setRow(i);
            widget->setColumn(j);
            screencount++;
            m_GridLayout->addWidget(widget,i,j);
            widget->setUseflag(true);
//            widget->setMergeFlag(true);
        }
    }
    m_row = row;
    m_column = column;
    if(row*column < listCount)
        removeUnnecessaryWidget(screencount);
}

void LayoutWidget::changeScreen(bool streched)
{ 
    m_curwidget=NULL;
    createLayout();
    BaseWidget *widget ;

    for(int i=0;i<m_ScreenList.count();i++)
    {
        widget = m_ScreenList.at(i);
        if(widget->useflag())
        {
//            connect(widget,SIGNAL(changeSpanSignal(BaseWidget*)),this,SLOT(changeSpanSlot(BaseWidget*)));
            connect(widget, SIGNAL(mouseEnterSig(BaseWidget*)), this, SLOT(mouseEnterSlot(BaseWidget*)));
            if (!widget->getDoubleClick())
            {
                m_GridLayout->addWidget(widget,widget->row(),widget->column(),widget->SpanRow(),widget->SpanColumn());
            }
        }
    }
}

bool LayoutWidget::changeLayout(int row, int column,BaseWidget* temp)
{
    m_curwidget=NULL;
    if(m_row ==row && m_column ==column)
        return true;
    qDeleteAll(m_ScreenList);
    m_ScreenList.clear();
    BaseWidget * widget ;
    createLayout();
    createScreen(row, column,temp);
    int listCount = m_ScreenList.count();
    int screenCount = row*column;
    if(screenCount<listCount)
    {
        for(int i =screenCount;i< listCount;i++)
        {
            widget = m_ScreenList.at(i);
            widget->setUseflag(false);
        }
    }
    return true;
}

QList<BaseWidget*> *LayoutWidget::ScreenList()
{
    return &m_ScreenList;
}

void LayoutWidget::changeSpanSlot(BaseWidget *widget)
{
    qDebug() << "LayoutWidget::changeSpanSlot";
    widget->restoreOldPos();
    changeScreen(true);
}

void LayoutWidget::selectScreenWidget(QPoint startPoint)
{
    BaseWidget *temp = getScreen(startPoint,m_ScreenList);
    if(!m_curwidget)
        m_curwidget = temp;
    if(temp==NULL){
        return;
    }
    if(temp == m_selectedScreen){
        return;
    }
    if(m_selectedScreen==NULL){
        m_selectedScreen =temp;
        temp->setSelected(true);
    }else{
        m_selectedScreen->setSelected(false);
        temp->setSelected(true);
        m_selectedScreen =temp;
    }
    update();
    emit selectedScreenSignal(m_selectedScreen);
}

BaseWidget *LayoutWidget::getScreen(QPoint startPoint, QList<BaseWidget *> list)
{
    BaseWidget* widget ;
    for(int i =0;i<list.count();i++){
        widget = list.at(i);
        if(!widget->useflag()) continue;
        if(widget->geometry().contains(startPoint)){
            return widget;
        }
    }
    return NULL;
}

void LayoutWidget::freeScreenList()
{
    BaseWidget* widget;
    for(int i=0;i<m_ScreenList.count();i++){
        widget = m_ScreenList.at(i);
        m_ScreenList.removeOne(widget);
        delete widget;
        widget =NULL;
    }
}

void LayoutWidget::removeUnnecessaryWidget(int index)
{
    for(int i=m_ScreenList.count()-1;i>=index;i--)
    {
        BaseWidget *widget = m_ScreenList[i];
//        if(widget ==m_curwidget)
//            m_curwidget = m_ScreenList[0];
//        delete widget;
//        widget=NULL;
        m_delScreenList.append(m_ScreenList.at(i));
//        m_ScreenList.removeAt(i);
        update();
    }
}

BaseWidget * LayoutWidget::selectScreen()
{
    return m_selectedScreen;
}

void LayoutWidget::mouseEnterSlot(BaseWidget *widget)
{
    m_curwidget = widget;
    update();
}

void LayoutWidget::paintEvent(QPaintEvent *e)
{
    if (m_flag)
    {
        if (m_curwidget)
        {
//            qDebug() << m_curwidget << "m_curwidget LayoutWidget::paintEvent";
            QPainter paint(this);
            paint.setPen(QPen(QColor(168, 240, 255),2,Qt::SolidLine,Qt::RoundCap));
            paint.drawRect(m_curwidget->x(),
                             m_curwidget->y(),
                             m_curwidget->width(),
                             m_curwidget->height());
        }
    }
}

void LayoutWidget::setPaintFlag(bool flag)
{
    m_flag = flag;
}

bool LayoutWidget::createWidgetLayout(int row, int column,BaseWidget* temp)
{
    m_curwidget=NULL;
    if(m_row ==row && m_column ==column)
        return true;

    BaseWidget *widget ;
    createLayout();
    createScreen(row, column,temp);
//    int listCount = m_ScreenList.count();
//    int screenCount = row*column;
//    if(screenCount<listCount)
//    {
//        for(int i =screenCount;i< listCount;i++)
//        {
//            m_delScreenList.append(m_ScreenList.at(i));
////            widget = m_ScreenList.at(i);
////            removeUnnecessaryWidget(i);
//        }
//    }
    return true;
}

QList<BaseWidget *> * LayoutWidget::getDelScreenList()
{
    return &m_delScreenList;
}

void LayoutWidget::delScreenList()
{
    int count = m_ScreenList.count();
    for(int i = 1; i <= m_delScreenList.count(); i++)
    {
        m_ScreenList.removeAt(count - i);
    }
    qDeleteAll(m_delScreenList);
    m_delScreenList.clear();
}

void LayoutWidget::setSelectScreen(BaseWidget *widget)
{
    m_selectedScreen = widget;
}

//void LayoutWidget::change()
//{
//    m_curwidget=NULL;
//    createLayout();
//    BaseWidget *widget;

//    for(int i = m_ScreenList.count() - 1; i >=0; i--)
//    {
//        widget = m_ScreenList.at(i);
//        if(widget->useflag())
//        {
//            qDebug() << "LayoutWidget::change" << widget;
//            connect(widget,SIGNAL(changeSpanSignal(BaseWidget*)),this,SLOT(changeSpanSlot(BaseWidget*)));
//            connect(widget, SIGNAL(mouseEnterSig(BaseWidget*)), this, SLOT(mouseEnterSlot(BaseWidget*)));
//            if (!widget->getDoubleClick())
//            {
//                m_GridLayout->addWidget(widget, 1, 1);
//            }
//        }
//    }
//}

//void LayoutWidget::removeLayoutWidget()
//{
//    foreach(BaseWidget*temp, m_ScreenList)
//    {
//        qDebug() << "LayoutWidget::removeLayoutWidget" << temp;
//        m_GridLayout->removeWidget(temp);
//    }
//    qDebug()<<"LayoutWidget::removeLayoutWidget"<<m_ScreenList.count();
//}

//void LayoutWidget::removeWidget(int index)
//{
//    for(int i=m_ScreenList.count()-1;i>=index;i--)
//    {
//        BaseWidget *widget = m_ScreenList[i];
//        if(widget ==m_curwidget)
//            m_curwidget = m_ScreenList[0];
//        delete widget;
//        widget=NULL;
//        m_delScreenList.append(m_ScreenList.at(i));
//        m_ScreenList.removeAt(i);
//        update();
//    }
//}

//void LayoutWidget::restoreScreen()
//{
//    for(int i=m_delScreenList.count()-1;i>=0;i--)
//    {
//        m_ScreenList.append(m_delScreenList.at(i));
//        m_delScreenList.removeAt(i);
//    }
//    qDebug() << "LayoutWidget::restoreScreen()" << m_ScreenList.count();
//}
