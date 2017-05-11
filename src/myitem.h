#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsItem>
#include <QtGui>
#include <QLine>

class MyItem : public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MyItem();

    QRectF boundingRect() const;
    QPoint leftup;
    QPoint rightup;
    QPoint leftdown;
    QPoint rightdown;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:
    
public slots:
    
};

#endif // MYITEM_H
