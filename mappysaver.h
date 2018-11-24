#include <QRect>
#include <QList>
#include <QDataStream>
#include <QString>
#include <QDataStream>>


#ifndef MAPPYSAVER_H
#define MAPPYSAVER_H


class MappySaver
{

public:


    MappySaver();
    void SaveMap(QString filename);

    //structure
    struct Tile
    {
    public:
        int ID;
        int x,y,w,h;
        QRect rect;
    };


    QList<Tile> Tiles;

    QObject t;

    Tile tile;



};



QDataStream& operator << (QDataStream& s, const MappySaver::Tile& tile);
QDataStream& operator >> (QDataStream& s, MappySaver::Tile& tile);


#endif // MAPPYSAVER_H