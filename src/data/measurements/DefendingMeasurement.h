//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_DEFENDINGMEASUREMENT_H
#define KNOWLEDGE_ENGINEERING_DEFENDINGMEASUREMENT_H

#include "Measurement.h"

class DefendingMeasurement : public Measurement {
public:
    DefendingMeasurement(float raw_value, float value)
        : Measurement(raw_value, value)
    {
        m_type = type::defending;
    }
};


class Interceptions : public DefendingMeasurement {

};

class Heading : public DefendingMeasurement {

};

class Marking : public DefendingMeasurement {

};

class StandingTackle : public DefendingMeasurement {

};

class SlidingTackle : public DefendingMeasurement {

};


#endif //KNOWLEDGE_ENGINEERING_DEFENDINGMEASUREMENT_H
