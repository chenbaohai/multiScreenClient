#include "screentoolbar.h"
#include "ui_screentoolbar.h"
#include <QMouseEvent>
#include <QDebug>
#include <QScrollBar>

ScreenToolBar::ScreenToolBar(QWidget *parent) :
    QWidget(parent),
    m_selectedBtn(NULL),
    ui(new Ui::ScreenToolBar)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
    ui->scrollAreaWidgetContents->installEventFilter(this);
}

ScreenToolBar::~ScreenToolBar()
{
    delete ui;
}

void ScreenToolBar::setScreenCount(int count)
{
    m_screenCount =count;
}

void ScreenToolBar::creatScreenId()
{
    for(int i =1;i<m_screenCount+1;i++)
    {
         QToolButton* btn = new QToolButton;
         btn->setProperty("module","screenIdBtn");
//         btn->setMinimumSize(50,50);
         btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
         btn->setText(QString::number(i));
         btn->installEventFilter(this);
         ui->ScreenIdLayout->addWidget(btn);
         m_toolbottons.append(btn);
    }
}

void ScreenToolBar::cancelDisplayId(int id)
{
    QToolButton* btn = getBtn(id);
    btn->setHidden(false);
}

void ScreenToolBar::cleanScreen()
{
    foreach(QToolButton *tmp,m_toolbottons)
        ui->ScreenIdLayout->removeWidget(tmp);
    qDeleteAll(m_toolbottons);
    m_toolbottons.clear();
}

void ScreenToolBar::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        m_startPoint = e->pos();
    QWidget::mousePressEvent(e);

}

void ScreenToolBar::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton) {
        int distance = (e->pos() - m_startPoint).manhattanLength();
        if (distance >= QApplication::startDragDistance())
            startDrag();
    }
    QWidget::mouseMoveEvent(e);
}

bool ScreenToolBar::eventFilter(QObject *target, QEvent *e)
{
    if (existBtn(target)){
        if (e->type() == QEvent::MouseButtonPress){
            QMouseEvent * Event = static_cast<QMouseEvent *>(e);
            mousePressEvent(Event);
            return true;
        }
    }
    return  QWidget::eventFilter(target, e);
}

void ScreenToolBar::startDrag()
{
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(m_selectedBtn->text());
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    //drag->setPixmap(QPixmap(":/images/person.png"));
    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        m_selectedBtn->setHidden(true);
}

bool ScreenToolBar::existBtn(QObject *btn)
{
    int index=  ui->ScreenIdLayout->indexOf((QWidget*)btn);
    if(index==-1){
      return false;
    }else{
      m_selectedBtn = (QToolButton*)btn;
      return true;
    }
}

QToolButton *ScreenToolBar::getBtn(int id)
{
    int count = ui->ScreenIdLayout->count();
    for(int i=0;i<count;i++){
        QToolButton* btn= (QToolButton*)ui->ScreenIdLayout->itemAt(i)->widget();
        if(btn->text().toInt()==id){
            return btn;
        }
    }
}

void ScreenToolBar::on_RtoolBtn_clicked()
{
    QScrollBar *bar= ui->scrollArea->horizontalScrollBar();
    int currentPostion = bar->sliderPosition();
    bar->setSingleStep(120);
    int pagestep = bar->singleStep();
    bar->setSliderPosition(currentPostion + pagestep);
}

void ScreenToolBar::on_LtoolBtn_clicked()
{
    QScrollBar *bar= ui->scrollArea->horizontalScrollBar();
    int currentPostion = bar->sliderPosition();
    bar->setSingleStep(120);
    int pagestep = bar->singleStep();
    bar->setSliderPosition(currentPostion - pagestep);
}
