//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_CLASS_H
#define KNOWLEDGE_ENGINEERING_CLASS_H

#include <QJsonObject>

class Class {
public:
    enum Type {
        NORMAL,
        ABSOLUTE_DIFFERENCE,
        RELATIVE_DIFFERENCE,
    };

    enum Value {
        GOOD,
        BAD,
    };

    Class(Type type, Value value) :
        type(type), value(value) {}


    Class(Type type) :
        Class(type, Value::GOOD) {}

    Class() :
        Class(Type::NORMAL, Value::GOOD) {}

    void writeJSON(QJsonObject &obj) const;
    void readJSON(const QJsonObject &obj);

    static QString typeToString(Type t);
    static QString valueToString(Value v);
    static Type typeFromString(const QString &s);
    static Value valueFromString(const QString &s);

    Type type;
    Value value;
};


#endif //KNOWLEDGE_ENGINEERING_CLASS_H
