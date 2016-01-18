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

    mainQmlView->loadUrl(QUrl("qrc:///qml/window.qml"));
    if (!mainQmlView->isReady()) {
        std::cerr << mainQmlView->errorString().toStdString() << std::endl;
        std::exit(-1);
    }

    QObject *topLevel = mainQmlView->create();
    window = qobject_cast<QQuickWindow*>(topLevel);
}

void Controller::loadData() {
    playerList = new QList<QObject *>;
    createPlayer("Matteo", "De Carlo", 175.0, NULL, false);
    createPlayer("Ruben", "Sikkes", 180.0, NULL, true);
}

#include <QJsonArray>

void Controller::loadContext() {
    loadData();

    QQmlContext *context = engine->rootContext();
    //std::cout << "number of elements in player list:   " << playerList->size() << std::endl;
    //std::cout << "number of elements after conversion: " << QVariant::fromValue((*playerList)).toJsonArray().size() <<
    //std::endl;
    context->setContextProperty("playerList", QVariant::fromValue((*playerList)));
    context->setContextProperty("appController", this);
}

void Controller::createPlayer(const QString &name, const QString &surname, qreal height, void *picture, bool special) {
    playerList->append(new Player(this, name, surname, height, picture, special));
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("playerList", QVariant::fromValue((*playerList)));
}
