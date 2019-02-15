#ifndef MUSICCONTROLLER_H
#define MUSICCONTROLLER_H

#include <QObject>
#include <QDirIterator>
#include <QResource>
#include <QTimer>
#include <QVector>
#include <QRandomGenerator>
#include <QLoggingCategory>

#include <SFML/Audio.hpp>

#include"applocation.h"

Q_DECLARE_LOGGING_CATEGORY(Music)

namespace civilage {

class MusicController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(QString currentSong READ currentSong NOTIFY currentSongChanged)
public:
    explicit MusicController(QObject *parent, bool autoPlay = true, float volume = 50);
    void play();
    void pause(bool state);

    float volume() const
    {
        return music.getVolume();
    }

    QString currentSong() const
    {
        if (current_pos == -1) {
            return "";
        }

        // assuming that path is :/.../audio.ogg
        return resource_list[current_pos]->fileName().section("/", -1).section(".", 0, 0);
    }

signals:
    void volumeChanged(int volume);
    void currentSongChanged(const QString song);

public slots:
    void setVolume(float volume)
    {
        music.setVolume(volume);
    }
    void changeLocation(AppLocation location);
    void skip();
    void stop();

private slots:
    void check_music_state();

private:
    QTimer *play_state_check_timer;
    QVector<QResource *> resource_list;
    qint32 current_pos;
    sf::Music music;

    QResource *get_random_resource();
};

} // namespace civilage

#endif // MUSICCONTROLLER_H
