#include "entity.h"

Entity::Entity(QObject *parent) : QObject(parent)
{

}

bool Entity::dead()
{
    return m_health > 0;
}
