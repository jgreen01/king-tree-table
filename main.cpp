#include <QtGui/QApplication>
#include "widget.h"

#include <QList>
#include <QString>
#include <QDebug>
#include <QGridLayout>

#include <wordstat.h>
#include <blocks.h>
#include <treemap.h>

#include <stdlib.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(825,625);
    w.show();

    QGridLayout *myLayout = new QGridLayout();

    QList<blocks> kingLearList;
    QString kingLearLoc = "../finalProject/kingLear.txt";

    WordStat kingLear;

    kingLear.genWordList(kingLearLoc,kingLearList);

    QList<blocks>::iterator it;
    for(it = kingLearList.begin(); it != kingLearList.end(); it++){
        qDebug() << (*it).getName() << '\t' << (*it).getNumOWords();
    }
    
    qDebug() << "words in list " << kingLear.wordsInList(kingLearList);

    treemap *kingLearTree = new treemap(&w,800,600,kingLearList);

    w.setLayout(myLayout);

    myLayout->addWidget(kingLearTree,0,0);

    return a.exec();
}
