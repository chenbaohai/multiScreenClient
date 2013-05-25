#include "montagelayout.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QPushButton>


MontageLayout::MontageLayout(QWidget *parent) :
    dragMoveFlag(false),
    mousePressFlag(false),
    m_cancelFlag(false),
    LayoutWidget(parent)
{
    rectfrm=NULL;
    m_cancelDisplayid = new QAction(this);
    m_context =new QMenu;
    m_cancelDisplayid->setText("取消");
    m_context->addAction(m_cancelDisplayid);
    connect(m_cancelDisplayid,SIGNAL(triggered()),this,SLOT(cancelDisplayidSlot()));
    this->setAcceptDrops(true);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();
}

MontageLayout::~MontageLayout()
{
    if(rectfrm!=NULL)
    {
        delete rectfrm;
        rectfrm = NULL;
    }
}


void MontageLayout::mousePressEvent(QMouseEvent * e)
{
    m_isMerged=false;
    m_startPoint=e->pos();
    selectScreenWidget(m_startPoint);
    mousePressFlag = true;
}

void MontageLayout::mouseMoveEvent(QMouseEvent * e)
{
    if(!mousePressFlag){
        return;
    }
    m_endPoint=e->pos();
    dragMoveFlag = true;
    if(!rectfrm)
    {
        rectfrm=new rectangle;
        rectfrm->show();
    }
    if(rectfrm)
    {
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

        rectfrm->setGeometry(QRect(gPointX,QSize(qAbs(m_endPoint.x()-m_startPoint.x()),qAbs(m_endPoint.y()-m_startPoint.y()))));

        QPoint topPoint=mapFromGlobal(gPointX);
        QRect rect(topPoint,rectfrm->geometry().size());
        m_selrect=rect;
    }
    calucate();
}

void MontageLayout::mouseReleaseEvent(QMouseEvent * e)
{
    mousePressFlag = false;  //鼠标释放后去除按下标��
    if(!dragMoveFlag) return;  //通过判断鼠标是否移动，判断是框选操作还是点击操作��
    if(rectfrm)
    {
        delete rectfrm;
        rectfrm=NULL;
    }
    m_endPoint=e->pos();

    MergeScreen();
    if(m_isMerged)
    {
        changeScreen(true);
        emit saveMergeXmlSig();
    }

    dragMoveFlag =false;
}

