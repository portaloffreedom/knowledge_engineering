//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_DRIBBLINGMEASUREMENT_H
#define KNOWLEDGE_ENGINEERING_DRIBBLINGMEASUREMENT_H

#include "Measurement.h"

class DribblingMeasurement : public Measurement {
public:
    DribblingMeasurement(float raw_value, float value)
        : Measurement(raw_value, value)
    {
        m_type = type::dribbling;
    }
};


class Agility : public DribblingMeasurement {

};

class Balance : public DribblingMeasurement {

};

class Reactions : public DribblingMeasurement {

};

class BallControl : public DribblingMeasurement {

};

class Dribbling : public DribblingMeasurement {

};

#endif //KNOWLEDGE_ENGINEERING_DRIBBLINGMEASUREMENT_H
