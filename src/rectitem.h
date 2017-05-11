#ifndef RECTITEM_H
#define RECTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QtGui>

class rectItem : public QGraphicsPolygonItem
{
public:
    rectItem(QGraphicsItem *parent = 0);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

//自定义 Scene
class CustomScene : public QGraphicsScene
{
protected:
    //左键：添加item 右键：移除item
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};
#endif // RECTITEM_H
