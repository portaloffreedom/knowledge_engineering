//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_DEFENDING_H
#define KNOWLEDGE_ENGINEERING_DEFENDING_H

#include "Statistic.h"

class Defending : public Statistic {
public:
    Defending(QObject *parent = nullptr) : Statistic(parent) {}
    Defending(const Defending* copy) :
        Statistic(copy) {}

    virtual QString getName() override {
        return QString("Defending");
    }
};


#endif //KNOWLEDGE_ENGINEERING_DEFENDING_H
