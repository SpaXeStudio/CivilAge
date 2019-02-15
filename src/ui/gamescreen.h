#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <math.h>

#include <QObject>
#include <QPointF>
#include <QUrl>
#include <QRandomGenerator>
#include <QtQuick/qquickwindow.h>
#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions>

// TODO: delete this
#define DEG_TO_RAD_RATIO M_PI / 180

class GameScreen : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GameScreen() : m_t(0), m_program(nullptr) { }
    ~GameScreen();

    void setT(qreal t) { m_t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setWindow(QQuickWindow *window) { m_window = window; }

    void moveCamera(qreal x, qreal y);
    void moveCamera(QPointF position);

public slots:
    void paint();
    void handleWindowResize();

private:
    QSize m_viewportSize;
    qreal m_t;
    QOpenGLShaderProgram *m_program;
    QQuickWindow *m_window;

    QPointF camera_position;
};

class Squircle : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)

public:
    Squircle();

    qreal t() const { return m_t; }
    void setT(qreal t);

signals:
    void tChanged();

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    qreal m_t;
    GameScreen *m_renderer;
};

#endif // GAMESCREEN_H
