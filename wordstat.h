#ifndef WORDSTAT_H
#define WORDSTAT_H

#include <QList>
#include <QString>

#include <blocks.h>

class WordStat
{
public:
    //WordStat();
    void genWordList(QString file, QList<blocks> &list);
    int wordsInList(QList<blocks> &list);

private:
    void removeJunkList(QStringList &junkieStrings);
    void removeJunk(QString &junkieString);
};

#endif // WORDSTAT_H
