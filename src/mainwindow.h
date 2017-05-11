#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QtGui>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "customitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    void save_truth();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void loadground_truth(const QString &fileName);

private:
    class Ui::MainWindow *ui;
private slots:
    void on_slotOpenImage_triggered();//读取文件夹下所有文件信号槽
    void on_slotNextImage_triggered();//显示下一个image信号槽
    void on_slotPreImage_triggered();//显示上一个image信号槽
    void on_slotSaveImage_triggered();//保存ground_truth
};

#endif // MAINWINDOW_H
