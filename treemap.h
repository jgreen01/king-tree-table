#ifndef TREEMAP_H
#define TREEMAP_H

#include <QWidget>
#include <QList>

#include <blocks.h>

class treemap : public QWidget
{
    Q_OBJECT

public:
    explicit treemap(QWidget *parent, double width_in,
                     double height_in, QList<blocks> &list);
    ~treemap();

signals:

private:
    void paintEvent(QPaintEvent *);
    int totalWords(QList<blocks> &list);
    void squarify(QList<blocks> list, QList<blocks> currRow, double width);
    void makeBox(QList<blocks> row);
    void prepareBlocks(QList<blocks> &list);
    double aspectRatio(QList<blocks> &row, double width);
    double findHeight(QList<blocks> &row, double width);
    // toil and trouble
    double findWidth();
    QList<blocks> drawList;
    double winWidth;
    double winHeight;
    double workWidth;
    double workHeight;
    double totalArea;
    double currHeight;
    double currX;
    double currY;
    bool isVertical;

};

#endif // TREEMAP_H
