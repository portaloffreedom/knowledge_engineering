#ifndef PLAYERSTATISTICS_H
#define PLAYERSTATISTICS_H

#include "Defending.h"
#include "Dribbling.h"
#include "Pace.h"
#include "Passing.h"
#include "Physical.h"
#include "Shooting.h"
#include "measurements/Measurement.h"
#include "difference.h"

class PlayerStatistics : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Statistic* defending READ defending NOTIFY defendingChanged)
    Q_PROPERTY(Statistic* dribbling READ dribbling NOTIFY dribblingChanged)
    Q_PROPERTY(Statistic* pace      READ pace      NOTIFY paceChanged     )
    Q_PROPERTY(Statistic* passing   READ passing   NOTIFY passingChanged  )
    Q_PROPERTY(Statistic* physical  READ physical  NOTIFY physicalChanged )
    Q_PROPERTY(Statistic* shooting  READ shooting  NOTIFY shootingChanged )
public:
    static void RegisterQmlType() {
        qmlRegisterType<PlayerStatistics>("org.covolunablu", 1, 0, "PlayerStatistics");
    }

    PlayerStatistics(QObject *parent = 0);
    PlayerStatistics(const PlayerStatistics &statistics);
    virtual ~PlayerStatistics() {}

    PlayerStatistics& operator=(const PlayerStatistics& copy) {
        m_dribbling = copy.m_dribbling;
        m_shooting = copy.m_shooting;
        m_physical = copy.m_physical;
        m_passing = copy.m_passing;
        m_pace = copy.m_pace;
        m_defending = copy.m_defending;
        return *this;
    }

    Statistic *defending() {
        return m_defending;
    }

    Statistic *dribbling() {
        return m_dribbling;
    }

    Statistic *pace() {
        return m_pace;
    }

    Statistic *passing() {
        return m_passing;
    }

    Statistic *physical() {
        return m_physical;
    }

    Statistic *shooting() {
        return m_shooting;
    }

    void insertMeasurement(Measurement *measurement) {
        Statistic *influenced_statistic;
        switch (measurement->getType()) {
        case Measurement::null:
            std::clog << "adding invalid measurement to player! (type null)" << std::endl;
            return;
            break;
        case Measurement::defending:
            influenced_statistic = defending();
            break;
        case Measurement::dribbling:
            influenced_statistic = dribbling();
            break;
        case Measurement::pace:
            influenced_statistic = pace();
            break;
        case Measurement::passing:
            influenced_statistic = passing();
            break;
        case Measurement::physical:
            influenced_statistic = physical();
            break;
        case Measurement::shooting:
            influenced_statistic = shooting();
            break;
        }

        influenced_statistic->addValue(measurement->value());

        switch (measurement->getType()) {
        case Measurement::null:
            std::clog << "adding invalid measurement to player! (type null) [2]" << std::endl;
            return;
            break;
        case Measurement::defending:
            emit shootingChanged(defending());
            break;
        case Measurement::dribbling:
            emit dribblingChanged(dribbling());
            break;
        case Measurement::pace:
            emit paceChanged(pace());
            break;
        case Measurement::passing:
            emit passingChanged(passing());
            break;
        case Measurement::physical:
            emit physicalChanged(physical());
            break;
        case Measurement::shooting:
            emit shootingChanged(shooting());
            break;
        }

        return;
    }

    void writeJSON(QJsonObject &obj) const;
    void readJSON(const QJsonObject &obj);

signals:
    void defendingChanged(Statistic *);
    void dribblingChanged(Statistic *);
    void paceChanged(Statistic *);
    void passingChanged(Statistic *);
    void physicalChanged(Statistic *);
    void shootingChanged(Statistic *);

public slots:
    void monitorInference(Statistic *);
    void classifyInferece(Difference difference, Statistic *statistic);

private:
    Dribbling *m_dribbling;
    Shooting *m_shooting;
    Physical *m_physical;
    Passing *m_passing;
    Pace *m_pace;
    Defending *m_defending;

    void init();
};

Q_DECLARE_METATYPE(PlayerStatistics*)

#endif // PLAYERSTATISTICS_H
