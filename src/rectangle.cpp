#include "rectangle.h"

#include <QPainter>

struct Rectangle::impl_t
{
    float x;
    float y;
};

Rectangle::Rectangle(QQuickPaintedItem* parent)
{
    createImpl();

    m_type = FigureType::Value::Rectangle;

    setAcceptedMouseButtons(Qt::AllButtons);
    setSize(QSize(100, 100));
}

Rectangle::Rectangle(const Rectangle& other)
{
    createImpl();

    m_type = FigureType::Value::Rectangle;

    impl().x = other.impl().x;
    impl().y = other.impl().y;
}

Rectangle::~Rectangle()
{

}

void Rectangle::paint(QPainter* painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QRectF rect(0, 0, 100, 100);
    painter->drawRect(rect);
}

void Rectangle::setBoardX(float x)
{
    impl().x = x;
    setX(impl().x);
}

void Rectangle::setBoardY(float y)
{
    impl().y = y;
    setY(impl().y);
}

void Rectangle::mousePressEvent(QMouseEvent* event)
{
    qDebug() << Q_FUNC_INFO;

    if (event->button() == Qt::MouseButton::RightButton)
    {
        emit openMenu(this);
        return;
    }
}

void Rectangle::mouseMoveEvent(QMouseEvent* event)
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

void Rectangle::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << Q_FUNC_INFO;

    if (event->button() == Qt::MouseButton::RightButton)
    {
        return;
    }

    emit moved(this);
}
