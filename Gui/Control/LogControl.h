#ifndef LOGCONTROL_H
#define LOGCONTROL_H

#include <QWidget>

namespace Ui {
class LogPrint;
}

class LogPrint : public QWidget
{
    Q_OBJECT

public:
    explicit LogPrint(QWidget *parent = nullptr);
    ~LogPrint();

private:
    Ui::LogPrint *ui;
};

#endif // LOGCONTROL_H
