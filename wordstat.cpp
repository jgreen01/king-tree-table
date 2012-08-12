#include "wordstat.h"

#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QtAlgorithms>
#include <QDebug>
#include <QChar>

#include <blocks.h>

// will construct the blocks
// atleast the numOWords and name

bool comp_numOwords(blocks& lhs, blocks& rhs){
    return (lhs.getNumOWords() > rhs.getNumOWords());
}

void WordStat::genWordList(QString file, QList<blocks> &list){

    QFile fp(file);
    if(!fp.open(QIODevice::ReadOnly))
        return;

    QTextStream stream(&fp);

    QString line;

    // reads file
    while(!stream.atEnd()){

        line = stream.readLine();

        QStringList lineWords(line.split(' ',
                                         QString::SkipEmptyParts,
                                         Qt::CaseInsensitive));
        removeJunkList(lineWords);

        for(int i = 0; i < lineWords.size(); i++){ // each word in line
            bool inList = false;

            QString word = lineWords.at(i).toLower();
            removeJunk(word);

            // checks if word is in list
            QList<blocks>::iterator it;
            for(it = list.begin(); it != list.end(); it++){

                // is word in list
                if(word == (*it).getName()){
                    (*it).incNumOWords();
                    inList = true;
                }
            }

            // add to list if word wasn't found
            if(!inList){
                blocks newBlock;
                newBlock.setName(word);
                newBlock.setNumOWords(1);
                list.append(newBlock);
            }
        }
    }
    // sorts list
    qSort(list.begin(),list.end(),comp_numOwords);
}

int WordStat::wordsInList(QList<blocks> &list){

    int total = 0;

    QList<blocks>::iterator it;
    for(it = list.begin(); it != list.end(); it++){
        total += (*it).getNumOWords();
    }

    return total;
}

void WordStat::removeJunkList(QStringList &junkieStrings){
    junkieStrings.replaceInStrings(".","",Qt::CaseInsensitive);
    junkieStrings.replaceInStrings(";","",Qt::CaseInsensitive);
    junkieStrings.replaceInStrings(":","",Qt::CaseInsensitive);
    junkieStrings.replaceInStrings(",","",Qt::CaseInsensitive);
    junkieStrings.replaceInStrings("?","",Qt::CaseInsensitive);
    junkieStrings.replaceInStrings("!","",Qt::CaseInsensitive);
    junkieStrings.replaceInStrings("[","",Qt::CaseInsensitive);
    junkieStrings.replaceInStrings("]","",Qt::CaseInsensitive);
    junkieStrings.replaceInStrings("(","",Qt::CaseInsensitive);
    junkieStrings.replaceInStrings(")","",Qt::CaseInsensitive);
}

void WordStat::removeJunk(QString &junkieString){
    if(junkieString.endsWith(QChar('-'),Qt::CaseInsensitive))
        junkieString.remove(QChar('-'),Qt::CaseInsensitive);

    if(junkieString.startsWith(QChar('\''),Qt::CaseInsensitive))
        junkieString.remove(QChar('\''),Qt::CaseInsensitive);

    if(junkieString.endsWith(QChar('\''),Qt::CaseInsensitive))
        junkieString.remove(QChar('\''),Qt::CaseInsensitive);
}
