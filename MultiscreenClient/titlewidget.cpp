#include "titlewidget.h"
#include "ui_titlewidget.h"
#include <QMouseEvent>

TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    m_move(false),
    ui(new Ui::TitleWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);

    connect(ui->minBtn, SIGNAL(clicked()), this, SIGNAL(minBtnClickSig()));
    connect(ui->closeBtn, SIGNAL(clicked()), this, SIGNAL(closeBtnClickSig()));
    connect(ui->maxBtn, SIGNAL(clicked()), this, SIGNAL(maxBtnClickSig()));
}

TitleWidget::~TitleWidget()
{
    delete ui;
}

QWidget *TitleWidget::content()
{
    return ui->content;
}

void TitleWidget::mousePressEvent(QMouseEvent *e)
{
    //按住左键移动可以拖动窗口
    if(e->button() == Qt::LeftButton)
    {
        m_startPos = e->globalPos();
        m_DragPos = e->globalPos() - frameGeometry().topLeft();
        if(ui->title->geometry().contains(e->pos())){
            m_move =true;
        }
        //   m_ParentPos = parentWidget()->pos();
        //    emit dragMousePressSignal(m_DragPos);
        e->accept();
    }
}

void TitleWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() && Qt::LeftButton)
    {
        if(m_move)
            move( e->globalPos()-m_DragPos);
        //     emit dragMouseMoveSignal(e->globalPos());
        e->accept();
    }
}

void TitleWidget::mouseReleaseEvent(QMouseEvent *)
{
    if(m_move)
    {
        m_move = false;
    }
}

void TitleWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit maxBtnClickSig();
}