void MontageLayout::dragEnterEvent(QDragEnterEvent *event)
{
    //    event->acceptProposedAction();
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void MontageLayout::dropEvent(QDropEvent *event)
{
    QPoint aPos = event->pos();
    BaseWidget* tem=getScreen(aPos,*ScreenList()) ;
    if(tem!=NULL){
        tem->setDisplayid(event->mimeData()->text());
    }
}

void MontageLayout::contextMenuEvent(QContextMenuEvent *event)
{
    if (m_cancelFlag)
    {
        if(m_selectedScreen!=NULL && m_selectedScreen->displayId()!="0")
            m_context->exec(event->globalPos());
    }
}

void MontageLayout::calucate()
{
    m_MergeList.clear();
    for(int i=0;i<m_ScreenList.count();i++)
    {
        Screen *widget=(Screen *)m_ScreenList[i];
        if(!widget->useflag())
            continue;
        widget->setSelected(false);
        int widgetLeft=widget->geometry().x();
        int widgetRight=widget->geometry().x()+widget->geometry().width();
        int widgetTop=widget->geometry().y();
        int widgetBottom=widget->geometry().y()+widget->geometry().height();

        int rectTop=m_selrect.y();
        int rectBottom=m_selrect.bottomLeft().y();
        if((widgetLeft>m_selrect.x()&&widgetLeft<m_selrect.topRight().x() || widgetRight>m_selrect.x()&&widgetRight<m_selrect.topRight().x() ||widgetLeft<m_selrect.x() && widgetRight>m_selrect.topRight().x())
                && (rectTop>widgetTop && rectTop<widgetBottom || rectBottom>widgetTop && rectBottom<widgetBottom || rectTop<widgetTop && rectBottom>widgetBottom))
        {
            widget->setSelected(true);
            m_MergeList.append(widget);
            //得到圈中的最大行最大列
        }
    }
    //得到行列内的所有widget
    //    qDebug()<<"LayoutWidget::calucate,m_ScreenList"<<m_ScreenList.count()<<",m_MergeList"<<m_MergeList.count();
}

void MontageLayout::MergeScreen()
{
    m_isMerged=m_MergeList.count()>1?true:false;
    int count = m_MergeList.count();
    if(count <=1){
        return;
    }
    if(searchMergeScreen(m_MergeList))
    {  //如果选中的screen有时合并过的，返回��
        m_isMerged = false;
        return;
    }
    int minRow ;
    int minColumn ;
    int rowSpan;
    int columnSpan;

    getScreenSpan(minRow,minColumn,rowSpan,columnSpan);

    FillMergeScreen(minRow,minColumn,rowSpan,columnSpan,(Screen *)m_selectedScreen);
    *(((Screen*)m_selectedScreen)->getMergeList())<<m_MergeList;
    m_MergeList.clear();
    emit selectedScreenSignal(m_selectedScreen);
}

void MontageLayout::getScreenSpan(int& Vminrow,int& Vmincolumn,int &rowSpan, int &columnSpan)
{
    Screen* widget;
    for(int i =0;i< m_MergeList.count();i++)
    {
        widget = (Screen *)m_MergeList.at(i);
        widget->setSelected(false);
    }
    int maxRow;
    int maxColumn ;
    int minRow ;
    int minColumn;
    getMax_MinRowColumn(minRow,minColumn,maxRow,maxColumn,m_MergeList);
    Vminrow = minRow;
    Vmincolumn = minColumn;
    rowSpan = maxRow -minRow+1;
    columnSpan = maxColumn - minColumn+1;
}

void MontageLayout::FillMergeScreen(int Vminrow, int Vmincolumn, int rowSpan, int columnSpan, Screen *widget)
{
    widget->saveOldPos();
    widget->setRow(Vminrow);
    widget->setColumn(Vmincolumn);
    widget->setSpanRow(rowSpan);
    widget->setSpanColumn(columnSpan);
    widget->setUseflag(true);
    widget->setIsMerge(true);
}

void MontageLayout::cancelDisplayidSlot()
{
    emit cancelDisplayidSig(m_selectedScreen->displayId().toInt());
    m_selectedScreen->cancelDisPlayid();
}

void MontageLayout::getMax_MinRowColumn(int& minRow,int& minColumn,int& maxRow,
                                        int& maxColumn,QList<Screen* > & list)
{
    Screen* widget;
    for(int i=0;i<list.count();i++)
    {
        widget = list.at(i);
        int tempminRow = 0;
        int tempminColumn =0;
        int tempmaxRow=0;
        int tempmaxColumn=0;
        if(0==i)
        {
            maxRow = widget->row();
            maxColumn = widget->column();
            minRow  = widget->row();
            minColumn = widget->column();
        }
        tempmaxRow = widget->SpanRow()+widget->row()-1;
        if(tempmaxRow<widget->row()){
            tempminRow = tempmaxRow;
            tempmaxRow = widget->row();
        }else{
            tempminRow = widget->row();
        }
        tempmaxColumn =  widget->SpanColumn() +widget->column() -1;
        if(tempmaxColumn< widget->column()){
            tempminColumn =tempmaxColumn;
            tempmaxColumn =  widget->column();
        }else{
            tempminColumn = widget->column();
        }

        if(maxRow<tempmaxRow){
            maxRow = tempmaxRow;
        }
        if(minRow>tempminRow){
            minRow = tempminRow;
        }
        if(maxColumn<tempmaxColumn){
            maxColumn = tempmaxColumn;
        }
        if(minColumn>tempminColumn){
            minColumn =tempminColumn;
        }
        widget->setIsMerge(false);
        widget->setUseflag(false);
    }
}

bool MontageLayout::searchMergeScreen(QList<Screen *> &list)
{
    foreach(Screen* tem,list)
    {
        if(tem->isMerged())
            return true;
    }
    return false;
}

void MontageLayout::changeSpanSlot(BaseWidget *widget)
{
    qDebug() << "MontageLayout::changeSpanSlot(BaseWidget *widget)";
    ((Screen*)widget)->setIsMerge(false);
    LayoutWidget::changeSpanSlot(widget);
    emit saveMergeXmlSig();
}

void MontageLayout::focusOutEvent(QFocusEvent *)
{
//    qDebug()<<"MontageLayout::focusOutEvent";
    Screen *screen= (Screen*)m_selectedScreen;
    if (screen != NULL)
    {
        screen->setPaintFlag(false);
    }
}

void MontageLayout::saveConfigXml()
{

}

void MontageLayout::setConfigFlag()
{
    m_configFlag = true;
}

void MontageLayout::setCancelFlag()
{
    m_cancelFlag = true;
}
