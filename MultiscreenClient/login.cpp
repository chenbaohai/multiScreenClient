#include "login.h"
#include "ui_login.h"
#include <QPaintEvent>
#include <QPainter>
#include <QBitmap>
#include <QAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QDir>
#include "mainwidget.h"
#include "requestManager.h"
#include "configini.h"

Login::Login(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);

    QDir file;
    bool exist = file.exists("config.ini");
    if (!exist)
    {
        ui->serverIpEdit->setText("192.168.208.41");
        ui->portEdit->setText("8380");
        ui->edt_multiip->setText("192.168.208.41");
        ui->edt_multiport->setText("5234");
    }
    else
    {
        ui->serverIpEdit->setText(ConfigIni::instance()->restIp());
        ui->portEdit->setText(QString::number(ConfigIni::instance()->restPort()));
        ui->edt_multiip->setText(ConfigIni::instance()->serverIp());
        ui->edt_multiport->setText(QString::number(ConfigIni::instance()->serverPort()));
    }

    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\MulitScreenApp", QSettings::NativeFormat);
    QString username=reg->value("username").toString();
    QString password=reg->value("password").toString();
    delete reg;

    ui->userEdit->setText(username);
    ui->pwdEdit->setText(password);
    if(ui->userEdit->text().isEmpty())
        ui->userEdit->setFocus();
    else
        ui->pwdEdit->setFocus();

    ui->userEdit->setTextMargins(32,0,0,0);
    ui->pwdEdit->setTextMargins(32,0,0,0);

    ui->serverWidget->hide();
    ui->optBtn->raise();

    connect(ui->exitBtn, SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->optBtn,SIGNAL(clicked()),this,SLOT(optWidgetShow()));

    m_socket=new MSocket;

    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx,NULL);
    ui->portEdit->setValidator( validator );
    ui->edt_multiport->setValidator(validator);

}

Login::~Login()
{
    if(m_socket)
    {
        delete m_socket;
    }
    delete ui;
}

void Login::paintEvent(QPaintEvent *event)
{
    QBitmap bitMap(size());
    bitMap.fill(QColor(255,255,255));
    QPainter painter(&bitMap);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::TextAntialiasing,true);
    painter.setBrush(QColor(0,0,0));
    painter.setPen(QPen(QColor(0,0,0), 1,Qt::SolidLine ,Qt::RoundCap,Qt::RoundJoin));
    painter.drawRoundRect(rect(),4,4);
    setMask(bitMap);
    QWidget::paintEvent(event);
}

void Login::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_startPos = e->globalPos();
        m_parentPos = this->pos();
        emit dragMousePressSignal(m_startPos);
        e->accept();
    }
}

void Login::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() && Qt::LeftButton)
    {
        this->move(m_parentPos + (e->globalPos()- m_startPos));
        emit dragMouseMoveSignal(e->globalPos());
        e->accept();
    }
}

void Login::optWidgetShow()
{
    if(ui->serverWidget->isHidden()) {
        ui->serverWidget->show();
        QAnimationGroup *aniGroup = new QParallelAnimationGroup;
        aniGroup->connect(aniGroup,SIGNAL(finished()),aniGroup,SLOT(deleteLater()));
        //            connect(aniGroup,SIGNAL(finished()),this,SLOT(animationFinished()));


        QPropertyAnimation *anim = new QPropertyAnimation(ui->serverWidget, "geometry");
        anim->setStartValue(QRect(ui->OptWidget->width() - ui->optBtn->width(), 0, 0, ui->OptWidget->height()));
        anim->setEndValue(QRect(0, 0, ui->OptWidget->width() - ui->optBtn->width(), ui->OptWidget->height()));
        anim->setDuration(100);
        anim->setEasingCurve(QEasingCurve::Linear);   //InOutBack OutCirc
        aniGroup->addAnimation(anim);

        aniGroup->start(QAbstractAnimation::DeleteWhenStopped);

    } else {
        QAnimationGroup *aniGroup = new QParallelAnimationGroup;
        aniGroup->connect(aniGroup,SIGNAL(finished()),aniGroup,SLOT(deleteLater()));
        connect(aniGroup,SIGNAL(finished()),ui->serverWidget,SLOT(hide()));


        QPropertyAnimation *anim = new QPropertyAnimation(ui->serverWidget, "geometry");
        anim->setEndValue(QRect(ui->OptWidget->width() - ui->optBtn->width(), 0, 0, ui->OptWidget->height()));
        anim->setStartValue(QRect(0, 0, ui->OptWidget->width() - ui->optBtn->width(), ui->OptWidget->height()));
        anim->setDuration(100);
        anim->setEasingCurve(QEasingCurve::Linear);   //InOutBack OutCirc
        aniGroup->addAnimation(anim);

        aniGroup->start(QAbstractAnimation::DeleteWhenStopped);
//        ui->serverWidget->hide();
    }
}

void Login::on_loginBtn_clicked()
{
    if (getLoginInfo())
    {
        LoginRequest *request = new LoginRequest;
        request->setUser(m_user);
        request->setPassword(m_password);
        ConfigIni::instance()->setRestIp(m_ip);
        ConfigIni::instance()->setRestPort(m_port);        
        ConfigIni::instance()->setServerIp(m_multiIp);
        ConfigIni::instance()->setServerPort(m_multiPort);
        if (RequestManager::instance()->token(request))
        {
            if(m_socket->connectServer())
            {
                QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\MulitScreenApp", QSettings::NativeFormat);
                reg->setValue("username",m_user);
                reg->setValue("password",m_password);
                delete reg;
                this->accept();
            }
            else
                QMessageBox::warning(this, "系统提示","连接多屏服务失败！",tr("确定"));
        }
        else
        {
            QMessageBox::warning(this, "系统提示","连接中心服务失败！",tr("确定"));
        }
    }
}

bool Login::getLoginInfo()
{
    m_user = ui->userEdit->text();
    m_password = ui->pwdEdit->text();
    m_ip = ui->serverIpEdit->text();
    m_port = ui->portEdit->text().toInt();
    m_multiIp = ui->edt_multiip->text();
    m_multiPort = ui->edt_multiport->text().toInt();
    if ( m_user == NULL || m_password == NULL)
    {
        QMessageBox::warning(this, "系统提示","用户名，密码不能为空！",tr("确定"));
        return false;
    }
    if(m_ip == NULL || m_port == NULL)
    {
        QMessageBox::warning(this, "系统提示","服务器地址，端口不能为空！",tr("确定"));
        return false;
    }
    if(m_multiIp == NULL || m_multiPort == NULL)
    {
        QMessageBox::warning(this, "系统提示","多屏卡地址，端口不能为空！",tr("确定"));
        return false;
    }
    return true;
}

void Login::on_pwdEdit_returnPressed()
{
    ui->loginBtn->click();
}

MSocket * Login::msgSocket()
{
    return this->m_socket;
}
