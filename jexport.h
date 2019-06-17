#ifndef JEXPORT_H
#define JEXPORT_H

#include "qlist.h"
#include "qstring.h"
#include "qdebug.h"
#include "qstringlist.h"

///@brief Version of JSON Validating
#define VERSION = RFC4627


class JObject
{
private:
    QString str_item;
    QString key_item;

public:
    void Value(QString Key, QString Value)
    {
        key_item = Key;
        str_item = Value;
    }

    QString GetKey()
    {
        return key_item;
    }

    QString GetValue()
    {
        return str_item;
    }

};


class JTile
{
private:
    int id;
    int x;
    int y;
public:
    QStringList b;
    struct tile
    {
    public:
        int ID;
        int X;
        int Y;
    };

    QList<tile> pice;

    void Add(int ID,int X,int Y)
    {
        id = ID;
        x = X;
        y = Y;

        b.append(QString("{\"ID\":%1 , \"X\":%2 , \"Y\":%3 }").arg(id).arg(x).arg(y));

        tile t;
        t.ID = ID;
        t.X = X;
        t.Y = Y;

        pice.append(t);
    }

};



class JStringArray
{

public:
    QStringList element;



};



class JNumberArray
{

public:
    QStringList Value;
    QStringList tmp;


    void Initialize(QString Key)
    {
        Value << QString("\"%1\" : [").arg(Key);
    }


    void Finalize()
    {
        Value << "]";
    }

    void Next()
    {
        Value << " , ";
    }

    void Push(QString Key,int value,bool cont = false)
    {
       /* if(tmp.length() == 0)
            tmp << "{ ";
        else
            tmp << ",";*/


        Value << tmp << QString("\"%1\" : %2 ").arg(Key).arg(value);

        if(cont)
            Value << " , ";
        else
            Value << "}";
    }



};



class JSerializer
{

public:
    struct str
    {
    public:
        QString Key;
        QString Value;
    };
    QList<str> lst;
    QStringList b;


    void Initialize()
    {
        b.append("var data = {");
    }

    void Finalize()
    {
        b.append("}");
    }


    void AddObject(QString Key,QString Value)
    {
        b << QString("\"%1\" : \"%2\"").arg(Key).arg(Value);

    }


    void AddObject(JObject object)
    {
        str st;
        st.Key = object.GetKey();
        st.Value = object.GetValue();
        lst.append(st);

    }


    void Serialize()
    {
        b << "{";


        for(int i = 0; i < lst.count(); i++)
        {
            b << "\"" + lst[i].Key + "\" : \"" + lst[i].Value + "\"";

            //congiunzione
            if(i+1 < lst.count())
                b << ",";
            else
                continue;

        }

      //  b << tiles.element;

        b << "}";
    }


  QStringList& operator << (QString &s)
  {
    b.append(s);
  }


  QStringList &operator << (QStringList &s)
  {
      b << s;
  }


  QStringList &operator << (JTile tile)
  {
      str t;
      t.Key = "ID";
      t.Value = tile.pice[0].X;
      lst.append(t);
  }
};



//! JExporter a JSON Exporter tool
class JExport
{


public:
    JExport();



};

#endif // JEXPORT_H
