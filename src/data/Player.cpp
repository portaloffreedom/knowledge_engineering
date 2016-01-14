//
// Created by matteo on 11/01/16.
//

#include "Player.h"

unsigned int Player::privateIDGenerator() {
    static unsigned int privateIDCounter = 0;
    return ++privateIDCounter;
}

Player::Player(QObject *parent, const QString &name, const QString &surname, qreal height, void *picture, bool special)
        : QObject(parent)
          , name(name)
          , surname(surname)
          , height(height)
          , picture(picture)
          , special(special) {

    privateID = this->privateIDGenerator();
}
