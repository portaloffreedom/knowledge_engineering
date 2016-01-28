//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_EXERCISE_H
#define KNOWLEDGE_ENGINEERING_EXERCISE_H
#include "Measurement.h"

#include <iostream>
#include <QString>
#include <QObject>
#include <QtQml>

class Exercise : public QObject{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString measurementUnit READ measurementUnit WRITE setMeasurementUnit NOTIFY measurementUnitChanged)
    Q_PROPERTY(float minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(float maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(float average READ average WRITE setAverage NOTIFY averageChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)

public:
    static void RegisterQmlType() {
        qmlRegisterType<Exercise>("org.covolunablu", 1, 0, "Exercise");
    }

    Exercise(float minimum, float maximum, float average, const QString &measurement_unit, const QString &name, const QString &description, Measurement::type exercise_type, QObject *parent = nullptr)
        : QObject(parent)
        , m_minimum(minimum)
        , m_maximum(maximum)
        , m_average(average)
        , m_measurement_unit(measurement_unit)
        , m_name(name)
        , m_description(description)
        , exercise_type(exercise_type)
    {}

    Exercise(QObject *parent = nullptr)
        : Exercise(0, 0, 0, "", "", "", Measurement::type::null, parent) {}

    virtual ~Exercise() {}

    // calculates Measurement from raw_measurement
    Q_INVOKABLE Measurement *createMeasurement(float raw_measurement) {
        return Measurement::newMeasurement(raw_measurement, normalizeMeasurement(raw_measurement), exercise_type);
    }

    // getters
    QString &name() {
        return m_name;
    }

    QString &description() {
        return m_description;
    }

    QString &measurementUnit() {
        return m_measurement_unit;
    }

    float minimum() {
        return m_minimum;
    }

    float maximum() {
        return m_maximum;
    }

    float average() {
        return m_average;
    }

    QString type() {
        return Measurement::TypeToString(exercise_type);
    }

    // setters
    void setName(QString &name) {
        m_name = name;
    }

    void setDescription(QString &description) {
        m_description = description;
    }

    void setMeasurementUnit(QString &measurementUnit) {
        m_measurement_unit = measurementUnit;
    }

    void setMinimum(float minimum) {
        m_minimum = minimum;
    }

    void setMaximum(float maximum) {
        m_maximum = maximum;
    }

    void setAverage(float average) {
        m_average = average;
    }

    void setType(QString &type) {
        exercise_type = Measurement::StringToType(type);
    }

signals:
    void nameChanged(QString &name);
    void descriptionChanged(QString &description);
    void measurementUnitChanged(QString &measurementUnit);
    void minimumChanged(float value);
    void maximumChanged(float value);
    void averageChanged(float value);
    void typeChanged(Measurement::type value);

private:
    virtual float normalizeMeasurement(float raw_measurement);

    float m_minimum;
    float m_maximum;
    float m_average;
    QString m_measurement_unit;
    QString m_name;
    QString m_description;
    Measurement::type exercise_type;
};

Q_DECLARE_METATYPE(Exercise*)

#endif //KNOWLEDGE_ENGINEERING_EXERCISE_H
