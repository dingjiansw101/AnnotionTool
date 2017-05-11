#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "customitem.h"
#include <cmath>
// 自定义 Item
CustomItem::CustomItem(QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
{
    // 画笔 - 边框色
    QPen p = pen();
    p.setWidth(2);
    p.setColor(QColor(0, 160, 230));

    setPen(p);
    // 可选择、可移动
    //setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    //可选择
    setFlags(QGraphicsItem::ItemIsSelectable);
}

void CustomItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

int CustomItem::type() const
{
    return UserType + 1;
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
            father->count = 0;
            // 检测光标下是否有 item
            QGraphicsItem *itemToRemove = NULL;
            foreach (QGraphicsItem *item, items(event->scenePos())) {
                qDebug() << "item type" << item->type() << "userType+1" << QGraphicsItem::UserType + 1;
                if (item->type() == QGraphicsItem::UserType+1) {
                    itemToRemove = item;
                    break;
                }
            }
            // 从 Scene 上移除 item
            if (itemToRemove != NULL)
            {
                removeItem(itemToRemove);
                //std::vector<CustomItem*> tmList;
                int posflag = 0;
                for (int i = 0; i < father->MyrecList.size(); i++)
                {
                    qDebug() << "compare i:" << i;
                    if (itemToRemove == father->MyrecList[i])
                    {
                         qDebug() << "delete i:" << i ;
                         //delete itemToRemove;
                         //father->MyrecList.erase(father->MyrecList.begin() + i);
                         posflag = i;

                         break;
                    }
                }
                father->MyrecList.erase(father->MyrecList.begin() + posflag);
                father->father->save_truth();
            }
        }
    }
}
