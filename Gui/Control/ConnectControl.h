#ifndef CONNECTCONTROL_H
#define CONNECTCONTROL_H

#include <QWidget>

namespace Ui {
class Connecter;
}

class Connecter : public QWidget
{
    Q_OBJECT

public:
    explicit Connecter(QWidget *parent = nullptr);
    ~Connecter();

private:
    Ui::Connecter *ui;
};

#endif // CONNECTCONTROL_H
