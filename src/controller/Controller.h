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

    QQmlListProperty<Player> &players() {
        return *playerQmlList;
    }

protected:
    void setup();

    void loadData();

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
