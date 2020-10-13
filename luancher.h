#ifndef LUANCHER_H
#define LUANCHER_H
/**
  * name   : 启动器类
  * auther : sparrowyang
  * time   : 2020-10-13
  * func   : 用于启动文件夹、应用、命令行
  */
#include <QString>
#include <QDesktopServices>
#include <QUrl>


class Luancher
{
public:
    Luancher();
    //--------------
    void openFolder(QString path);

};

#endif // LUANCHER_H
