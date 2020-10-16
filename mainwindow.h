#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "launcher.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void MoveEdge();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

    void rightClickMenu();
    void showIcon();




    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void stopAndExit();
    void addFolder();
    void onTaskBoxContextMenuEvent();

private:
    QSystemTrayIcon m_trayIcon;
    Ui::MainWindow *ui;
    QPixmap m_Pixmap;
    QPoint m_CurrentPos;

    Launcher launcher;

};

#endif // MAINWINDOW_H
