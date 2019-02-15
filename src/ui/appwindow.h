#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QtQuick/QQuickItem>

#include "../applocation.h"

class AppWindow : public QQuickItem
{
    Q_OBJECT
public:
    AppWindow();

signals:
    void navigated(AppLocation location);
public slots:
};

#endif // APPWINDOW_H
