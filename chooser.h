#ifndef CHOOSER_H
#define CHOOSER_H

#include <QDialog>

namespace Ui {
class Chooser;
}

class Chooser : public QDialog
{
    Q_OBJECT

public:
    explicit Chooser(QWidget *parent = 0);
    ~Chooser();

private:
    Ui::Chooser *ui;
};

#endif // CHOOSER_H
