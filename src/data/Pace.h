//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_PACE_H
#define KNOWLEDGE_ENGINEERING_PACE_H

#include "Statistic.h"

class Pace : public Statistic {
public:
    Pace(QObject *parent = nullptr) : Statistic(parent) {}
    Pace(const Pace *copy) :
        Statistic(copy) {}

    virtual QString getName() override {
        return QString("Pace");
    }
};


#endif //KNOWLEDGE_ENGINEERING_PACE_H
