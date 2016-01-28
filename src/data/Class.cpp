//
// Created by matteo on 11/01/16.
//

#include "Class.h"

#define TYPE_FIELD "type"
#define VALUE_FIELD "value"

void Class::writeJSON(QJsonObject &obj) const
{
    obj[TYPE_FIELD] = typeToString(this->type);
    obj[VALUE_FIELD] = valueToString(this->value);
}

void Class::readJSON(const QJsonObject &obj)
{
    this->type = typeFromString(obj[TYPE_FIELD].toString());
    this->value = valueFromString(obj[VALUE_FIELD].toString());
}

#define TYPE_NORMAL "normal"
#define TYPE_ABSOLUTE_DIFFERENCE "absolute_difference"
#define TYPE_RELATIVE_DIFFERENCE "relative_difference"

#define VALUE_GOOD "good"
#define VALUE_BAD "bad"

QString Class::typeToString(Class::Type t)
{
    switch (t) {
    case Class::NORMAL:
        return QStringLiteral(TYPE_NORMAL);
    case Class::ABSOLUTE_DIFFERENCE:
        return QStringLiteral(TYPE_ABSOLUTE_DIFFERENCE);
    case Class::RELATIVE_DIFFERENCE:
        return QStringLiteral(TYPE_RELATIVE_DIFFERENCE);
    default:
        qWarning("Class::typeToString -> unreconized type");
        return QStringLiteral("");
    }
}

QString Class::valueToString(Class::Value v)
{
    switch (v) {
    case Class::GOOD:
        return QStringLiteral(VALUE_GOOD);
    case Class::BAD:
        return QStringLiteral(VALUE_BAD);
    default:
        qWarning("Class::valueToString -> unreconized value");
        return QStringLiteral("");
    }
}

Class::Type Class::typeFromString(const QString &s)
{
    if (s.compare(TYPE_NORMAL) == 0) {
        return Type::NORMAL;
    } else if (s.compare(TYPE_ABSOLUTE_DIFFERENCE) == 0) {
        return Type::ABSOLUTE_DIFFERENCE;
    } else if (s.compare(TYPE_RELATIVE_DIFFERENCE) == 0) {
        return Type::RELATIVE_DIFFERENCE;
    } else {
        qWarning("Class::typeFromString -> unreconized type");
        return Type::NORMAL;
    }
}

Class::Value Class::valueFromString(const QString &s)
{
    if (s.compare(VALUE_GOOD) == 0) {
        return Value::GOOD;
    } else if (s.compare(VALUE_BAD) == 0) {
        return Value::BAD;
    } else {
        qWarning("Class::valueFromString -> unreconized value");
        return Value::GOOD;
    }
}
