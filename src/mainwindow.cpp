#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <io.h>


void GetAllFiles( std::string path, std::vector<std::string>& files)

{



    long hFile = 0;

    //文件信息

    struct _finddata_t fileinfo;

    std::string p;

    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1)

    {

        do

        {

            if((fileinfo.attrib & _A_SUBDIR))

            {

                if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0)

                {

                    files.push_back(p.assign(path).append("\\").append(fileinfo.name) );

                    GetAllFiles( p.assign(path).append("\\").append(fileinfo.name), files );

                }

            }

            else

            {

                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );

            }



        }while(_findnext(hFile, &fileinfo) == 0);



        _findclose(hFile);

    }



}
void GetAllFormatFiles( std::string path, std::vector<std::string>& files,std::string format)

{

    //文件句柄

    long hFile = 0;

    //文件信息

    struct _finddata_t fileinfo;

    std::string p;

    if((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(),&fileinfo)) != -1)

    {

        do

        {

            if((fileinfo.attrib & _A_SUBDIR))

            {

                if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0)

                {

                    //files.push_back(p.assign(path).append("\\").append(fileinfo.name) );

                    GetAllFormatFiles( p.assign(path).append("\\").append(fileinfo.name), files,format);

                }

            }

            else

            {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
            }
        }while(_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);

    }
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //resize(800, 600);
    //将graphicsView的一个成员scene中添加一个MyView指针成员，指向graphicsView自己
    ui->graphicsView->scene->father = ui->graphicsView;
    //
    ui->graphicsView->father = this;
    //image = new QImage();

    //connect the button listener event
    connect(ui->load,SIGNAL(clicked()), this, SLOT(on_slotOpenImage_triggered()));
    connect(ui->next,SIGNAL(clicked()), this, SLOT(on_slotNextImage_triggered()));
    connect(ui->pre,SIGNAL(clicked()), this, SLOT(on_slotPreImage_triggered()));
    connect(ui->save, SIGNAL(clicked()), this, SLOT(on_slotSaveImage_triggered()));
    //connect(ui->jump,SIGNAL(), this, SLOT(on_slotJumpImage_triggered()));
}

//void MainWindow::save_truth()
//{
//    int position = ui->graphicsView->pos;
//    QString tmp = ui->graphicsView->fielLists[position] + ".txt";
//    std::string stdtmp = tmp.toStdString();
//    const char* filename = stdtmp.c_str();
//    std::ofstream out(filename);
//    //ui->graphicsView->selectdItem->setToolTip(ui->label->text());
//    for (int i = 0; i < ui->graphicsView->MyrecList.size(); i++)
//    {
//        CustomItem *item = new CustomItem();
//        QString tmplabel = ui->label->text();
//        std::string label = tmplabel.toStdString();
//        out << label << std::endl;

//        //out << item->polygon();
//        int x1 = ui->graphicsView->MyrecList[i]->leftup.x();
//        int y1 = ui->graphicsView->MyrecList[i]->leftup.y();
//        int x2 = ui->graphicsView->MyrecList[i]->rightup.x();
//        int y2 = ui->graphicsView->MyrecList[i]->rightup.y();
//        int x3 = ui->graphicsView->MyrecList[i]->rightdown.x();
//        int y3 = ui->graphicsView->MyrecList[i]->rightdown.y();
//        int x4 = ui->graphicsView->MyrecList[i]->leftdown.x();
//        int y4 = ui->graphicsView->MyrecList[i]->leftdown.y();

//        out << x1 << " " << y1 << std::endl;
//        out << x2 << " " << y2 << std::endl;
//        out << x3 << " " << y3 << std::endl;
//        out << x4 << " " << y4 << std::endl;
//        out << std::endl;
//    }
//}

