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

public:
    Controller(int argc, char** argv);
    virtual ~Controller();

    int exec();

    Q_INVOKABLE void createPlayer(const QString &name = "", const QString &surname = "", qreal height = 0,
                                  void *picture = nullptr, bool special = false);

protected:
    void setup();

    void loadData();

    void loadContext();

    QQmlEngine* engine;
    QQuickWindow* window;
    QList<QObject *> *playerList;
};


#endif //KNOWLEDGE_ENGINEERING_CONTROLLER_H
