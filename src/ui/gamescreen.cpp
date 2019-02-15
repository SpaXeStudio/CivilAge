#include "gamescreen.h"

Squircle::Squircle()
    : m_t(0)
    , m_renderer(nullptr)
{
    connect(this, &QQuickItem::windowChanged, this, &Squircle::handleWindowChanged);
}

void Squircle::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}

void Squircle::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &Squircle::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &Squircle::cleanup, Qt::DirectConnection);
        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
        win->setClearBeforeRendering(false);
    }
}
void Squircle::cleanup()
{
    if (m_renderer) {
        delete m_renderer;
        m_renderer = nullptr;
    }
}

void Squircle::sync()
{
    if (!m_renderer) {
        m_renderer = new GameScreen();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &GameScreen::paint, Qt::DirectConnection);
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setT(m_t);
    m_renderer->setWindow(window());
}

void GameScreen::paint()
{   
    float points[4 * 2] = {
        0.5, 0.5,
        -0.5, -0.5,
        -0.5, 0.5,
        0.5, -0.5
    };

    if (!m_program) {
        initializeOpenGLFunctions();

        m_program = new QOpenGLShaderProgram();
        m_program->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/bg.vsh");
        m_program->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/bg.fsh");

        m_program->link();
        m_program->bindAttributeLocation("position", 0);
        m_program->bindAttributeLocation("t", 1);

    }
    m_program->bind();

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    m_program->setUniformValue(1, static_cast<float>(m_t));

    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

    glDrawArrays(GL_POINTS, 0, sizeof(points) / 2);

    m_program->release();

    // Not strictly needed for this example, but generally useful for when
    // mixing with raw OpenGL.
    m_window->resetOpenGLState();
}

void GameScreen::handleWindowResize()
{
    //outer_circle_radius = static_cast<float>(hypot(win->width() / 2, win->height() / 2));
}

GameScreen::~GameScreen()
{
    delete m_program;
}

void GameScreen::moveCamera(qreal x, qreal y)
{
    camera_position = QPointF(x, y);
}

void GameScreen::moveCamera(QPointF position)
{
    camera_position = position;
}
