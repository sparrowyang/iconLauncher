

#include "launcher.h"


Launcher::Launcher():
    m_settings("D:/workspace/qt/sparrow_lancher/config/settings.ini",QSettings::IniFormat)
{
    this->setTitle(tr("启动..."));
    m_settings.setIniCodec(QTextCodec::codecForName("utf-8"));
    m_settings.beginGroup("/path");
    QStringList allkeys = m_settings.childKeys();

    QString i;
    QAction* act;
    foreach (i, allkeys) {
        act = new QAction(i);
        connect(act,SIGNAL(triggered()),this,SLOT(openFolder()));
        act->setData(m_settings.value(i));
        this->addAction(act);
    }
    m_settings.endGroup();
}

Launcher::~Launcher(){
    qDebug()<<"closing launcher...";

}


void Launcher::openFolder(){
    QAction *pEven = qobject_cast<QAction *>(this->sender());
    QString path = pEven->data().toString();
    qDebug()<<"open folder "<<path;
    path = "file:" + path;
    QDesktopServices::openUrl(QUrl(path, QUrl::TolerantMode));
}

/* 超级大的坑：
 * QFileDialog::getExistingDirectory()第一个参数要一个窗口的指针
 * 如果为空，则选择完文件后程序会退出，暂时不知道啥原因。
 * 试了一下，当第一个参数是主窗口才能保证程序不退出
 * 所以，得传窗口指针进来才能用
 * DEBUG 2小时+
 * */
void Launcher::addFolder(QWidget* w){
    QString srcDirPath = QFileDialog::getExistingDirectory(w,QObject::tr("s"),"D:/",QFileDialog::DontUseNativeDialog);
    QString dirName = srcDirPath.split('/')[srcDirPath.split('/').length()-1];
    qDebug()<<dirName;
    m_folder_map.insert(dirName,srcDirPath);

}


void Launcher::saveIni(){
    if(m_folder_map.isEmpty()){
        return;
    }
    m_settings.beginGroup("/path");
    for(auto x:m_folder_map.keys()){
        qDebug()<<"saving ini..."<<x<<m_folder_map[x];
        m_settings.setValue(x,m_folder_map[x]);
    }
    m_settings.endGroup();
}


