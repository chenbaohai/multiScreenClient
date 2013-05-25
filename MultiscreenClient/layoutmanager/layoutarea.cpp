#include "layoutarea.h"

LayoutArea::LayoutArea()
{

}
LayoutArea::LayoutArea(int irow,int icol,int irowspan,int icolspan)
{
    col=icol;
    row=irow;
    rowspan=irowspan;
    colspan=icolspan;
}
