#include "rectitem.h"

rectItem::rectItem(QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
{
    // 画笔 - 边框色
    QPen p = pen();
    p.setWidth(2);
    p.setColor(QColor(0, 160, 230));

    setPen(p);
    // 可选择、可移动
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

//QRectF rectItem::boundingRect() const
//{
//    qreal penWidth = 1;
//    return QRectF(0 - penWidth/2.0, 0 - penWidth / 2,
//                  20 + penWidth, 20 + penWidth);
//}

void rectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
       qDebug() << "Custom item left clicked.";
       QGraphicsItem::mousePressEvent(event);
       event->accept();
    } else if (event->button() == Qt::RightButton) {
        qDebug() << "Custom item right clicked.";
        event->ignore();
    }
}
// 自定义 Scene
void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Custom scene clicked.";
    QGraphicsScene::mousePressEvent(event);
    qDebug() << "Custom scene 2";
    if (!event->isAccepted()) {
        if (event->button() == Qt::LeftButton) {
            // 在 Scene 上添加一个自定义 item
              qDebug() << "int scene leftButton";
        } else if (event->button() == Qt::RightButton) {
            // 检测光标下是否有 item
            QGraphicsItem *itemToRemove = NULL;
            foreach (QGraphicsItem *item, items(event->scenePos())) {
                if (item->type() == QGraphicsItem::UserType+1) {
                    itemToRemove = item;
                    break;
                }
            }
            // 从 Scene 上移除 item
            if (itemToRemove != NULL)
                removeItem(itemToRemove);
        }
    }
}
