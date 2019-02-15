#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QPointF>

class Entity : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 health READ health WRITE setHealth NOTIFY healthChanged)
    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(QPointF position READ position WRITE setPosition NOTIFY positionChanged)
public:
    explicit Entity(QObject *parent = nullptr);

    quint16 health() const
    {
        return m_health;
    }

    bool selected() const
    {
        return m_selected;
    }

    QPointF position() const
    {
        return m_position;
    }

    bool dead();

signals:
    void healthChanged(quint16 health);
    void selectedChanged(bool selected);
    void positionChanged(QPointF position);

public slots:
    void setHealth(quint16 health)
    {
        if (m_health == health)
            return;

        m_health = health;
        emit healthChanged(m_health);
    }

    void setSelected(bool selected)
    {
        if (m_selected == selected)
            return;

        m_selected = selected;
        emit selectedChanged(m_selected);
    }

    void setPosition(QPointF position)
    {
        if (m_position == position)
            return;

        m_position = position;
        emit positionChanged(m_position);
    }

private:
    quint16 m_health{};
    bool m_selected{};
    QPointF m_position;
    qreal vision_range{};
};

#endif // ENTITY_H
