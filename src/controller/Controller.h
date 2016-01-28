//
// Created by matteo on 08/01/16.
//

#ifndef KNOWLEDGE_ENGINEERING_CONTROLLER_H
#define KNOWLEDGE_ENGINEERING_CONTROLLER_H

#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QQuickWindow>
#include <QApplication>
#include "Player.h"
#include "measurements/Measurement.h"

class Controller : public QApplication {
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<Player> players READ players NOTIFY playersChanged)

public:
    Controller(int argc, char** argv);
    Controller(const Controller &copy);
    Controller();
    virtual ~Controller();

    int exec();

    Q_INVOKABLE void createPlayer(const QString &name = "", const QString &surname = "", qreal height = 0,
                                  void *picture = nullptr, bool special = false);

    Q_INVOKABLE void insertMeasurement(int playerIndex, Measurement *measurement) {
        Player *player = playerList.at(playerIndex);
        player->addMeasurement(measurement);
    }

    QQmlListProperty<Player> &players() {
        return *playerQmlList;
    }

protected:
    void setup();

    bool loadData();
    bool saveData() const;

    void loadContext();

    QQmlEngine* engine;
    QQuickWindow* window;
    QList<Player*> playerList;
    QQmlListProperty<Player> *playerQmlList;

signals:
    void playersChanged(QQmlListProperty<Player> *);
};

Q_DECLARE_METATYPE(Controller)


#endif //KNOWLEDGE_ENGINEERING_CONTROLLER_H
