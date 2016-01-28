//
// Created by matteo on 11/01/16.
//

#include "Measurement.h"

#include <iostream>
#include "DefendingMeasurement.h"
#include "DribblingMeasurement.h"
#include "PaceMeasurement.h"
#include "PassingMeasurement.h"
#include "PhysicalMeasurement.h"
#include "ShootingMeasurement.h"

Measurement *Measurement::newMeasurement(float raw_value, float value, Measurement::type type)
{
    switch (type) {
    case Measurement::defending:
        return new DefendingMeasurement(raw_value, value);
    case Measurement::dribbling:
        return new DribblingMeasurement(raw_value, value);
    case Measurement::pace:
        return new PaceMeasurement(raw_value, value);
    case Measurement::passing:
        return new PassingMeasurement(raw_value, value);
    case Measurement::physical:
        return new PhysicalMeasurement(raw_value, value);
    case Measurement::shooting:
        return new ShootingMeasurement(raw_value, value);

    case Measurement::null:
        std::clog << "null type measurement entered: ";
    default:
        std::clog << "Invalid measurement type!" << std::endl;
        return nullptr;
    }
}
