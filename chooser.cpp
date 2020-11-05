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

void Chooser::on_pushButton_clicked()
{
    QString name = ui->c_name->text();
    if(name==""){
        return;
    }
    //0 path 1 ps 2 sh
    int type = ui->c_type->currentIndex();
    QString stype;
    switch (type) {
    case 0:
        stype = "/path";
        break;
    case 1:
        stype = "/run";
        break;
    case 2:
        stype = "/shell";
        break;
    default:
        break;
    }
    QString src_path = QFileDialog::getExistingDirectory(this,QObject::tr("s"),"D:/",QFileDialog::DontUseNativeDialog);
    QSettings qs("D:/workspace/qt/sparrow_lancher/config/settings.ini",QSettings::IniFormat);
    qs.setIniCodec(QTextCodec::codecForName("utf-8"));
    qs.beginGroup(stype);
    qs.setValue(name,src_path);
}
