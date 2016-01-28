//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_MEASUREMENT_H
#define KNOWLEDGE_ENGINEERING_MEASUREMENT_H

#include <QObject>
#include <QtQml>
#include <iostream>

class Measurement : public QObject {
    Q_OBJECT

    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(float raw_value READ raw_value WRITE setRaw_value NOTIFY raw_valueChanged)
public:
    static void RegisterQmlType() {
        qmlRegisterType<Measurement>("org.covolunablu", 1, 0, "Exercise");
    }

    Measurement(float raw_value, float value, QObject *parent = nullptr)
        : QObject(parent)
        , m_raw_value(raw_value)
        , m_value(value)
        , m_type(type::null)
        , date(QDateTime::currentDateTime())
    {}

    Measurement(QObject *parent = nullptr)
        : Measurement(0, 0, parent)
    {}

    virtual ~Measurement() {

    }

    enum type {
        null = 0,
        defending,
        dribbling,
        pace,
        passing,
        physical,
        shooting
    };

    static QString TypeToString(type t) {
        switch (t) {
        case Measurement::null:
            return QString("null");
        case Measurement::defending:
            return QString("defending");
        case Measurement::dribbling:
            return QString("dribbling");
        case Measurement::pace:
            return QString("pace");
        case Measurement::passing:
            return QString("passing");
        case Measurement::physical:
            return QString("physical");
        case Measurement::shooting:
            return QString("shooting");
        default:
            return QString("invalid");
        }
    }

    static type StringToType(const QString &s) {
        if (s.compare("defending") == 0) {
            return Measurement::defending;
        } else if (s.compare("dribbling") == 0) {
            return Measurement::dribbling;
        } else if (s.compare("pace") == 0) {
            return Measurement::pace;
        } else if (s.compare("passing") == 0) {
            return Measurement::passing;
        } else if (s.compare("physical") == 0) {
            return Measurement::physical;
        } else if (s.compare("shooting") == 0) {
            return Measurement::shooting;
        } else {
            return Measurement::null;
        }
    }

    static Measurement *newMeasurement(float raw_value, float value, type type);

    // getters
    float raw_value() {
        return m_raw_value;
    }

    float value() {
        return m_value;
    }

    type getType() {
        return m_type;
    }

    // setters
    void setRaw_value(float raw_value) {
        m_raw_value = raw_value;
    }

    void setValue(float value) {
        m_value = value;
    }

protected:
    // internal variables
    float m_raw_value;
    float m_value;
    const QDateTime date;
    type m_type;

signals:
    void valueChanged(float);
    void raw_valueChanged(float);
};

Q_DECLARE_METATYPE(Measurement*)



#endif //KNOWLEDGE_ENGINEERING_MEASUREMENT_H