void MainWindow::save_truth()
{
    int position = ui->graphicsView->pos;
    QString tmp = ui->graphicsView->fielLists[position] + ".txt";
    std::string stdtmp = tmp.toStdString();
    const char* filename = stdtmp.c_str();
    std::ofstream out(filename);

    for (int i = 0; i < ui->graphicsView->MyrecList.size(); i++)
    {
        CustomItem *item = new CustomItem();
        QString tmplabel = ui->label->text();
        std::string label = tmplabel.toStdString();
        out << label << std::endl;

        //out << item->polygon();
        int x1 = ui->graphicsView->MyrecList[i]->leftup.x();
        int y1 = ui->graphicsView->MyrecList[i]->leftup.y();
        int x2 = ui->graphicsView->MyrecList[i]->rightup.x();
        int y2 = ui->graphicsView->MyrecList[i]->rightup.y();
        int x3 = ui->graphicsView->MyrecList[i]->rightdown.x();
        int y3 = ui->graphicsView->MyrecList[i]->rightdown.y();
        int x4 = ui->graphicsView->MyrecList[i]->leftdown.x();
        int y4 = ui->graphicsView->MyrecList[i]->leftdown.y();

        qDebug() << "pointer for ui->view" << ui->graphicsView;
        qDebug() << "recList in mainWindow";
        qDebug() << x1 << " " << y1;
        qDebug() << x2 << " " << y2;
        qDebug() << x3 << " " << y3;
        qDebug() << x4 << " " << y4;

        out << x1 << " " << y1 << std::endl;
        out << x2 << " " << y2 << std::endl;
        out << x3 << " " << y3 << std::endl;
        out << x4 << " " << y4 << std::endl;
        out << std::endl;
    }
}

void MainWindow::on_slotSaveImage_triggered()
{
      save_truth();
}

void MainWindow::loadground_truth(const QString &fileName)
{
    //QString fileName = ui->graphicsView->fielLists[0];
    std::string ground_truthfile = fileName.toStdString();
    ground_truthfile = ground_truthfile + ".txt";
    const char* truthName = ground_truthfile.c_str();
    std::ifstream in(truthName);
    int a, b;
    int t = 0;
    int label = -1;
    QPointF tmpoints[4];
    if (in)//判断文件是否存在
    {
        while(!in.eof())
        {

            if (t == 0)
            {
                in >> label;
            }
            else if (t == 5)
            {
                //rectItem *tmItem = new rectItem;

                CustomItem *tmItem = new CustomItem;
                QVector<QPointF> points;
                for(int i = 0; i < 4; i++)
                {
                    points.push_back(tmpoints[i]);
                }
                tmItem->setPolygon(points);
                //tmItem->setToolTip();
                tmItem->leftup = tmpoints[0];
                tmItem->rightup = tmpoints[1];
                tmItem->rightdown = tmpoints[2];
                tmItem->leftdown = tmpoints[3];
                ui->graphicsView->MyrecList.push_back(tmItem);
                t = -1;
            }
            else
            {
                in >> a >> b;
                std::cout << a << " " << b << std::endl;
                QPointF tpoint = QPointF(a, b);
                tmpoints[t - 1] = tpoint;
            }
            t++;
        }
    }
}

