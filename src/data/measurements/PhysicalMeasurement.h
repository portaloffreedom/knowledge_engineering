//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_PHYSICALMEASUREMENT_H
#define KNOWLEDGE_ENGINEERING_PHYSICALMEASUREMENT_H

#include "Measurement.h"

class PhysicalMeasurement : public Measurement {
public:
    PhysicalMeasurement(float raw_value, float value)
        : Measurement(raw_value, value)
    {
        m_type = type::physical;
    }
};


class Jumping : public PhysicalMeasurement {

};

class Stamina : public PhysicalMeasurement {

};

class Strength : public PhysicalMeasurement {

};

class Aggression : public PhysicalMeasurement {

};

#endif //KNOWLEDGE_ENGINEERING_PHYSICALMEASUREMENT_H
