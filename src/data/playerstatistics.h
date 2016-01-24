#ifndef PLAYERSTATISTICS_H
#define PLAYERSTATISTICS_H

#include "Defending.h"
#include "Dribbling.h"
#include "Pace.h"
#include "Passing.h"
#include "Physical.h"
#include "Shooting.h"

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

signals:
    void defendingChanged(Statistic *);
    void dribblingChanged(Statistic *);
    void paceChanged(Statistic *);
    void passingChanged(Statistic *);
    void physicalChanged(Statistic *);
    void shootingChanged(Statistic *);

public slots:

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
