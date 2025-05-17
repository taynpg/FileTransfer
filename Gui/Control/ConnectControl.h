#ifndef CONNECTCONTROL_H
#define CONNECTCONTROL_H

#include <ClientCore.h>
#include <QWidget>

namespace Ui {
class Connecter;
}

class LogPrint;
class Connecter : public QWidget
{
    Q_OBJECT

public:
    explicit Connecter(QWidget* parent = nullptr);
    ~Connecter();

public:
    void SetClientCore(const std::shared_ptr<ClientCore>& clientCore);
    void SetLogPrint(LogPrint* log);

private:
    void InitControl();
    void Connect();

private:
    Ui::Connecter* ui;
    LogPrint* log_;
    bool connceted_{false};
    std::shared_ptr<ClientCore> clientCore_;
};

#endif   // CONNECTCONTROL_H
