#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    QMenu *pMenu = new QMenu(this);


    QMenu *pNewTask = new QMenu(tr("启动"), this);
    QAction *taskExplore = new QAction(tr("文件管理器"), this);

    QAction *pEditTask = new QAction(tr("设置任务"), this);
    QAction *pDeleteTask = new QAction(tr("删除任务"), this);
    QAction *pToolRenName = new QAction(tr("改名工具"), this);
    QAction *pToolEdot = new QAction(tr("设置工具"), this);
    QAction *pToolDelete = new QAction(tr("退出"), this);

    //1:新建任务 2:设置任务 3:删除任务 4:改名工具 5:设置工具 6:删除工具
    taskExplore->setData(1);
    pEditTask->setData(2);
    pDeleteTask ->setData(3);
    pToolRenName->setData(4);
    pToolEdot->setData(5);
    pToolDelete ->setData(6);

    pNewTask->addAction(taskExplore);
    //把QAction对象添加到菜单上
    pMenu->addMenu(pNewTask);
    pMenu->addAction(pEditTask);
    pMenu->addAction(pDeleteTask);
    pMenu->addAction(pToolRenName);
    pMenu->addAction(pToolEdot);
    pMenu->addAction(pToolDelete);

    //连接鼠标右键点击信号
    //链接Qaction 的点击信号到 onTaskBoxContextMenuEvent()槽，这样
    //点击QAction 后会发送信号，槽就会收到。
    connect(taskExplore, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pEditTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pDeleteTask, SIGNAL(triggered()), SLOT(onTaskBoxContextMenuEvent()));
    connect(pToolRenName, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pToolEdot, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pToolDelete, SIGNAL(triggered()), SLOT(onTaskBoxContextMenuEvent()));

    //在鼠标右键点击的地方显示菜单
    pMenu->exec(cursor().pos());

    //释放内存
    QList<QAction*> list = pMenu->actions();
    foreach (QAction* pAction, list) delete pAction;
    delete pMenu;
}

void MainWindow::onTaskBoxContextMenuEvent()
{
    QAction *pEven = qobject_cast<QAction *>(this->sender()); //this->sender()就是发信号者 QAction

    //获取发送信息类型 1:新建任务 2:设置任务 3:删除任务 4:改名工具 5:设置工具 6:删除工具
    int iType = pEven->data().toInt();

    switch (iType)
    {
    case 1:

        luancher.openFolder(QString::fromLocal8Bit("D:/QQ_data"));
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


    m_trayIcon.setIcon(QIcon(":/img/ouc.png"));     //设置图标
    m_trayIcon.setToolTip(tr("Known image viewer"));    //设置鼠标放上去显示的信息
    QMenu *menu = new QMenu(this);			 //右键菜单
    QAction *quit = new QAction(tr("退出"),this);
    menu->addAction(quit);
    m_trayIcon.setContextMenu(menu); 			 //设置右键菜单
    connect(quit, SIGNAL(triggered()),this, SLOT(stopAndExit()));

    //不显示任务栏
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool );
    m_trayIcon.show();
}
void MainWindow::stopAndExit(){
    close();
    m_trayIcon.hide();
}




