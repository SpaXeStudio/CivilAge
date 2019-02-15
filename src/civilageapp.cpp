#include "civilageapp.h"

Q_LOGGING_CATEGORY(App, "ca.app")

namespace civilage {

CivilAgeApp::CivilAgeApp(int &argc, char **argv)
    : QObject(nullptr)
    , qapp(CreateApplication(argc, argv))
    , qengine(new QQmlApplicationEngine)
    , music_controller(new MusicController(this))
    , sound_controller(new SoundController(this))
{
    connect(qapp, &QGuiApplication::applicationStateChanged, this, &CivilAgeApp::handleApplicationStateChanged);
    InitQMLEngine();
}

CivilAgeApp::~CivilAgeApp()
{
    delete music_controller;
    delete sound_controller;
}

int CivilAgeApp::Run()
{
    return qapp->exec();
}

void CivilAgeApp::handleApplicationStateChanged(Qt::ApplicationState state)
{
    qCDebug(App) << "state changed to" << state;
#ifdef Q_OS_ANDROID
    // TODO: Qt::ApplicationActive in splitscreen
    music_controller->pause(state != Qt::ApplicationActive);
#else
    music_controller->pause(state == Qt::ApplicationSuspended);
#endif
}

QGuiApplication *CivilAgeApp::CreateApplication(int &argc, char **argv)
{
    log::Logger::Init();
    log::Logger::AddTarget(std::make_shared<log::FileLogger>());
    log::Logger::AddTarget(std::make_shared<log::stdoutLogger>());

    qCInfo(App) << "Initialized logger";

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication *qapp = new QGuiApplication(argc, argv);

    qCDebug(App) << "created qt app";

    return qapp;
}

void CivilAgeApp::InitQMLEngine()
{
    qmlRegisterType<MainMenuWindow>("CivilAge.MainMenuWindow", 1, 0, "MainMenuWindow");
    qmlRegisterType<GameWindow>("CivilAge.GameWindow", 1, 0, "GameWindow");
    qmlRegisterType<Squircle>("CivilAge.GameScreen", 1, 0, "GameScreen");

    qengine->rootContext()->setContextProperty("musicController", music_controller);
    qengine->rootContext()->setContextProperty("soundController", sound_controller);

    qengine->load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
}

} // namespace civilage
