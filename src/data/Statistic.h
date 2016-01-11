//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_STATISTIC_H
#define KNOWLEDGE_ENGINEERING_STATISTIC_H

#include <list>

class Statistic {
public:
    float avarage_value;
    std::list<float> avarage_history;

    struct Boundaries {
        float upper;
        float lower;
    } boundaries;
};


#endif //KNOWLEDGE_ENGINEERING_STATISTIC_H
