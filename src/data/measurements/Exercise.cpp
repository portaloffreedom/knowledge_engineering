//
// Created by matteo on 11/01/16.
//

#include "Exercise.h"

float Exercise::normalizeMeasurement(float raw_measurement) {
    float measurement;
    if (raw_measurement > m_maximum) {
        std::clog << "Maximum for exercise exeeded" << std::endl;
        measurement = 100;
    } else if (raw_measurement < m_minimum) {
        std::clog << "Minimum for exercise exeeded" << std::endl;
        measurement = 0;
    } else {
        measurement = (raw_measurement - m_minimum) / (m_maximum - m_minimum);
        measurement *= 100;
    }

    return measurement;
}
