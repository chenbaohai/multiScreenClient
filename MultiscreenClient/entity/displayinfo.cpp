#include "displayinfo.h"

#include <QDebug>

DisPlayInfo::DisPlayInfo(QObject *parent) :
    QObject(parent)
{
}

DisPlayInfo::~DisPlayInfo()
{
}

void DisPlayInfo::setIdienfier(QString displayId)
{
    m_Idienfier = displayId;
}

QString DisPlayInfo::Idienfier()
{
    return  m_Idienfier;
}

void DisPlayInfo::setRect(QRect &rect)
{
    m_Rect = rect;
}

const QRect &DisPlayInfo::getDisPlayRect()
{
    return  m_Rect;
}

DisPlayInfo *DisPlayInfo::clone()
{
    DisPlayInfo * info = new DisPlayInfo;
    info->setIdienfier(m_Idienfier);
    info->setRect(m_Rect);
    *(info->OutputList()) << m_OutputList;
    return info;
}

QList<QString> *DisPlayInfo::OutputList()
{
    return &m_OutputList;
}

void DisPlayInfo::expandRect(const QList<QRect> & list)
{ 
     int minx =0;
     int miny=0;
     int maxx=0;
     int maxy=0;
     QRect rect = list.at(0);
      rect.getCoords(&minx,&miny,&maxx,&maxy);
     for(int i=0;i<list.count();i++){
         int temx1;
         int temy1;
         int temx2;
         int temy2;
         rect = list.at(i);
         rect.getCoords(&temx1,&temy1,&temx2,&temy2);
         if(minx > temx1){
                minx = temx1;
         }
         if(maxx < temx2){
             maxx = temx2;
         }
         if(miny > temy1){
             miny = temy1;
         }
         if(maxy < temy2){
             maxy = temy2;
         }
     }
     m_Rect.setCoords(minx,miny,maxx,maxy);
}
