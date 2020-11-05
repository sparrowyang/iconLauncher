#ifndef CHOOSER_H
#define CHOOSER_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
#include <QTextCodec>

namespace Ui {
class Chooser;
}

class Chooser : public QDialog
{
    Q_OBJECT

public:
    explicit Chooser(QWidget *parent = 0);
    ~Chooser();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Chooser *ui;
};

#endif // CHOOSER_H
