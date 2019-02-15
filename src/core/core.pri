INCLUDEPATH = $$PWD

HEADERS += \
    $$PWD/units/entity.h \
    $$PWD/gamemanager.h \
    $$PWD/behaviours/attackbehaviour.h \
    $$PWD/behaviours/movebehaviour.h \
    $$PWD/pathfinding/route.h \
    $$PWD/logging/logger.h

SOURCES += \
    $$PWD/units/entity.cpp \
    $$PWD/gamemanager.cpp \
    $$PWD/behaviours/attackbehaviour.cpp \
    $$PWD/behaviours/movebehaviour.cpp \
    $$PWD/pathfinding/route.cpp \
    $$PWD/logging/logger.cpp

RESOURCES += \
    $$PWD/graphics/shaders/shaders.qrc
