#ifndef LAYOUTAREA_H
#define LAYOUTAREA_H

class LayoutArea
{
public:
    LayoutArea();
    LayoutArea(int irow,int icol ,int irowspan,int icolspan);
    int col;
    int row;
    int rowspan;
    int colspan;
};

#endif // LAYOUTAREA_H
