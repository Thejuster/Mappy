#include "tileset.h"
#include "qmessagebox.h"
#include "qstring.h"

Tileset::Tileset(QWidget *parent) :
    QLabel(parent)
{
}


void Tileset::paintEvent(QPaintEvent *)
{
     QPainter p(this);

     if(Tilesets.isNull())
     {

     }else
     {
         p.drawPixmap(0,0,Tilesets.width(),Tilesets.height(),Tilesets);
     }

     DrawGrid(&p);
     DrawCursor(&p);

     QPen old = p.pen();



     if(DrawSelection)
     {
         p.drawRect(SelectionStart.x(),SelectionStart.y(),SelectionEnd.x() - SelectionStart.x(),SelectionEnd.y() - SelectionStart.y());
     }
     update();


}


void Tileset::mouseMoveEvent(QMouseEvent *ev)
{
    if(StartCrop)
    {
        SelectionEnd = QPoint( ev->x() / 32 * 32 + 32,ev->y() / 32 * 32 + 32)  ;
    }

   msx = ev->x();
   msy = ev->y();
}


void Tileset::mousePressEvent(QMouseEvent *ev)
{


    StartCrop=true;

    SelectionStart = QPoint(ev->x() / 32 * 32,ev->y() / 32 * 32);



}


void Tileset::mouseReleaseEvent(QMouseEvent *ev)
{


    StartCrop = false;

    SelectionEnd = QPoint(ev->x() / 32 * 32,ev->y() / 32 * 32);


     CropArea = QRect(SelectionStart.x(),SelectionStart.y(),SelectionEnd.x(),SelectionEnd.y());

     DrawSelection=true;
}


void Tileset::DrawGrid(QPainter *p)
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


void Tileset::LoadTileset(QString filename)
{
    Tilesets.load(filename);

    this->setMinimumHeight(Tilesets.height());
    this->setMinimumWidth(Tilesets.width());
    this->setMaximumWidth(Tilesets.width());
    this->setMaximumHeight(Tilesets.height());
}


void Tileset::DrawCursor(QPainter *p)
{
    p->drawRect(msx / bw * bw,msy/bh*bh,bw,bh);

}





QDataStream& operator <<(QDataStream &s,QString& tt)
{
    s << tt;
    return s;
}


QDataStream& operator >>(QDataStream &in, QString& tt)
{
    in >> tt;
    return in;
}
