#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QHBoxLayout"
#include "QList"
#include "newmap.h"
#include "QMessageBox"
#include "qfiledialog.h"
#include "mappysaver.h"
#include "qstring.h"
#include "qdebug.h"
#include "about.h"
#include "jexport.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QHBoxLayout *l = new QHBoxLayout();
    l->addWidget(ui->tileset);
    ui->scrollArea->widget()->setLayout(l);

    l = new QHBoxLayout();
    l->addWidget(ui->maps);
    ui->scrollArea_2->widget()->setLayout(l);

    //Setting Size
    ui->tileset->setMaximumHeight(0);
    ui->tileset->setMinimumHeight(0);
    ui->tileset->setMaximumWidth(0);
    ui->tileset->setMinimumWidth(0);
    ui->maps->setMaximumHeight(0);
    ui->maps->setMinimumHeight(0);
    ui->maps->setMaximumWidth(0);
    ui->maps->setMinimumWidth(0);

    //Default Setting
    ui->tileset->setMinimumWidth(0);
    ui->tileset->setMinimumHeight(0);
    QList<int> sizes;
    sizes << 200 << 500;
    ui->splitter->setSizes(sizes);





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_Map_triggered()
{
    NewMap *map = new NewMap();
    int result = map->exec();

    if(result == QDialog::Accepted)
    {
        ui->maps->blw = map->blw;
        ui->maps->blh = map->blh;

        //Apply new size
        ui->maps->setMinimumWidth(map->blw * 32);
        ui->maps->setMinimumHeight(map->blh * 32);
        ui->maps->setMaximumWidth(map->blw * 32);
        ui->maps->setMaximumHeight(map->blh * 32);

        //Creating map
        ui->maps->map = QPixmap(map->blw *32,map->blh *32);
        ui->maps->tileset = this->ui->tileset;
        ui->maps->Tiles.clear();


        EnableTool();
    }
}


void MainWindow::on_actionLoad_Tileset_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                        tr("Apri il file Tileset"),"",
                                                        tr("File PNG ( *.png )"));

        if(filename.isEmpty())
        {
            return;
        }else
        {
            ui->tileset->LoadTileset(filename);
            ui->tileset->Tilename = filename;

        }
}


void MainWindow::on_actionSave_Map_triggered()
{

    QString filename = QFileDialog::getSaveFileName(this,
                                                tr("Seleziona il file da salvare"),"",
                                            tr("File Mappa ( *.mp2d )"));

    MappySaver::Tile t;
    MappySaver m;
    Tileset tset;


    for(int i = 0; i < ui->maps->Tiles.count(); i++)
    {
        t.ID = ui->maps->Tiles[i].ID;
        t.h = ui->maps->Tiles[i].h;
        t.rect = ui->maps->Tiles[i].rect;
        t.w = ui->maps->Tiles[i].w;
        t.x = ui->maps->Tiles[i].x;
        t.y = ui->maps->Tiles[i].y;
        m.Tiles.append(t);
    }



    qDebug() << m.Tiles.count();


    for(int i = 0; i <m.Tiles.count(); i++)
    {
        MappySaver::Tile t = static_cast<MappySaver::Tile>(m.Tiles[i]);

        int duplicates = 0;
        for(int j = 0; j < m.Tiles.count(); j++)
        {
           if(m.Tiles[i] == m.Tiles[j])
           {
               duplicates++;
            qDebug() << "duplicato";
           }else
           {

           }

        }

        if(duplicates > 1)
            m.Tiles.removeAt(i);
    }


        QFile f(filename);

         if(!f.open(QIODevice::WriteOnly))
         {

         }else
         {
             QDataStream out(&f);
             out.setVersion(QDataStream::Qt_4_8);

             //Write all Tiles
             out << m.Tiles;
             f.flush();

             //Write Tileset filename information
             QString tilename = ui->tileset->Tilename;
             out << tilename.toLocal8Bit();
             f.flush();

             //Write MapSize
             out <<  ui->maps->blw;
             f.flush();
             out << ui->maps->blh;
             f.flush();


         }

        f.flush();
        f.close();


        this->currentfile = filename;
}


