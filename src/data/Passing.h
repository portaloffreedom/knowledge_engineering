//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_PASSING_H
#define KNOWLEDGE_ENGINEERING_PASSING_H

#include "Statistic.h"

class Passing : public Statistic {
public:
    Passing(QObject *parent = nullptr) : Statistic(parent) {}
    Passing(const Passing *copy) :
        Statistic(copy) {}

    virtual QString getName() override {
        return QString("Passing");
    }
};


#endif //KNOWLEDGE_ENGINEERING_PASSING_H
