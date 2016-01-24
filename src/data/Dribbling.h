//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_DRIBBLING_H
#define KNOWLEDGE_ENGINEERING_DRIBBLING_H

#include "Statistic.h"

class Dribbling : public Statistic {
public:
    Dribbling(QObject *parent = nullptr) : Statistic(parent) {}
    Dribbling(const Dribbling* copy);

    virtual QString getName() override {
        return QString("Dribbling");
    }
};


#endif //KNOWLEDGE_ENGINEERING_DRIBBLING_H
