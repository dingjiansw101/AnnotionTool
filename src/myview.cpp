#include "myview.h"


MyView::MyView(QWidget *parent) :
    QGraphicsView(parent), scene(new CustomScene), image(new QImage), pos(0),
    lastpos(0), count(0)
{
}
//void MyView::wheelEvent(QWheelEvent*event)  //滚轮事件
//{
////   if(event->delta() > 0)  //如果鼠标滚轮远离使用者，则delta()返回正值
////       scale(0.5,0.5);  //视图缩放
////   else scale(2,2);
//}
void MyView::mousePressEvent(QMouseEvent*event)
{
    qDebug() << "view press";
    QGraphicsView::mousePressEvent(event);
    if(event->button() == Qt::LeftButton)
    {
        lastPoint = mapToScene(event->pos());
        qDebug() << lastPoint;

//        if (selectdItem = itemAt(event->pos()) ) {
//            qDebug() << "You clicked on item" << selectdItem << selectdItem->toolTip();

//            //selectdItem.pos();

//        } else {
//            qDebug() << "You didn't click on an item.";
//        }
        QPoint tmPoint = lastPoint.toPoint();
        point[count] = tmPoint;

        if (count == 2)
        {
            count = -1;
            CustomItem *myitem = new CustomItem();
            //rectItem *myitem = new rectItem();
            QVector<QPointF> points;
            points.push_back(point[0]);
            points.push_back(point[1]);
            myitem->leftup = point[0];
            myitem->rightup = point[1];
            QPoint tmp_p3;
            QPoint tmp_p4;
            if (point[1].x() != point[0].x())
            {
                double delt_x = point[1].x() - point[0].x();
                double delt_y = -point[1].y() - (-point[0].y());
                double kilo = delt_y/delt_x;
                double dr = (-kilo*point[2].x() + (-point[2].y()) + kilo*point[0].x() - (-point[0].y()));
                double d = dr/sqrt(kilo*kilo + 1);
                double theta = atan(kilo);
                //double theta = atan2(delt_y, delt_x);
                int tmp3_x = 0;
                int tmp3_y = d;
                int tmp4_x = 0;
                int tmp4_y = d;
                tmp_p3.setX(point[1].x() + cos(theta)*tmp3_x - sin(theta) * tmp3_y);
                tmp_p3.setY(-(-point[1].y() + sin(theta) * tmp3_x + cos(theta) * tmp3_y));
                //QPoint tmp_p3(point[1].x() + cos(theta)*tmp3_x - sin(theta) * tmp3_y,
                  //      -(-point[1].y() + sin(theta) * tmp3_x + cos(theta) * tmp3_y));
                tmp_p4.setX(point[0].x() + cos(theta)*tmp4_x - sin(theta) * tmp4_y);
                tmp_p4.setY(-(-point[0].y() + sin(theta) * tmp4_x + cos(theta) * tmp4_y));
                //QPoint tmp_p4(point[0].x() + cos(theta)*tmp4_x - sin(theta) * tmp4_y,
                  //      -(-point[0].y() + sin(theta) * tmp4_x + cos(theta) * tmp4_y));
            }
            else
            {
                tmp_p3.setX(point[2].x());
                tmp_p3.setY(point[1].y());
                tmp_p4.setX(point[2].x());
                tmp_p4.setY(point[0].y());
            }


            points.push_back(tmp_p3);
            points.push_back(tmp_p4);

            myitem->rightdown = tmp_p3;
            myitem->leftdown = tmp_p4;

            myitem->setPolygon(points);
            MyrecList.push_back(myitem);
            for (int i = 0; i < MyrecList.size(); i++)
            {
                qDebug() << "My rect i:" << i;
                scene->addItem(MyrecList[i]);
            }
            scene->addItem(myitem);
//            for (int i = 0; i < MyrecList.size(); i++)
//            {
////                CustomItem *item = new CustomItem();
////                QString tmplabel = ui->label->text();
////                std::string label = tmplabel.toStdString();
////                out << label << std::endl;

//                //out << item->polygon();
//                int x1 = MyrecList[i]->leftup.x();
//                int y1 = MyrecList[i]->leftup.y();
//                int x2 = MyrecList[i]->rightup.x();
//                int y2 = MyrecList[i]->rightup.y();
//                int x3 = MyrecList[i]->rightdown.x();
//                int y3 = MyrecList[i]->rightdown.y();
//                int x4 = MyrecList[i]->leftdown.x();
//                int y4 = MyrecList[i]->leftdown.y();
////                qDebug() << "pointer for view" << this;
////                qDebug() << "recList in view";
////                qDebug() << x1 << " " << y1;
////                qDebug() << x2 << " " << y2;
////                qDebug() << x3 << " " << y3;
////                qDebug() << x4 << " " << y4;

//            }

            //setScene(scene);
            //setAlignment(Qt::AlignLeft | Qt::AlignTop);
            //drawItems();
            //update();
            //show();
            //viewport()->repaint();
        }
        count++;

    }
    else if (event->button() == Qt::RightButton)
    {
        qDebug() << "view right button";
        //count = 0;
//        if (selectdItem)
//        {
//            scene->removeItem(selectdItem);
//            for (int i = 0; i < MyrecList.size(); i++)
//            {
//                qDebug() << "compare i:" << i;
//                if (selectdItem == MyrecList[i])
//                {
//                    qDebug() << "delete i:" << i ;
//                    delete selectdItem;
//                    MyrecList.erase(MyrecList.begin() + i);
//                }
//            }
//        }
//        QGraphicsItem *itemToRemove = NULL;
//        foreach (QGraphicsItem *item, items(scene->event->scenePos())) {
//            if (item->type() == QGraphicsItem::UserType+1) {
//                itemToRemove = item;
//                break;
//            }
//        }
//        // 从 Scene 上移除 item
//        if (itemToRemove != NULL)
//            scene->removeItem(itemToRemove);
    }
}

void MyView::mouseReleaseEvent(QMouseEvent *event)
{
        if (event->button() == Qt::LeftButton)
        {
            endPoint = mapToScene(event->pos());
            qDebug() << "in mouseRelease" ;
            QString fileName = fielLists[pos];
            if(fileName != "")
            {
                if(image->load(fileName))
                {
                    int x,y,w,h;
                    x = lastPoint.x();
                    y = lastPoint.y();
                    w = endPoint.x() - x;
                    h = endPoint.y() - y;
                    if (w + h > 3)
                    {
                        QGraphicsRectItem *item = new QGraphicsRectItem(x, y, w, h);//矩形项
                        QPen pen; //画笔
                        pen.setColor(QColor(255, 0, 0));
                        item->setPen(pen);
                        rectList.push_back(item);
                        count = 0;
                    }


                    //item->setGraphicsEffect();
                    for (int i = 0; i < rectList.size(); i++)
                    {
                        qDebug() << "i:" << i;
                        scene->addItem(rectList[i]);
                    }
                    setScene(scene);
                    setAlignment(Qt::AlignLeft | Qt::AlignTop);
                    //ui->graphicsView->resize(image->width() + 10, image->height() + 10);
                    //show();
                    //viewport()->repaint();
                    QString text = QString::number(pos, 10);
                }
            }
        }
}

MyView::~MyView()
{
    delete scene;
    delete image;
    //delete effect;
    for (int i = 0; i < rectList.size(); i++)
    {
        delete rectList[i];
    }
    rectList.clear();
    for (int i = 0; i < MyrecList.size(); i++)
    {
        delete MyrecList[i];
    }
}
