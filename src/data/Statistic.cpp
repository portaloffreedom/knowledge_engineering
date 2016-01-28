//
// Created by matteo on 11/01/16.
//

#include "Statistic.h"

Statistic::Statistic(QObject *parent) :
    QObject(parent),
    boundaries({40,60})
{
    addClass(Class::Type::NORMAL);
}

//Statistic::Statistic(const Statistic &statistic) :
//    QObject(statistic.parent()),
//    avarageHistory(statistic.avarageHistory),
//    boundaries(statistic.boundaries)
//{

//}

Statistic::Statistic(const Statistic *statistic) :
    QObject(statistic->parent()),
    averageHistory(statistic->averageHistory),
    boundaries(statistic->boundaries),
    classes(statistic->classes)
{

}

qreal Statistic::averageValue() {
    qreal average = 0;
    int i = 0;
    for (qreal value: averageHistory) {
        average += value;
        i++;
    }

    if (i > 0)
        average /= i;

    return average;
}

void Statistic::addClass(Class _class)
{
    if (_class.type == Class::Type::NORMAL) {
        Q_ASSERT(classes.length() == 0);
        _class.value = Class::Value::GOOD;
    }
    classes.append(_class);

    emit isOutstandingChanged();
    emit isOutstandingGoodChanged();
    emit hasSuddenChangedChanged();
    emit hasSuddenChangedGoodChanged();
    emit isNormalChanged();
}

void Statistic::resetClasses()
{
    classes.clear();
    emit isOutstandingChanged();
    emit isOutstandingGoodChanged();
    emit hasSuddenChangedChanged();
    emit hasSuddenChangedGoodChanged();
    emit isNormalChanged();
}


Class *Statistic::hasClass(Class::Type type)
{
    for (Class &c: classes) {
        if (c.type == type)
            return &c;
    }
    return nullptr;
}

bool Statistic::isOutstanding()
{
    if (hasClass(Class::Type::ABSOLUTE_DIFFERENCE) == nullptr)
        return false;
    else
        return true;
}

bool Statistic::isOutstandingGood()
{
    Class *c = hasClass(Class::Type::ABSOLUTE_DIFFERENCE);
    if (c == nullptr)
        return false;
    if (c->value == Class::Value::GOOD)
        return true;
    else
        return false;
}

bool Statistic::hasSuddenChanged()
{
    if (hasClass(Class::Type::RELATIVE_DIFFERENCE) == nullptr)
        return false;
    else
        return true;
}

bool Statistic::hasSuddenChangedGood()
{
    Class *c = hasClass(Class::Type::RELATIVE_DIFFERENCE);
    if (c == nullptr)
        return false;
    if (c->value == Class::Value::GOOD)
        return true;
    else
        return false;
}

bool Statistic::isNormal()
{
    if (hasClass(Class::Type::NORMAL) == nullptr)
        return false;
    else
        return true;
}

#define AVERAGE_HISTORY_FIELD "history"
#define CLASSES_FIELD "classes"

void Statistic::writeJSON(QJsonObject &obj) const
{
    QJsonArray historyArray,
            classesArray;

    for (const qreal value: averageHistory) {
        historyArray.append(value);
    }
    for (const Class &c: classes) {
        QJsonObject class_obj;
        c.writeJSON(class_obj);
        classesArray.append(class_obj);
    }

    obj[AVERAGE_HISTORY_FIELD] = historyArray;
    obj[CLASSES_FIELD] = classesArray;
}

void Statistic::readJSON(const QJsonObject &obj)
{
    const QJsonArray historyArray = obj[AVERAGE_HISTORY_FIELD].toArray(),
            classesArray = obj[CLASSES_FIELD].toArray();

    averageHistory.clear();
    for (auto it = historyArray.constBegin(); it < historyArray.constEnd(); it++) {
        averageHistory.append((*it).toDouble());
    }

    classes.clear();
    for (auto it = classesArray.constBegin(); it < classesArray.constEnd(); it++) {
        const QJsonObject class_obj = (*it).toObject();
        Class c;
        c.readJSON(class_obj);
        classes.append(c);
    }

}
