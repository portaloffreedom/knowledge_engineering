//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_PASSINGMEASUREMENT_H
#define KNOWLEDGE_ENGINEERING_PASSINGMEASUREMENT_H

#include "Measurement.h"

class PassingMeasurement : public Measurement {
public:
    PassingMeasurement(float raw_value, float value)
        : Measurement(raw_value, value)
    {
        m_type = type::passing;
    }
};


class Vision : public PassingMeasurement {

};

class Crossing : public PassingMeasurement {

};

class FreeKicks : public PassingMeasurement {

};

class ShortPassing : public PassingMeasurement {

};

class LongPassing : public PassingMeasurement {

};

class Curve : public PassingMeasurement {

};

#endif //KNOWLEDGE_ENGINEERING_PASSINGMEASUREMENT_H
