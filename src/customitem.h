#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QtGui>
#include <myview.h>

class CustomItem : public QGraphicsPolygonItem
{
public:
    explicit CustomItem(QGraphicsItem *parent = 0);
    QPointF leftup;
    QPointF rightup;
    QPointF leftdown;
    QPointF rightdown;
protected:
    //Shift+左键：进行选择 Alt:准备缩放
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
   // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:
    QPointF m_centerPointF;
    bool m_bResizing;
};

//自定义 Scene
class CustomScene : public QGraphicsScene
{
public:
    class MyView *father;
protected:
    //左键：添加item 右键：移除item,并将scene的count置为0
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // CUSTOMITEM_H
