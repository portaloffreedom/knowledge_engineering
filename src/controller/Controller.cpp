//
// Created by matteo on 08/01/16.
//

#include <iostream>
#include <QQmlContext>
#include "Controller.h"
#include "measurements/Exercise.h"
#include "measurements/Measurement.h"

Controller::Controller(int argc, char** argv)
        : QApplication(argc, argv),
          engine(nullptr),
          window(nullptr)
{
}

Controller::~Controller() {
    saveData();
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

#define SAVE_FILENAME "data.json"
#define VERSION_FIELD "version"
#define SAVING_VERSION "1.0"
#define PLAYERS_FIELD "players"

bool Controller::loadData() {
    //playerList = new QList<Player *>;
    playerQmlList = new QQmlListProperty<Player>(this, playerList);
    /*
    createPlayer("Matteo", "De Carlo", 175.0, NULL, false);
    createPlayer("Ruben", "Sikkes", 184.0, NULL, false);
    playerList[0]->statistics()->pace()->resetClasses();
    playerList[0]->statistics()->pace()->addClass(Class(Class::Type::RELATIVE_DIFFERENCE, Class::Value::GOOD));
    playerList[1]->statistics()->physical()->resetClasses();
    playerList[1]->statistics()->physical()->addClass(Class(Class::Type::ABSOLUTE_DIFFERENCE, Class::Value::GOOD));
    playerList[1]->statistics()->physical()->addClass(Class(Class::Type::RELATIVE_DIFFERENCE, Class::Value::BAD));
    return true;
    */

    QFile loadFile(QStringLiteral(SAVE_FILENAME));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    const QJsonObject mainObject = loadDoc.object();

    const QString version = mainObject[VERSION_FIELD].toString();
    if (version.compare(SAVING_VERSION) != 0) {
        //TODO conversion to new format function
        qWarning("version incopatible, loading discarded");
        return false;
    }

    const QJsonArray playerArray = mainObject[PLAYERS_FIELD].toArray();
    for (auto it = playerArray.constBegin(); it < playerArray.constEnd(); it++) {
         Player *p = new Player();
         playerList.append(p);

         p->readJSON((*it).toObject());
    }

    return true;
}

bool Controller::saveData() const
{
    QFile saveFile(QStringLiteral(SAVE_FILENAME));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    // saving data creation section
    QJsonObject savingObject;
    savingObject[VERSION_FIELD] = SAVING_VERSION;

    QJsonArray playerArray;

    foreach (const Player *player, playerList) {
        QJsonObject playerObject;
        player->writeJSON(playerObject);
        playerArray.append(playerObject);
    }

    savingObject[PLAYERS_FIELD] = playerArray;

    // saving to disk
    QJsonDocument saveDoc(savingObject);
    saveFile.write(saveDoc.toJson());

    return true;
}

void Controller::loadContext() {
    Statistic::RegisterQmlType();
    PlayerStatistics::RegisterQmlType();
    Player::RegisterQmlType();
    PlayerStatistics::RegisterQmlType();
    Statistic::RegisterQmlType();
    Measurement::RegisterQmlType();
    Exercise::RegisterQmlType();

    loadData();

    QQmlContext *context = engine->rootContext();
    context->setContextProperty("appController", this);
}

void Controller::createPlayer(const QString &name, const QString &surname, qreal height, void *picture, bool special) {
    playerList.append(new Player(this, name, surname, height, picture, special));
    emit playersChanged(playerQmlList);
}
