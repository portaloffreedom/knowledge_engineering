//
// Created by matteo on 08/01/16.
//

#include <iostream>
#include <QQmlContext>
#include "Controller.h"

Controller::Controller(int argc, char** argv)
        : QApplication(argc, argv),
          engine(nullptr),
          window(nullptr)
{
}

Controller::~Controller() {
    delete playerQmlList;
}

int Controller::exec() {
    setup();
    return QApplication::exec();
}

void Controller::setup() {
    engine = new QQmlEngine(this);
    loadContext();

    QQmlComponent* mainQmlView = new QQmlComponent(engine, this);
    connect(engine, SIGNAL(quit()), this, SLOT(quit()));

    mainQmlView->loadUrl(QUrl("qrc:///window.qml"));
    if (!mainQmlView->isReady()) {
        std::cerr << mainQmlView->errorString().toStdString() << std::endl;
        std::exit(-1);
    }

    QObject *topLevel = mainQmlView->create();
    window = qobject_cast<QQuickWindow*>(topLevel);
}

void Controller::loadData() {
    //playerList = new QList<Player *>;
    playerQmlList = new QQmlListProperty<Player>(this, playerList);
    createPlayer("Matteo", "De Carlo", 175.0, NULL, false);
    createPlayer("Ruben", "Sikkes", 180.0, NULL, true);
    playerList[0]->statistics()->pace()->resetClasses();
    playerList[0]->statistics()->pace()->addClass(Class::Type::RELATIVE_DIFFERENCE, Class::Value::GOOD);
    playerList[1]->statistics()->physical()->resetClasses();
    playerList[1]->statistics()->physical()->addClass(Class::Type::ABSOLUTE_DIFFERENCE, Class::Value::GOOD);
    playerList[1]->statistics()->physical()->addClass(Class::Type::RELATIVE_DIFFERENCE, Class::Value::BAD);
}

#include <QJsonArray>

void Controller::loadContext() {
    Statistic::RegisterQmlType();
    PlayerStatistics::RegisterQmlType();
    Player::RegisterQmlType();
    PlayerStatistics::RegisterQmlType();
    Statistic::RegisterQmlType();

    loadData();

    QQmlContext *context = engine->rootContext();
    context->setContextProperty("appController", this);
}

void Controller::createPlayer(const QString &name, const QString &surname, qreal height, void *picture, bool special) {
    playerList.append(new Player(this, name, surname, height, picture, special));
    emit playersChanged(playerQmlList);
}
