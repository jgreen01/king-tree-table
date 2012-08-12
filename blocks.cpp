#include "blocks.h"

blocks::blocks(){
    percent = 0.0;
    area = 0.0;
    numOWords = 0;
    name = "none";
    QRect tempBox(0,0,0,0);
    box = tempBox;
}

double blocks::getPercent(){
    return this->percent;
}

void blocks::setPercent(double percent_in){
    this->percent = percent_in;
}

double blocks::getArea(){
    return this->area;
}

void blocks::setArea(double area_in){
    this->area = area_in;
}

int blocks::getNumOWords(){
    return this->numOWords;
}

void blocks::setNumOWords(int numOWords_in){
    this->numOWords = numOWords_in;
}

void blocks::incNumOWords(){
    this->numOWords++;
}

QString blocks::getName(){
    return this->name;
}

void blocks::setName(QString name_in){
    this->name = name_in;
}

QRect blocks::getBox(){
    return this->box;
}

void blocks::setBox(QRect box_in){
    this->box = box_in;
}
