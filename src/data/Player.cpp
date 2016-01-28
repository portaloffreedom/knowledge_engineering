//
// Created by matteo on 11/01/16.
//

#include "Player.h"

unsigned int Player::privateIDGenerator() {
    static unsigned int privateIDCounter = 0;
    return ++privateIDCounter;
}

void Player::init()
{
    this->m_statistics = new PlayerStatistics();
}

Player::Player(QObject *parent)
        : QObject(parent)
          , name("")
          , surname("")
          , height(0)
          , picture(nullptr)
          , special(false)
          , privateID(Player::privateIDGenerator()) {
    init();
}

Player::Player(const Player &player)
        : QObject(player.parent())
          , name(player.name)
          , surname(player.surname)
          , height(player.height)
          , picture(player.picture)
          , special(player.special)
          , privateID(player.privateID) {
    init();
}


Player::Player(QObject *parent, const QString &name, const QString &surname, qreal height, void *picture, bool special)
        : QObject(parent)
          , name(name)
          , surname(surname)
          , height(height)
          , picture(picture)
          , special(special)
        , privateID(Player::privateIDGenerator()) {
    init();
}

Player::~Player()
{
    delete m_statistics;
}

#define NAME_FIELD "name"
#define SURNAME_FIELD "surname"
#define HEIGHT_FIELD "height"
#define SPECIAL_FIELD "special"
#define PRIVATE_ID_FIELD "private_id"
#define STATISTICS "statistcs"

void Player::writeJSON(QJsonObject &obj) const
{
    obj[NAME_FIELD] = this->name;
    obj[SURNAME_FIELD] = this->surname;
    obj[HEIGHT_FIELD] = this->height;
    obj[SPECIAL_FIELD] = this->special;
    obj[PRIVATE_ID_FIELD] = int(this->privateID);

    QJsonObject statistics;
    m_statistics->writeJSON(statistics);
    obj[STATISTICS] = statistics;
}

void Player::readJSON(const QJsonObject &obj)
{
    this->name = obj[NAME_FIELD].toString();
    this->surname = obj[SURNAME_FIELD].toString();
    this->height = obj[HEIGHT_FIELD].toDouble();
    this->special = obj[SPECIAL_FIELD].toBool();
    this->privateID = obj[PRIVATE_ID_FIELD].toInt();

    const QJsonObject statistics =  obj[STATISTICS].toObject();
    m_statistics->readJSON(statistics);
}