void MainWindow::on_slotOpenImage_triggered()
{
//   // QString fileName = QFileDialog::getOpenFileName(
//                this, "open image file",
//                ".",
//                "Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)");

    QString dir = QFileDialog::getExistingDirectory(this, "Open Directory", ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    qDebug() << dir;
    std::string str = dir.toStdString();
    QString qstr = QString::fromStdString(str);
    std::cout << str << std::endl;

    std::vector<std::string> files;

    ////获取该路径下的所有文件
    //getFiles(str, files );
    GetAllFormatFiles(str, files, "jpg");
    //GetAllFiles(str, files);
    for (int i = 0; i < files.size(); i++)
    {
        QString tmp = QString::fromStdString(files[i]);
        ui->graphicsView->fielLists.push_back(tmp);
        std::cout << files[i] << std::endl;
    }

    QString fileName = ui->graphicsView->fielLists[0];
    loadground_truth(fileName);

    if(fileName != "")
    {
        if(ui->graphicsView->image->load(fileName))
        {
            ui->graphicsView->scene->clear();
            ui->graphicsView->scene->addPixmap(QPixmap::fromImage(*ui->graphicsView->image));
            for (int i = 0; i < ui->graphicsView->MyrecList.size(); i++)
            {
                ui->graphicsView->scene->addItem(ui->graphicsView->MyrecList[i]);
                qDebug() << "myrect i:" << i ;
            }
            //ui->graphicsView->scene->items();
            //QList<QGraphicsItem*> ItemList = ui->graphicsView->scene->items();
            //ui->graphicsView->scene->removeItem(ItemList[3]);
            //qDebug() << "ItemList size:" << ItemList.size();
            ui->graphicsView->setScene(ui->graphicsView->scene);
            ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
            ui->graphicsView->show();

            QString text = QString::number(ui->graphicsView->pos, 10);
            ui->jump->setText(text);
            ui->jump->show();
        }
    }
}

void MainWindow::on_slotNextImage_triggered()
{
    //clear rect
    for (int i = 0; i < ui->graphicsView->rectList.size(); i++)
    {
        delete ui->graphicsView->rectList[i];
    }
    ui->graphicsView->rectList.clear();
    ui->graphicsView->MyrecList.clear();

    bool ok;
    ui->graphicsView->pos = ui->jump->text().toInt(&ok,10); //ok=rue
    ui->graphicsView->pos++;
    //check if out of border
    if (ui->graphicsView->pos > ui->graphicsView->fielLists.size() - 1)
        ui->graphicsView->pos = ui->graphicsView->fielLists.size() - 1;
    QString fileName = ui->graphicsView->fielLists[ui->graphicsView->pos];
    loadground_truth(fileName);

    if(fileName != "")
    {
        if(ui->graphicsView->image->load(fileName))
        {

            //QGraphicsScene *scene = new QGraphicsScene;
            ui->graphicsView->scene->clear();
            ui->graphicsView->scene->addPixmap(QPixmap::fromImage(*ui->graphicsView->image));
            for (int i = 0; i < ui->graphicsView->MyrecList.size(); i++)
            {
                ui->graphicsView->scene->addItem(ui->graphicsView->MyrecList[i]);
                qDebug() << "myrect i:" << i ;
            }


            ui->graphicsView->setScene(ui->graphicsView->scene);
            ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
            //ui->graphicsView->resize(image->width() + 10, image->height() + 10);
            ui->graphicsView->show();
            QString text = QString::number(ui->graphicsView->pos, 10);
            ui->jump->setText(text);
            ui->jump->show();
        }
    }
}
void MainWindow::on_slotPreImage_triggered()
{
    //clear rect
    for (int i = 0; i < ui->graphicsView->rectList.size(); i++)
    {
        delete ui->graphicsView->rectList[i];
    }
    ui->graphicsView->rectList.clear();
    ui->graphicsView->MyrecList.clear();

    bool ok;
    ui->graphicsView->pos = ui->jump->text().toInt(&ok,10); //ok=rue
    ui->graphicsView->pos--;
    if (ui->graphicsView->pos < 0)
        ui->graphicsView->pos = 0;
    QString fileName = ui->graphicsView->fielLists[ui->graphicsView->pos];
    loadground_truth(fileName);
    if(fileName != "")
    {
        if(ui->graphicsView->image->load(fileName))
        {

            //QGraphicsScene *scene = new QGraphicsScene;
            ui->graphicsView->scene->clear();//显示上一张图片时将当前scene清空
            ui->graphicsView->scene->addPixmap(QPixmap::fromImage(*ui->graphicsView->image));
            for (int i = 0; i < ui->graphicsView->MyrecList.size(); i++)
            {
                ui->graphicsView->scene->addItem(ui->graphicsView->MyrecList[i]);
                qDebug() << "myrect i:" << i ;
            }


            ui->graphicsView->setScene(ui->graphicsView->scene);
            ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
            //ui->graphicsView->resize(image->width() + 10, image->height() + 10);
            ui->graphicsView->show();
            QString text = QString::number(ui->graphicsView->pos, 10);
            ui->jump->setText(text);
            ui->jump->show();

        }
    }
}



MainWindow::~MainWindow()
{
    //delete image;
    delete ui;
    //delete myview;
}

//void MainWindow::mousePressEvent(QMouseEvent *event)
//{
//    //qDebug() << event->pos();
//    if(event->button() == Qt::LeftButton)
//    {
//        lastPoint = event->pos();
//        // Detect if the click is in the view.
//        QPoint remapped = ui->graphicsView->mapFromParent( event->pos() );
//        if ( ui->graphicsView->rect().contains( remapped ) )
//        {
//             QPointF mousePoint = ui->graphicsView->mapToScene( remapped );
//             qDebug() << mousePoint;
//        }
//        //QPointF mousePoint = ui->graphicsView->mapToScene(event->pos());
//        //qDebug() << mousePoint;

//    }
//}


//void MainWindow::paintEvent(QPaintEvent *)
//{
//    QPainter painter(this);
//    QPixmap pix;
//    pix.load("F:\\documentation\\Data\\chips\\chip1.jpg");
//    painter.drawPixmap(0, 0, 129, 66, pix);
//}
