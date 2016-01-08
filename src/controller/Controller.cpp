//
// Created by matteo on 08/01/16.
//

#include <iostream>
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
