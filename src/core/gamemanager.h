#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QVector>

#include "../core/units/entity.h"

class GameManager : public QObject
{
    Q_OBJECT
public:
    explicit GameManager(QObject *parent = nullptr);

signals:

public slots:

private:
    QVector<Entity *> selected_entities;
};

#endif // GAMEMANAGER_H
