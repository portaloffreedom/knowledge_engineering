//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_SHOOTINGMEASUREMENT_H
#define KNOWLEDGE_ENGINEERING_SHOOTINGMEASUREMENT_H

#include "Measurement.h"

class ShootingMeasurement : public Measurement {
public:
    ShootingMeasurement(float raw_value, float value)
        : Measurement(raw_value, value)
    {
        m_type = type::shooting;
    }
};


class Positioning : public ShootingMeasurement {

};

class Finishing : public ShootingMeasurement {

};

class ShotPower : public ShootingMeasurement {

};

class LongShots : public ShootingMeasurement {

};

class Volleys : public ShootingMeasurement {

};

class Penalties : public ShootingMeasurement {

};

#endif //KNOWLEDGE_ENGINEERING_SHOOTINGMEASUREMENT_H
