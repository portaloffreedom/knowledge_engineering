#include "playerstatistics.h"
#include "normal.h"
#include "Class.h"

PlayerStatistics::PlayerStatistics(QObject *parent) : QObject(parent)
{
    init();
}

PlayerStatistics::PlayerStatistics(const PlayerStatistics &copy)
 : QObject(nullptr)
{
    m_dribbling = new Dribbling(copy.m_dribbling);
    m_shooting = new Shooting(copy.m_shooting);
    m_physical = new Physical(copy.m_physical);
    m_passing = new Passing(copy.m_passing);
    m_pace = new Pace(copy.m_pace);
    m_defending = new Defending(copy.m_defending);
}

void PlayerStatistics::monitorInference(Statistic *statistic)
{
    // specify normal
    Normal normal(
                statistic->boundaries.upper,
                statistic->boundaries.lower,
                statistic->averageValue()
    );

    // compare
    Difference difference = normal.difference(statistic->last_value());

    // classify
    classifyInferece(difference, statistic);
}

void PlayerStatistics::classifyInferece(Difference difference, Statistic *statistic)
{
    statistic->resetClasses();

    bool isNormal = true;

    Class classes[] = {
        Class(Class::Type::ABSOLUTE_DIFFERENCE, Class::Value::GOOD),
        Class(Class::Type::ABSOLUTE_DIFFERENCE, Class::Value::BAD),
        Class(Class::Type::RELATIVE_DIFFERENCE, Class::Value::GOOD),
        Class(Class::Type::RELATIVE_DIFFERENCE, Class::Value::BAD),
        Class(Class::Type::NORMAL), // this has to be the last one
    };

    // generate
    for (int i=0; i<5; i++) {
        Class candidate = classes[i];

        // specify & obtain
        qreal feature;
        switch (candidate.type) {
        case Class::NORMAL:
            if (isNormal) {
                statistic->addClass(candidate);
            }
            break;
        case Class::ABSOLUTE_DIFFERENCE:
            switch (candidate.value) {
            case Class::GOOD:
                feature = difference.upper;
                // match
                if (feature > 0) {
                    statistic->addClass(candidate);
                    isNormal = false;
                }
                break;
            case Class::BAD:
                feature = difference.lower;
                // match
                if (feature < 0) {
                    statistic->addClass(candidate);
                    isNormal = false;
                }
                break;
            }
            break;
        case Class::RELATIVE_DIFFERENCE:
            feature = difference.average;
            switch (candidate.value) {
            case Class::GOOD:
                // match
                if (feature > 10) {
                    statistic->addClass(candidate);
                    isNormal = false;
                }
                break;
            case Class::BAD:
                // match
                if (feature < -10) {
                    statistic->addClass(candidate);
                    isNormal = false;
                }
                break;
            }
            break;
        }
    }
}

void PlayerStatistics::init() {
    m_defending = new Defending();
    m_dribbling = new Dribbling();
    m_pace = new Pace();
    m_passing = new Passing();
    m_physical = new Physical();
    m_shooting = new Shooting();

    connect(this, SIGNAL(defendingChanged(Statistic*)), this, SLOT(monitorInference(Statistic *)));
    connect(this, SIGNAL(dribblingChanged(Statistic*)), this, SLOT(monitorInference(Statistic *)));
    connect(this, SIGNAL(paceChanged(Statistic*)), this, SLOT(monitorInference(Statistic *)));
    connect(this, SIGNAL(passingChanged(Statistic*)), this, SLOT(monitorInference(Statistic *)));
    connect(this, SIGNAL(physicalChanged(Statistic*)), this, SLOT(monitorInference(Statistic *)));
    connect(this, SIGNAL(shootingChanged(Statistic*)), this, SLOT(monitorInference(Statistic *)));
}

#define DEFENDING_FIELD "defending"
#define DRIBBLING_FIELD "dribbling"
#define PACE_FIELD "pace"
#define PASSING_FIELD "passing"
#define PHYSICAL_FIELD "physical"
#define SHOOTING_FIELD "shooting"

void PlayerStatistics::writeJSON(QJsonObject &obj) const
{
    QJsonObject defending_statistic,
            dribbling_statistic,
            pace_statistic,
            passing_statistic,
            physical_statistic,
            shooting_statistic;

    m_defending->writeJSON(defending_statistic);
    m_dribbling->writeJSON(dribbling_statistic);
    m_pace->writeJSON(pace_statistic);
    m_passing->writeJSON(passing_statistic);
    m_physical->writeJSON(physical_statistic);
    m_shooting->writeJSON(shooting_statistic);

    obj[DEFENDING_FIELD] = defending_statistic;
    obj[DRIBBLING_FIELD] = dribbling_statistic;
    obj[PACE_FIELD] = pace_statistic;
    obj[PASSING_FIELD] = passing_statistic;
    obj[PHYSICAL_FIELD] = physical_statistic;
    obj[SHOOTING_FIELD] = shooting_statistic;
}

void PlayerStatistics::readJSON(const QJsonObject &obj)
{
    const QJsonObject defending_statistic = obj[DEFENDING_FIELD].toObject(),
            dribbling_statistic = obj[DRIBBLING_FIELD].toObject(),
            pace_statistic = obj[PACE_FIELD].toObject(),
            passing_statistic = obj[PASSING_FIELD].toObject(),
            physical_statistic = obj[PHYSICAL_FIELD].toObject(),
            shooting_statistic = obj[SHOOTING_FIELD].toObject();

    m_defending->readJSON(defending_statistic);
    m_dribbling->readJSON(dribbling_statistic);
    m_pace->readJSON(pace_statistic);
    m_passing->readJSON(passing_statistic);
    m_physical->readJSON(physical_statistic);
    m_shooting->readJSON(shooting_statistic);
}
