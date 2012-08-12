#ifndef BLOCKS_H
#define BLOCKS_H

#include <QString>
#include <QRect>

class blocks
{
public:
    blocks();

    double getPercent();
    void setPercent(double percent_in);

    double getArea();
    void setArea(double area_in);

    int getNumOWords();
    void setNumOWords(int numOWords_in);
    void incNumOWords();

    QString getName();
    void setName(QString name_in);

    QRect getBox();
    void setBox(QRect box_in);

private:
    double percent;
    double area;
    int numOWords;
    QString name;
    QRect box;
};

#endif // BLOCKS_H