void MainWindow::on_actionLoad_Map_triggered()
{

       //Flush Data
       this->ui->maps->Tiles.clear();
       this->ui->maps->update();


       QString filename = QFileDialog::getOpenFileName(this,tr("Apri una mappa"),tr(""),tr("File Mappa (*.mp2d)"));

       QFile f(filename);

       MappySaver m;
       Tileset tset;


     if(!f.open(QIODevice::ReadOnly))
     {

     }else
     {

         QDataStream in(&f);
         in.setVersion(QDataStream::Qt_4_8);

         //Load all pice of tiles
         in >> m.Tiles;
         f.flush();

         qDebug() << m.Tiles.count();

         //Load Tileset file name
         QByteArray array;
         in >> array;

         QString tilename = QString::fromLocal8Bit(array);
         ui->tileset->Tilename = tilename;
         ui->tileset->LoadTileset(tilename); //Apply
         f.flush();

         //Reading Map Size
        int blw,blh;

        in >> blw;
        f.flush();
        in >> blh;

        ui->maps->blw = blw;
        ui->maps->blh = blh;

        //Apply new size
        ui->maps->setMinimumWidth(blw * 32);
        ui->maps->setMinimumHeight(blh * 32);
        ui->maps->setMaximumWidth(blw * 32);
        ui->maps->setMaximumHeight(blh * 32);

        //Creating map
        ui->maps->map = QPixmap(blw *32,blh *32);
        ui->maps->tileset = this->ui->tileset;






     }

    f.flush();
    f.close();


    mapeditor::Tile t;
    for(int i = 0; i < m.Tiles.count(); i++)
    {
        t.h = m.Tiles[i].h;
        t.ID = m.Tiles[i].ID;
        t.rect = m.Tiles[i].rect;
        t.w = m.Tiles[i].w;
        t.x = m.Tiles[i].x;
        t.y = m.Tiles[i].y;
        ui->maps->Tiles.append(t);
    }

    this->currentfile = filename;
    ui->actionSave->setEnabled(true);

    EnableTool();

}


void MainWindow::on_actionAbout_triggered()
{
    About *ab = new About();
    ab->exec();
}

void MainWindow::on_actionSave_triggered()
{
   //ToDO
   //Adding secondary save method
    SaveMap(this->currentfile);


}


//Void called whit ToolBar
void MainWindow::SaveMap(QString filename)
{

    MappySaver::Tile t;
    MappySaver m;
    Tileset tset;


    for(int i = 0; i < ui->maps->Tiles.count(); i++)
    {
        t.ID = ui->maps->Tiles[i].ID;
        t.h = ui->maps->Tiles[i].h;
        t.rect = ui->maps->Tiles[i].rect;
        t.w = ui->maps->Tiles[i].w;
        t.x = ui->maps->Tiles[i].x;
        t.y = ui->maps->Tiles[i].y;
        m.Tiles.append(t);
    }



    qDebug() << m.Tiles.count();


    for(int i = 0; i <m.Tiles.count(); i++)
    {
        MappySaver::Tile t = static_cast<MappySaver::Tile>(m.Tiles[i]);

        int duplicates = 0;
        for(int j = 0; j < m.Tiles.count(); j++)
        {
           if(m.Tiles[i] == m.Tiles[j])
           {
               duplicates++;
            qDebug() << "duplicato";
           }else
           {

           }

        }

        if(duplicates > 1)
            m.Tiles.removeAt(i);
    }


        QFile f(filename);

         if(!f.open(QIODevice::WriteOnly))
         {

         }else
         {
             QDataStream out(&f);
             out.setVersion(QDataStream::Qt_4_8);

             //Write all Tiles
             out << m.Tiles;
             f.flush();

             //Write Tileset filename information
             QString tilename = ui->tileset->Tilename;
             out << tilename.toLocal8Bit();
             f.flush();

             //Write MapSize
             out <<  ui->maps->blw;
             f.flush();
             out << ui->maps->blh;
             f.flush();


         }

        f.flush();
        f.close();


        this->currentfile = filename;
}


//Enable Toolbar Instruments
void MainWindow::EnableTool()
{
    ui->actionPencil->setEnabled(true);
    ui->actionEraser->setEnabled(true);

}


//Disable Toolbar Instruments
void MainWindow::DisableTool()
{
    ui->actionEraser->setEnabled(false);
    ui->actionPencil->setEnabled(false);
}


void MainWindow::on_actionEraser_triggered()
{
    ui->actionEraser->setChecked(true);

    JObject<int,QString> obj;
    obj.Set(0,"Filename");

}
