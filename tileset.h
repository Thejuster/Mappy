#ifndef TILESET_H
#define TILESET_H

#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QList>

class Tileset : public QLabel
{
    Q_OBJECT

public:
    explicit Tileset(QWidget *parent = 0);
    void DrawGrid(QPainter *p);
    void LoadTileset(QString filename);
    void DrawCursor(QPainter *p);
    int msx=0,msy=0;
    int bw = 32,bh=32;
    QPixmap Tilesets;
    QString Tilename;

    //Crop Var
    int cropX,cropY;
    int RelX,RelY;
    QRect CropArea;
    QPoint SelectionStart;
    QPoint SelectionEnd;
    bool DrawSelection=false;

private:
    bool StartCrop = false;

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);

    
signals:
    
public slots:
    
};

/*
QDataStream& operator <<(QDataStream &s, QString& tt);
QDataStream& operator >>(QDataStream &in, QString& tt);
*/

#endif // TILESET_H



