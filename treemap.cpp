#include "treemap.h"

#include <QList>
#include <QString>
#include <QRect>
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QBrush>

#include <blocks.h>

treemap::treemap(QWidget *parent, double width_in,
                 double height_in, QList<blocks> &list) :
    QWidget(parent){
    winWidth = width_in;
    winHeight = height_in;

    workWidth = winWidth;
    workHeight = winHeight;

    currHeight = 0;
    currX = 0;
    currY = 0;

    totalArea = winWidth * winHeight;

    prepareBlocks(list);

    QList<blocks> newList;
    squarify(list,newList,findWidth());
}

treemap::~treemap(){

}

void treemap::paintEvent(QPaintEvent *){

    qDebug() << "drawing?";

    QPainter p(this);

    p.drawLine(1,1,100,100);

    QColor myBrushColor, myPenColor;

    myBrushColor.setRgb(0,255,0);
    myPenColor.setRgb(0,0,0);

    QBrush myBrush;
    myBrush.setColor(myBrushColor);
    myBrush.setStyle(Qt::SolidPattern);
    p.setBrush(myBrush);

    QPen myPen;
    myPen.setColor(myPenColor);
    myPen.setWidth(1);
    p.setPen(myPen);

    p.drawRect(0,0,200,200);

    QList<blocks>::iterator it;
    for(it = drawList.begin(); it != drawList.end();it++){
        p.drawRect((*it).getBox());
        if((*it).getArea() > 200)
            p.drawText((*it).getBox().x()+2,
                       (*it).getBox().y()+((*it).getBox().height()/2),
                       (*it).getName());
    }

}

/*explaination:
 * list is our list     // will change the list (pass by value)
 * currRow is a list of all blocks in the row we're working on
 *      row will change as we atempt to optizime the aspect ratio
 * width is the width of the current row */
void treemap::squarify(QList<blocks> list, QList<blocks> currRow, double width){

    QList<blocks> nextState = currRow; // the possible next iteration

    qDebug() << "blocks left in list " << list.size();

    // put next list value at beginning of nextState
    if(list.size() > 1)
        nextState.push_front(list.at(0));

    double currAspect = aspectRatio(currRow,width);
    double nextAspect = aspectRatio(nextState,width);

    // if end OR nextAspect is better than currAspect
    if(currAspect == 0 || (nextAspect < currAspect && nextAspect >= 1)){
        currRow.push_front(list.at(0));
        list.pop_front();
        currHeight = findHeight(currRow,width);

        if(list.size() > 0)
            squarify(list,currRow,width); // continue
        else
            makeBox(currRow); // end of list
    } else {
        // row is optimized
        makeBox(currRow);
        QList<blocks> newList;
        squarify(list,newList,findWidth());
    }
}

void treemap::makeBox(QList<blocks> row){

    double startX = currX;
    double startY = currY;

    if(!isVertical)
        if(workHeight != currHeight)
            currY = workHeight - currHeight;

    QList<blocks>::iterator it;
    for(it = row.begin(); it != row.end(); it++){
        double width;
        double height;

        // determines the correct width for the block based on area and height
        if(isVertical){
            width = currHeight;
            height = (*it).getArea()/currHeight;
        } else {
            width = (*it).getArea()/currHeight;
            height = currHeight;
        }

        QRect newBox(currX,currY,width,height);
        qDebug() << newBox << " name: " << (*it).getName();
        qDebug() << "currX: " << currX << " currY: " << currY;
        qDebug() << "width: " << width << " height: " << height;
        (*it).setBox(newBox);
        drawList.append(*it);

        // preparing for next block in the list
        if(isVertical)
            currY += height;
        else
            currX += width;
    }

    if(isVertical){
        currX += currHeight;
        currY = startY;
        workWidth -= currHeight;
    } else {
        currX = startX;
        currY = startY;
        workHeight -= currHeight;
    }

    currHeight = 0;
}

// decides whether to work vertically or horizonitally
// if vertical, width is the height
double treemap::findWidth(){

    if(workHeight > workWidth){
        isVertical = false;
        return workWidth;
    } else {
        isVertical = true;
        return workHeight;
    }
}

double treemap::findHeight(QList<blocks> &row, double width){
    double sum = 0;

    QList<blocks>::iterator it;
    for(it = row.begin(); it != row.end(); it++)
        sum += (*it).getArea();

    return sum/width;
}

double treemap::aspectRatio(QList<blocks> &row, double width){
    double areaSum = 0, max = -1, min = 99999;

    QList<blocks>::iterator it;
    for(it = row.begin(); it != row.end(); it++){
        areaSum += (*it).getArea();

        if((*it).getArea() > max)
            max = (*it).getArea();

        if((*it).getArea() < min)
            min = (*it).getArea();
    }

    double widthSq = width*width;
    double areaSumSq = areaSum*areaSum;

    double ratio1 = (widthSq*max)/areaSumSq;
    double ratio2 = areaSumSq/(widthSq*min);

    if(ratio1 > ratio2)
        return ratio1;
    else
        return ratio2;
}

void treemap::prepareBlocks(QList<blocks> &list){
    int wordSum = totalWords(list);

    QList<blocks>::iterator it;
    for(it = list.begin(); it != list.end(); it++){
        double percent = (double) (*it).getNumOWords() / (double) wordSum;
        double area = totalArea * percent;
        (*it).setPercent(percent);
        (*it).setArea(area);
    }
}

int treemap::totalWords(QList<blocks> &list){

    int total = 0;

    QList<blocks>::iterator it;
    for(it = list.begin(); it != list.end(); it++){
        total += (*it).getNumOWords();
    }

    return total;
}
