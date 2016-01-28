//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_PACEMEASUREMENT_H
#define KNOWLEDGE_ENGINEERING_PACEMEASUREMENT_H

#include "Measurement.h"

class PaceMeasurement : public Measurement {
public:
    PaceMeasurement(float raw_value, float value)
        : Measurement(raw_value, value)
    {
        m_type = type::pace;
    }
};


class Acceleration : public PaceMeasurement {

};

class SprintSpeed : public PaceMeasurement {

};

#endif //KNOWLEDGE_ENGINEERING_PACEMEASUREMENT_H
