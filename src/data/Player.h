//
// Created by matteo on 11/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_PLAYER_H
#define KNOWLEDGE_ENGINEERING_PLAYER_H

#include <string>
#include <QObject>
#include "Dribbling.h"
#include "Shooting.h"
#include "Physical.h"
#include "Passing.h"
#include "Pace.h"
#include "Defending.h"

class Player : public QObject {
Q_OBJECT

    Q_PROPERTY(QString name
                       READ getName
                       WRITE setName
                       NOTIFY nameChanged)
    Q_PROPERTY(QString surname
                       READ getSurname
                       WRITE setSurname
                       NOTIFY surnameChanged)
    Q_PROPERTY(qreal height
                       READ getHeight
                       WRITE setHeight
                       NOTIFY heightChanged)
    Q_PROPERTY(bool special
                       READ isSpecial
                       WRITE setSpecial
                       NOTIFY specialChanged)

public:
    Player(QObject *parent = nullptr);

    Player(const Player &player);
    Player(QObject *parent, const QString &name, const QString &surname, qreal height, void *picture, bool special);

    QString name;
    QString surname;
    qreal height;
    void *picture; //placeholder
    bool special;

    struct specialStatistics {
        Dribbling *dribbling;
        Shooting *shooting;
        Physical *physical;
        Passing *passing;
        Pace *pace;
        Defending *defending;
    };

    const QString &getName() const {
        return name;
    }

    const QString &getSurname() const {
        return surname;
    }

    qreal getHeight() const {
        return height;
    }

    bool isSpecial() const {
        return special;
    }

public slots:

    void setName(const QString &name) {
        Player::name = name;
    }


    void setSurname(const QString &surname) {
        Player::surname = surname;
    }


    void setHeight(qreal height) {
        Player::height = height;
    }


    void setSpecial(bool special) {
        Player::special = special;
    }

signals:

    void nameChanged();

    void surnameChanged();

    void heightChanged(qreal newValue);

    void specialChanged(bool newValue);

private:
    static unsigned int privateIDGenerator();
    unsigned int privateID;
};

Q_DECLARE_METATYPE(Player)

#endif //KNOWLEDGE_ENGINEERING_PLAYER_H
