#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <QtGui>
#include "mainwindow.h"
#include "myview.h"
#include "customitem.h"

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = 0);
    ~MyView();
    QStringList fielLists;
    //QStringList txtLists;
    QImage *image;
    int pos;
    int lastpos;
    QGraphicsItem *selectdItem;
    //rectItem selectdItem;
    //QGraphicsScene *scene;
    class CustomScene *scene;
    class MainWindow *father;
    QPointF lastPoint;
    QPointF endPoint;
    std::vector<QGraphicsRectItem*> rectList;
    std::vector<class CustomItem*> MyrecList;
    QPoint point[4];
    int count;
protected:
   //void wheelEvent(QWheelEvent *event);
   void mousePressEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);
private:
   QPixmap pix;
signals:
    
public slots:
    
};

#endif // MYVIEW_H
