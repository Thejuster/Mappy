#include "mapeditor.h"
#include "qpen.h"
#include "QDebug"
#include "qmessagebox.h"

/* (C) Copyright Making Italia - By Thejuster
 * for pierotofy.it Community
 **/

mapeditor::mapeditor(QWidget *parent) :
    QLabel(parent)
{

}


void mapeditor::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    for(int i = 0; i < Tiles.count(); i++)
    {
        p.drawPixmap(Tiles[i].x,Tiles[i].y,tileset->Tilesets,Tiles[i].rect.x(),Tiles[i].rect.y(),Tiles[i].rect.width()- Tiles[i].rect.x() + 32,Tiles[i].rect.height() - Tiles[i].rect.y() + 32);
    }


    DrawGrid(&p);
    DrawCursor(&p);


    this->update();

}


void mapeditor::mouseMoveEvent(QMouseEvent *ev)
{
    msX = ev->x();
    msY = ev->y();

    if(mdown)
    {
        Tile t;

        bool find = false;

        t.ID = Tiles.count();
        t.x = ev->x() / bw * bw;
        t.y = ev->y() / bh * bh;
        t.rect = tileset->CropArea;


        for(int i = 0; i < Tiles.count(); i ++)
        {
            if(Tiles[i].x == t.x && Tiles[i].y == t.y)
                find=true;
        }

        if(!find)
        Tiles.append(t);
    }
}


//Create a dynamic grid
void mapeditor::DrawGrid(QPainter *p)
{
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidthF(1.5f);
    QVector<qreal> dash;
    dash << 1.0 << 5.0;
    pen.setDashPattern(dash);

    QPen old = p->pen();
    p->setPen(pen);

    for(int i = 0; i < this->width(); i+=32)
    {
        p->drawLine(i,0,i,this->height());
    }

    for(int i = 0; i < this->height(); i+=32)
    {
        p->drawLine(0,i,this->width(),i);
    }

    p->setPen(old);
}



void mapeditor::DrawCursor(QPainter *p)
{
    if(!eventMode)
    {
     p->drawRect(QRect(msX / bw * bw,msY / bh * bh,bw,bh));
     p->setOpacity(.5f);
     p->drawPixmap(QPoint(msX / bw * bw,msY / bh * bh),tileset->Tilesets,QRect(tileset->SelectionStart.x(),tileset->SelectionStart.y(),tileset->SelectionEnd.x() - tileset->SelectionStart.x() + 32 ,tileset->SelectionEnd.y() - tileset->SelectionStart.y() + 32));

    }else
    {
        QPen old = p->pen();

        QPen pn;
        pn.setColor(Qt::red);
        pn.setWidthF(2.0f);
        p->setPen(pn);

        p->drawRect(QRect(msX / bw * bw,msY / bh * bh,bw,bh));

        p->fillRect(QRect((msX / bw * bw) + 5,(msY / bh * bh)+5,bw-10,bh-10),Qt::darkGray);

        p->setPen(old);
    }

}


void mapeditor::mousePressEvent(QMouseEvent *ev)
{
    //mdown = true;

    if(ev->button() == Qt::RightButton)
    {
        for(int i = 0; i < Tiles.count(); i++)
        {
            if(Tiles[i].x == msX && Tiles[i].y == msY)
            {
                Tiles.removeAt(i);

            }
        }
    }else
    {
        mdown = true;
    }


}

void mapeditor::mouseReleaseEvent(QMouseEvent *ev)
{
       mdown = false;

        Tile t;

        bool find = false;

        t.ID = Tiles.count();
        t.x = ev->x() / bw * bw;
        t.y = ev->y() / bh * bh;
        t.rect = tileset->CropArea;
        t.Tx = tileset->Tx;
        t.Ty = tileset->Ty;


        int tfind;

        for(int i = 0; i < Tiles.count(); i ++)
        {
            if(Tiles[i].x == t.x && Tiles[i].y == t.y)
            {
                find=true;
                tfind = i;
            }
        }



       // if(!find)
        Tiles.append(t);


}
