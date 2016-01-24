//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_SHOOTING_H
#define KNOWLEDGE_ENGINEERING_SHOOTING_H

#include "Statistic.h"

class Shooting : public Statistic {
public:
    Shooting(QObject *parent = nullptr) : Statistic(parent) {}
    Shooting(const Shooting *copy) :
        Statistic(copy) {}

    virtual QString getName() override {
        return QString("Shooting");
    }
};


#endif //KNOWLEDGE_ENGINEERING_SHOOTING_H
