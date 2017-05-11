#include "myitem.h"

MyItem::MyItem()
{

}

QRectF MyItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0 - penWidth/2.0, 0 - penWidth / 2,
                  20 + penWidth, 20 + penWidth);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen; //画笔
    pen.setColor(QColor(255, 0, 0));
    painter->setPen(pen);
    //painter->setBrush(Qt::red);
    //painter->drawRect(0, 0, 20, 20);
    QLine line1(leftup, rightup);
    QLine line2(rightup, rightdown);
    QLine line3(rightdown, leftdown);
    QLine line4(leftdown, leftup);
    painter->drawLine(line1);
    painter->drawLine(line2);
    painter->drawLine(line3);
    painter->drawLine(line4);
    //painter->drawPolygon();
}



