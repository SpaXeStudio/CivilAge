#ifndef ATTACKBEHAVIOUR_H
#define ATTACKBEHAVIOUR_H

#include <QVector>

#include "../units/entity.h"

class AttackBehaviour
{
public:
    AttackBehaviour();
private:
    QVector<Entity *> targets;
};

#endif // ATTACKBEHAVIOUR_H
