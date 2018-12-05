#include "about.h"
#include "ui_about.h"
#include "qmessagebox.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    connect( ui->label_7, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );

}

About::~About()
{
    delete ui;
}




