#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <QObject>
#include <QLoggingCategory>

#include "applocation.h"

Q_DECLARE_LOGGING_CATEGORY(Sound)

namespace civilage {

class SoundController : public QObject
{
    Q_OBJECT
public:
    explicit SoundController(QObject *parent = nullptr);

signals:

public slots:
    //void changeLocation(AppLocation location);
};

} // namespace civilage

#endif // SOUNDCONTROLLER_H
