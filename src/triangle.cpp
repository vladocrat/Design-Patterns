#include "triangle.h"

#include <QPainter>

struct Triangle::impl_t
{
    float x;
    float y;
};

Triangle::Triangle(QQuickPaintedItem* parent)
{
    qDebug() << Q_FUNC_INFO;
    createImpl();

    setAcceptedMouseButtons(Qt::AllButtons);
    setSize(QSize(100, 100));
}

Triangle::~Triangle()
{

}

void Triangle::setBoardX(float x)
{
    impl().x = x;
    setX(impl().x);
}

void Triangle::setBoardY(float y)
{
    impl().y = y;
    setY(impl().y);
}

void Triangle::paint(QPainter* painter)
{
    qDebug() << Q_FUNC_INFO;
    painter->setRenderHint(QPainter::Antialiasing);
    QPolygonF triangle;
    triangle << QPointF(width() /  2,  0) << QPointF(0, height()) << QPointF(width(), height());
    painter->drawPolygon(triangle);
}

void Triangle::mousePressEvent(QMouseEvent* event)
{
    qDebug() << Q_FUNC_INFO;
}

void Triangle::mouseMoveEvent(QMouseEvent* event)
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
