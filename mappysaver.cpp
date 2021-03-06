#include "mappysaver.h"
#include "qfile.h"
#include "QtCore"
#include "qdatastream.h"


MappySaver::MappySaver()
{


}


//Deprecato
void MappySaver::SaveMap(QString filename)
{

    QFile f(filename);

     if(!f.open(QIODevice::WriteOnly))
     {

     }else
     {
         QDataStream out(&f);
         out.setVersion(QDataStream::Qt_4_8);
         out << this->Tiles;
     }


}


QDataStream &operator<<(QDataStream &s, const MappySaver::Tile& tile)
{
    s << tile.h << tile.ID << tile.rect << tile.w << tile.x << tile.y << tile.Tx << tile.Ty;
    return s;
}


QDataStream &operator>>(QDataStream &s, MappySaver::Tile& tile)
{
  s >> tile.h >> tile.ID >> tile.rect >> tile.w >> tile.x >> tile.y << tile.Tx << tile.Ty;
  return s;
}


bool operator == (const MappySaver::Tile &tile, const MappySaver::Tile &match)
{

    return (tile.ID == match.ID) && (tile.h == match.h) && (tile.rect == match.rect) && (tile.w == match.w) &&
            (tile.x == match.x) && (tile.y == match.y) && (tile.Tx == match.Tx) && (tile.Ty == match.Ty);
}


