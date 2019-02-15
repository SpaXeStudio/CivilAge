#ifndef CIVILAGEAPP_H
#define CIVILAGEAPP_H

#include <memory>

#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLoggingCategory>

#include "applocation.h"

#include "ui/mainmenuwindow.h"
#include "ui/gamewindow.h"
#include "ui/gamescreen.h"

#include "soundcontroller.h"
#include "musiccontroller.h"

#include "src/core/logging/logger.h"

Q_DECLARE_LOGGING_CATEGORY(app)

namespace civilage {

class CivilAgeApp : public QObject
{
    Q_OBJECT

public:
    explicit CivilAgeApp(int &argc, char **argv);
    ~CivilAgeApp();

    int Run();

private slots:
    void handleApplicationStateChanged(Qt::ApplicationState state);

private:
    static QGuiApplication *CreateApplication(int &argc, char **argv);

    void InitQMLEngine();

    QGuiApplication *qapp;
    QQmlApplicationEngine *qengine;

    MusicController *music_controller;
    SoundController *sound_controller;
};

} // namespace civilage

#endif // CIVILAGEAPP_H
