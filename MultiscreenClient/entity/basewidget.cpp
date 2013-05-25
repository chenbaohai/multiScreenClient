#include "basewidget.h"
#include "ui_basewidget.h"
#include <QPainter>
#include <QDebug>

BaseWidget::BaseWidget(QWidget *parent) :
    m_Row(-1),
    m_Column(-1),
    m_RowSpan(1),
    m_ColumnSpan(1),
    m_originalRow(0),
    m_originalColumn(0),
    m_originalRowSpan(0),
    m_originalColSpan(0),
    m_selected(false),
    m_useFlag(true),
    m_mergeFlag(true),
    m_paintFlag(false),
    m_displayId("0"),
    m_doubleClickFlag(false),
    QWidget(parent),
    ui(new Ui::BaseWidget)
{
    ui->setupUi(this);
}

BaseWidget::~BaseWidget()
{
    delete ui;
}

int BaseWidget::row()
{
    return m_Row;
}

int BaseWidget::column()
{
    return m_Column;
}

void BaseWidget::setRow(int row)
{
    m_Row = row;
}

void BaseWidget::setColumn(int col)
{
    m_Column = col;
}

int BaseWidget::SpanRow()
{
    return m_RowSpan;
}

int BaseWidget::SpanColumn()
{
    return m_ColumnSpan;
}


void BaseWidget::saveOldPos()
{
    m_originalColumn =m_Column ;
    m_originalRow =m_Row ;
    m_originalColSpan = m_ColumnSpan;
    m_originalRowSpan = m_RowSpan;
}

void BaseWidget::restoreOldPos()
{
    m_Column = m_originalColumn;
    m_Row = m_originalRow;
    m_RowSpan = m_originalRowSpan;
    m_ColumnSpan = m_originalColSpan;
}

bool BaseWidget::useflag()
{
    return m_useFlag;
}

QString& BaseWidget::displayId()
{
    return m_displayId;
}

void BaseWidget::setUseflag(bool is)
{
    this->setHidden(!is);
    m_useFlag = is;
}

BaseWidget *BaseWidget::clone()
{
}

void BaseWidget::setDisplayid(const QString &id)
{
    m_displayId = id;
}

void BaseWidget::setSelected(bool is)
{
    m_selected = is;
}

void BaseWidget::cancelDisPlayid()
{
    return;
}

void BaseWidget::setSpanRow(int span)
{
    m_RowSpan = span;
}

void BaseWidget::setSpanColumn(int span)
{
    m_ColumnSpan = span;
}

void BaseWidget::enterEvent(QEvent *)
{
//    qDebug() << "BaseWidget::enterEvent";
    emit mouseEnterSig(this);
}

void BaseWidget::setPaintFlag(bool flag)
{
    m_paintFlag = flag;
}

bool BaseWidget::select()
{
    return m_selected;
}

int BaseWidget::originalRow()
{
    return m_originalRow;
}

int BaseWidget::originalColumn()
{
    return m_originalColumn;
}

int BaseWidget::originalSpanRow()
{
    return m_originalRowSpan;
}

int BaseWidget::originalSpanColumn()
{
    return m_originalColSpan;
}

void BaseWidget::setOriginalRow(int row)
{
    m_originalRow = row;
}

void BaseWidget::setOriginalColumn(int col)
{
    m_originalColumn = col;
}

void BaseWidget::setOriginalSpanRow(int row)
{
    m_originalRowSpan = row;
}

void BaseWidget::setOriginalSpanColumn(int col)
{
    m_originalColSpan = col;
}

void BaseWidget::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing,true);
    QLinearGradient linearGradient(rect().width(),rect().height(),0,0);
    linearGradient.setSpread(QGradient::RepeatSpread);

    if (m_paintFlag)
    {
        linearGradient.setSpread(QGradient::RepeatSpread);
        linearGradient.setColorAt(0.0, QColor(168, 240, 255));
        linearGradient.setColorAt(0.2, QColor(168, 240, 255));
        linearGradient.setColorAt(0.8, QColor(168, 240, 255));
        linearGradient.setColorAt(1.0, QColor(168, 240, 255));
    }
    else
    {
        linearGradient.setSpread(QGradient::RepeatSpread);

        linearGradient.setColorAt(0.0, QColor(237, 252, 255));
        linearGradient.setColorAt(0.2, QColor(237, 252, 255));
        linearGradient.setColorAt(0.8, QColor(237, 252, 255));
        linearGradient.setColorAt(1.0, QColor(237, 252, 255));
    }

    paint.setBrush(QBrush(linearGradient));
    paint.drawRect(rect());
}

void BaseWidget::setDoubleClick(bool flag)
{
    m_doubleClickFlag = flag;
}

bool BaseWidget::getDoubleClick()
{
    return m_doubleClickFlag;
}

//bool BaseWidget::mergeFlag()
//{
//    return m_mergeFlag;
//}

//void BaseWidget::setMergeFlag(bool flag)
//{
//    m_mergeFlag = flag;
//}
