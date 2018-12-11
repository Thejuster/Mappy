#ifndef MAPEDITOR_H
#define MAPEDITOR_H



#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QList>
#include <QRect>

#include "tileset.h"

class mapeditor : public QLabel
{
    Q_OBJECT

public:
    int blw = 32,blh = 32;
    int bw = 32, bh = 32;
    int msX = 0,msY = 0;
    explicit mapeditor(QWidget *parent = 0);

    void DrawGrid(QPainter *p);
    void DrawCursor(QPainter *p);

    QPixmap map;
    Tileset *tileset;
    
    bool mdown = false;

    //structure
    struct Tile
    {
    public:
        int ID;
        int x,y,w,h;
        QRect rect;
    };


    QList<Tile> Tiles;


protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

signals:
    
public slots:
    
};

#endif // MAPEDITOR_H
