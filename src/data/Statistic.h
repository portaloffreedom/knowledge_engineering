//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_STATISTIC_H
#define KNOWLEDGE_ENGINEERING_STATISTIC_H

#include <list>
#include <QObject>
#include <QtQml>
#include "Class.h"

class Statistic : public QObject {
    Q_OBJECT

    Q_PROPERTY(qreal averageValue READ averageValue NOTIFY averageValueChange)
    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(bool isOutstanding READ isOutstanding NOTIFY isOutstandingChanged)
    Q_PROPERTY(bool isOutstandingGood READ isOutstandingGood NOTIFY isOutstandingGoodChanged)
    Q_PROPERTY(bool hasSuddenChanged READ hasSuddenChanged NOTIFY hasSuddenChangedChanged)
    Q_PROPERTY(bool hasSuddenChangedGood READ hasSuddenChangedGood NOTIFY hasSuddenChangedGoodChanged)
    Q_PROPERTY(bool isNormal READ isNormal NOTIFY isNormalChanged)

public:
    static void RegisterQmlType() {
        qmlRegisterType<Statistic>("org.covolunablu", 1, 0, "Statistic");
    }

    struct Boundaries {
        qreal lower;
        qreal upper;
    };

    Statistic(QObject *parent = nullptr);
    Statistic(const Statistic *statistic);
    virtual ~Statistic() {}

    qreal averageValue();
    Q_INVOKABLE virtual QString getName() {
        return QString("invalid");
    }

    virtual void addValue(float value) {
        this->averageHistory.append(value);
        emit averageValueChange();
    }

    qreal last_value() {
        return averageHistory.last();
    }

    void addClass(Class _class);
    void resetClasses();

    bool isOutstanding();
    bool isOutstandingGood();
    bool hasSuddenChanged();
    bool hasSuddenChangedGood();
    bool isNormal();

    Boundaries boundaries;

    void writeJSON(QJsonObject &obj) const;
    void readJSON(const QJsonObject &obj);

private:
    QList<qreal> averageHistory;
    QList<Class> classes;

    Class *hasClass(Class::Type);


signals:
    void averageValueChange();
    void isOutstandingChanged();
    void isOutstandingGoodChanged();
    void hasSuddenChangedChanged();
    void hasSuddenChangedGoodChanged();
    void isNormalChanged();
};

Q_DECLARE_METATYPE(Statistic*)

#endif //KNOWLEDGE_ENGINEERING_STATISTIC_H
