#ifndef NEWMAP_H
#define NEWMAP_H

#include <QDialog>

namespace Ui {
class NewMap;
}

class NewMap : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewMap(QWidget *parent = 0);
    ~NewMap();
    int blw = 0;
    int blh = 0;
    void UpdateSize();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

private:
    Ui::NewMap *ui;
};

#endif // NEWMAP_H
