#include "playerstatistics.h"

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

void PlayerStatistics::init() {
    m_dribbling = new Dribbling();
    m_shooting = new Shooting();
    m_physical = new Physical();
    m_passing = new Passing();
    m_pace = new Pace();
    m_defending = new Defending();
}
