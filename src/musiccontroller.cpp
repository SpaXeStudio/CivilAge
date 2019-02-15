#include "musiccontroller.h"

Q_LOGGING_CATEGORY(Music, "ca.music")

namespace civilage {

MusicController::MusicController(QObject *parent, bool autoPlay, float volume)
    : QObject(parent)
    , play_state_check_timer(new QTimer(this))
    , current_pos(-1)
{
    connect(play_state_check_timer, &QTimer::timeout, this, &MusicController::check_music_state);
    QDirIterator it(QLatin1String(":/music"));
    while (it.hasNext()) {
        QResource *res = new QResource(it.next());
        resource_list.push_back(res);
    }

    setVolume(volume);

    if (autoPlay) {
        skip();
    }
}

void MusicController::changeLocation(AppLocation location)
{
    switch (location) {
    case AppLocation::MAIN_SCREEN:
        pause(false);
        break;
    case AppLocation::GAME_SCREEN:
        pause(false);
        break;
    case SETTINGS_SCREEN:
        pause(true);
        break;
    }
}

QResource *MusicController::get_random_resource()
{
    qint32 randPos = QRandomGenerator::global()->bounded(resource_list.size());

    // ensure we will not play the same song twice
    if (randPos == current_pos && resource_list.size() > 1) {
        if (++randPos == resource_list.size()) {
            randPos = 0;
        }
    }
    current_pos = randPos;

    return resource_list[current_pos];
}

void MusicController::play()
{
    emit currentSongChanged(currentSong());
    qCInfo(Music()) << "playing:" << currentSong();
    music.play();

    play_state_check_timer->start(2000);
}

void MusicController::pause(bool state)
{
    if(state) {
        music.pause();
        qCDebug(Music) << "paused";
    } else if (music.getStatus() != sf::SoundStream::Status::Playing){
        music.play();
        qCDebug(Music) << "resumed";
    }
}

void MusicController::skip()
{
    stop();
    qCDebug(Music) << "skipping";
    QResource *randResource = get_random_resource();
    music.openFromMemory(randResource->data(), randResource->size());
    play();
}

void MusicController::stop()
{
    music.stop();
}

void MusicController::check_music_state()
{
    if (music.getStatus() == sf::SoundStream::Status::Stopped) {
        skip();
    }
}

} // namespace civilage
