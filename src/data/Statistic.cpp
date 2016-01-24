//
// Created by matteo on 11/01/16.
//

#include "Statistic.h"

Statistic::Statistic(QObject *parent) :
    QObject(parent),
    boundaries({0,100})
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
    avarageHistory(statistic->avarageHistory),
    boundaries(statistic->boundaries),
    classes(statistic->classes)
{

}

qreal Statistic::avarageValue() {
    qreal avarage = 0;
    int i = 0;
    for (qreal value: avarageHistory) {
        avarage += value;
        i++;
    }

    if (i > 0)
        avarage /= i;

    return avarage;
}

void Statistic::addClass(Class::Type type, Class::Value value)
{
    if (type == Class::Type::NORMAL) {
        Q_ASSERT(classes.length() == 0);
        value = Class::Value::GOOD;
    }
    classes.append(Class(type, value));

    emit avarageValueChange();
    emit isOutstandingChanged();
    emit isOutstandingGoodChanged();
    emit hasSuddenChangedChanged();
    emit hasSuddenChangedGoodChanged();
    emit isNormalChanged();
}

void Statistic::resetClasses()
{
    classes.clear();
    emit avarageValueChange();
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
