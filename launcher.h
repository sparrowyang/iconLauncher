#ifndef LAUNCHER_H
#define LAUNCHER_H
/**
  * name   : 启动器类
  * auther : sparrowyang
  * time   : 2020-10-13
  * func   : 用于启动文件夹、应用、命令行
  */

#include <QString>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>
#include <QFileDialog>
#include <QDebug>
#include <QTextCodec>
#include <QMenu>

class Launcher:public QMenu
{
    Q_OBJECT
public slots:
    void openFolder();

public:
    Launcher();
    ~Launcher();
    //--------------

    void addFolder(QWidget* w);
    void runProsess();
    void addProsess();
    void runShell();
    void addShell();
    void saveIni();


protected:
    QSettings m_settings;

    QMap<QString,QString> m_folder_map;
    QMap<QString,QString> m_prosess_map;
    QMap<QString,QString> m_shell_map;




};

#endif // LAUNCHER_H
