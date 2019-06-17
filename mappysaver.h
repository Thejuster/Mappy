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
        int x,y,w,h,Tx,Ty,Tw,Th;
        QRect rect;
    };


    QList<Tile> Tiles;

    QObject t;

    Tile tile;



};



QDataStream& operator << (QDataStream& s, const MappySaver::Tile& tile);
QDataStream& operator >> (QDataStream& s, MappySaver::Tile& tile);
bool operator == (const MappySaver::Tile &tile, const MappySaver::Tile& match);


#endif // MAPPYSAVER_H
