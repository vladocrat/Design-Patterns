#include "circle.h"

#include <QPainter>

struct Circle::impl_t
{
    float x;
    float y;
};

Circle::Circle(QQuickPaintedItem* parent)
{
    qDebug() << Q_FUNC_INFO;
    createImpl();

    m_type = FigureType::Value::Circle;

    setAcceptedMouseButtons(Qt::AllButtons);
    setSize(QSize(100, 100));
}

Circle::~Circle()
{

}

void Circle::setBoardX(float x)
{
    impl().x = x;
    setX(impl().x);
}

void Circle::setBoardY(float y)
{
    impl().y = y;
    setY(impl().y);
}

void Circle::paint(QPainter* painter)
{
    qDebug() << Q_FUNC_INFO;
    painter->setRenderHint(QPainter::Antialiasing);
    QRectF rect(0, 0, 100, 100);
    painter->drawEllipse(rect);
}

void Circle::mousePressEvent(QMouseEvent* event)
{
    qDebug() << Q_FUNC_INFO;

    if (event->button() == Qt::MouseButton::RightButton)
    {
        emit openMenu(this);
        return;
    }
}

void Circle::mouseMoveEvent(QMouseEvent* event)
{
    auto diffY = event->y() - height() / 2;
    auto diffX = event->x() - width() / 2;

    auto resX = x() + diffX;
    auto resY = y() + diffY;

    if (resX < 0)
    {
        setBoardX(0);
    }
    else
    {
        setBoardX(resX);
    }

    if (resY < 0)
    {
        setBoardY(0);
    }
    else
    {
        setBoardY(resY);
    }
}

void Circle::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << Q_FUNC_INFO;

    if (event->button() == Qt::MouseButton::RightButton)
    {
        return;
    }

    emit moved(this);
}
