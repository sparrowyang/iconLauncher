#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chooser.h"

#include <QtGui>
#include <QMessageBox>
#include <QPropertyAnimation>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("我设置的标题");
    m_Pixmap.load(":/img/ouc.png");
    resize(m_Pixmap.size());
    setMask(m_Pixmap.mask());

    showIcon();
}

MainWindow::~MainWindow()
{

    delete ui;
    qDebug()<<"closing MainWindow..";

}

void MainWindow::MoveEdge(){

}



void MainWindow::mousePressEvent(QMouseEvent *event)
{

    //按住左键可以托动窗口，按下右键关闭程序
    if(event->button() == Qt::LeftButton)
    {

        m_CurrentPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    else if(event->button() == Qt::RightButton){
        //QString srcDirPath = QFileDialog::getExistingDirectory(this,QObject::tr("s"),"D:/",QFileDialog::DontUseNativeDialog);
        rightClickMenu();
        //mbar.show();
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() && Qt::LeftButton)
    {
        move(event->globalPos() - m_CurrentPos);
        event->accept();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.drawPixmap(0, 0, m_Pixmap);
}

void MainWindow::leaveEvent(QEvent *event)
{
    //鼠标离开窗口时是普通的指针
    setCursor(Qt::ArrowCursor);
}

void MainWindow::enterEvent(QEvent *event)
{


    //鼠标留在窗口上时是一个手指

    setCursor(Qt::PointingHandCursor);
}

void MainWindow::rightClickMenu(){
    /*
    这些东西最好写在类成员里，每次创建和销毁有点鸡肋
    */

    //在鼠标右键点击的地方显示菜单
    launcher.exec(cursor().pos());

}

void MainWindow::onTaskBoxContextMenuEvent()
{
    QAction *pEven = qobject_cast<QAction *>(this->sender()); //this->sender()就是发信号者 QAction

    //获取发送信息类型 1:新建任务 2:设置任务 3:删除任务 4:改名工具 5:设置工具 6:删除工具
    int iType = pEven->data().toInt();

    switch (iType)
    {
    case 1:
        launcher.addFolder(this);
        //luancher.openFolder(QString::fromLocal8Bit("D:/QQ_data"));
        break;
    case 2:
        QMessageBox::about(this, "tip", pEven->text());
        break;
    case 3:
        QMessageBox::about(this, "tip", pEven->text());
        break;
    case 4:
        QMessageBox::about(this, "tip", pEven->text());
        break;
    case 5:
        QMessageBox::about(this, "tip", pEven->text());
        break;
    case 6:
        close();
        break;
    default:
        break;
    }
}

void MainWindow::showIcon(){
    //设置图标
    m_trayIcon.setIcon(QIcon(":/img/ouc.png"));
    m_trayIcon.setToolTip(tr("Known image viewer"));    //设置鼠标放上去显示的信息
    //右键菜单
    QMenu *menu = new QMenu(this);
    QAction *quit = new QAction(tr("退出"),this);
    QAction *addFolderAct = new QAction(tr("添加文件夹"),this);
    menu->addAction(quit);
    menu->addAction(addFolderAct);
    m_trayIcon.setContextMenu(menu); 			 //设置右键菜单
    connect(quit, SIGNAL(triggered()),this, SLOT(stopAndExit()));
    connect(addFolderAct, SIGNAL(triggered()),this, SLOT(addFolder()));
    //不显示任务栏
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool );
    m_trayIcon.show();
}


void MainWindow::stopAndExit(){
    QApplication* app;
    app->exit(0);
}

void MainWindow::addFolder(){

    Chooser chooser(this);
    chooser.exec();

}


