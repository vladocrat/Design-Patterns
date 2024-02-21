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

    setAcceptedMouseButtons(Qt::AllButtons);
    setSize(QSize(100, 100));
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
}

void Rectangle::mouseMoveEvent(QMouseEvent* event)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << impl().x << " " << impl().y;
    qDebug() << event->x() << " " << event->y();

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
