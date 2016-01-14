//
// Created by matteo on 08/01/16.
//

#include <iostream>
#include <QQmlContext>
#include "Controller.h"

#include "Player.h"

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
    QQmlComponent* mainQmlView = new QQmlComponent(engine, this);
    connect(engine, SIGNAL(quit()), this, SLOT(quit()));

    mainQmlView->loadUrl(QUrl("qrc:///qml/window.qml"));
    if (!mainQmlView->isReady()) {
        std::cerr << mainQmlView->errorString().toStdString() << std::endl;
        std::exit(-1);
    }

    QObject *topLevel = mainQmlView->create();
    window = qobject_cast<QQuickWindow*>(topLevel);

    loadContext();
}

void Controller::loadData() {
    this->playerList = new QList<QObject *>;
    this->playerList->append(new Player(this, "Matteo", "De Carlo", 175.0, NULL, false));
    this->playerList->append(new Player(this, "Ruben", "Sikkes", 180.0, NULL, true));
}

#include <QJsonArray>

void Controller::loadContext() {
    loadData();

    QQmlContext *context = engine->rootContext();
    std::cout << "number of elements in player list:   " << playerList->size() << std::endl;
    std::cout << "number of elements after conversion: " << QVariant::fromValue((*playerList)).toJsonArray().size() <<
    std::endl;
    context->setContextProperty("playerList", QVariant::fromValue((*playerList)));


    QStringList dataList;
    dataList.append("Item 1");
    dataList.append("Item 2");
    dataList.append("Item 3");
    dataList.append("Item 4");

    context->setContextProperty("_playerList", QVariant::fromValue(dataList));
}
