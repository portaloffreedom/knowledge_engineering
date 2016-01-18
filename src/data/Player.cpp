//
// Created by matteo on 11/01/16.
//

#include "Player.h"

unsigned int Player::privateIDGenerator() {
    static unsigned int privateIDCounter = 0;
    return ++privateIDCounter;
}

Player::Player(QObject *parent)
        : QObject(parent)
          , name("")
          , surname("")
          , height(0)
          , picture(nullptr)
          , special(false)
          , privateID(Player::privateIDGenerator()) {
}

Player::Player(const Player &player)
        : QObject(player.parent())
          , name(player.name)
          , surname(player.surname)
          , height(player.height)
          , picture(player.picture)
          , special(player.special)
          , privateID(player.privateID) {
}


Player::Player(QObject *parent, const QString &name, const QString &surname, qreal height, void *picture, bool special)
        : QObject(parent)
          , name(name)
          , surname(surname)
          , height(height)
          , picture(picture)
          , special(special)
          , privateID(Player::privateIDGenerator()) {
}
