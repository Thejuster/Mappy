#include "newmap.h"
#include "ui_newmap.h"

NewMap::NewMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMap)
{
    ui->setupUi(this);
}

NewMap::~NewMap()
{
    delete ui;
}

void NewMap::on_spinBox_valueChanged(int arg1)
{
    this->blw = arg1;
    UpdateSize();

}

void NewMap::on_spinBox_2_valueChanged(int arg1)
{
    this->blh = arg1;
    UpdateSize();
}

void NewMap::UpdateSize()
{
    ui->label_4->setText(tr("Map Size: %1 X %2 Pixel").arg(blw * 32).arg(blh * 32));
}


void NewMap::on_buttonBox_accepted()
{

}
