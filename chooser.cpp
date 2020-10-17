#include "chooser.h"
#include "ui_chooser.h"

Chooser::Chooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chooser)
{
    ui->setupUi(this);
}

Chooser::~Chooser()
{
    delete ui;
}
