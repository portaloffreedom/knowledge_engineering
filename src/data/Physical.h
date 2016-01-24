//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_PHYSICAL_H
#define KNOWLEDGE_ENGINEERING_PHYSICAL_H

#include "Statistic.h"

class Physical : public Statistic {
public:
    Physical(QObject *parent = nullptr) : Statistic(parent) {}
    Physical(const Physical *copy) :
        Statistic(copy) {}

    virtual QString getName() override {
        return QString("Physical");
    }
};


#endif //KNOWLEDGE_ENGINEERING_PHYSICAL_H
