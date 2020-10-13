

#include "luancher.h"

Luancher::Luancher()
{

}


void Luancher::openFolder(QString path){

    path = "file:" + path;
    QDesktopServices::openUrl(QUrl(path, QUrl::TolerantMode));
}
