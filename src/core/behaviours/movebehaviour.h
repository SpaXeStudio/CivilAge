#ifndef MOVEBEHAVIOUR_H
#define MOVEBEHAVIOUR_H

#include <QPointF>

#include "../pathfinding/route.h"

class MoveBehaviour
{
public:
    MoveBehaviour();

private:
    QPointF destination;
    Route *route{};
};

#endif // MOVEBEHAVIOUR_H
