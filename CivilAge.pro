TARGET = CivilAge
TEMPLATE = app

QT += qml quick
CONFIG += c++11 sanitizer

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT QT_NO_INFO_OUTPUT QT_NO_WARNING_OUTPUT

include(src/core/core.pri)

HEADERS += \
    src/ui/gamewindow.h \
    src/ui/mainmenuwindow.h \
    src/ui/gamescreen.h \
    src/civilageapp.h \
    src/musiccontroller.h \
    src/soundcontroller.h \
    src/ui/appwindow.h \
    src/applocation.h

SOURCES += \
        src/main.cpp \
    src/ui/gamewindow.cpp \
    src/ui/mainmenuwindow.cpp \
    src/ui/gamescreen.cpp \
    src/civilageapp.cpp \
    src/musiccontroller.cpp \
    src/soundcontroller.cpp \
    src/ui/appwindow.cpp

RESOURCES += \
    src/assets/audio/music/music.qrc \
    src/assets/audio/sounds.qrc \
    src/assets/images/images.qrc \
    src/ui/qml/qml.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android

    ANDROID_EXTRA_LIBS += \
        $$PWD/deps/SFML-lib/android/armeabi-v7a/libsfml-audio.so \
        $$PWD/deps/SFML-lib/android/armeabi-v7a/libsfml-system.so \
        $$PWD/deps/SFML/extlibs/libs-android/armeabi-v7a/libopenal.so
}

unix:!android: {
    target.path = /opt/$${TARGET}/bin

    # libraries should be placed into libs/ near executable manually for now
    QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/libs\'"

    CONFIG(debug, release|debug) {
        LIBS += -L$$PWD/deps/SFML-lib/unix -lsfml-audio-d -lsfml-system-d
    } else {
        LIBS += -L$$PWD/deps/SFML-lib/unix -lsfml-audio -lsfml-system
    }
}
android: {
    LIBS += -L$$PWD/deps/SFML-lib/android/armeabi-v7a -lsfml-audio -lsfml-system
}

!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/deps/SFML/include
DEPENDPATH += $$PWD/deps/SFML/include
