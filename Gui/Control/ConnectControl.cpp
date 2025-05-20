#include "ConnectControl.h"

#include <future>

#include "Gui/Control/LogControl.h"
#include "Gui/GUIUtil/Public.h"
#include "ui_ConnectControl.h"

Connecter::Connecter(QWidget* parent) : QWidget(parent), ui(new Ui::Connecter)
{
    ui->setupUi(this);
    InitControl();
}

Connecter::~Connecter()
{
    if (thConnect_.joinable()) {
        thConnect_.join();
    }
    delete ui;
}

void Connecter::SetClientCore(const std::shared_ptr<ClientCore>& clientCore)
{
    clientCore_ = clientCore;
}

void Connecter::SetLogPrint(LogPrint* log)
{
    log_ = log;
}

void Connecter::Connect()
{
    auto ip = ui->edIP->text().trimmed();
    auto port = ui->edPort->text().trimmed();
    if (ip.isEmpty() || port.isEmpty()) {
        FTCommon::msg(this, tr("IP or Port is empty"));
        return;
    }
    auto task = [this, ip, port]() {
        emit sendConnect(ConnectState::CS_CONNECTING);
        connceted_ = clientCore_->Connect(ip.toStdString(), port.toInt());
        if (connceted_) {
            emit sendConnect(ConnectState::CS_CONNECTED);
        } else {
            emit sendConnect(ConnectState::CS_DISCONNECT);
        }
    };
    if (thConnect_.joinable()) {
        thConnect_.join();
    }
    thConnect_ = std::thread(task);
}

void Connecter::setState(ConnectState cs)
{
    switch (cs) {
    case CS_CONNECTING:
        ui->btnConnect->setEnabled(false);
        ui->btnDisconnect->setEnabled(false);
        log_->Info(tr("Connecting..."));
        break;
    case CS_CONNECTED:
        ui->btnConnect->setEnabled(false);
        ui->btnDisconnect->setEnabled(true);
        break;
    case CS_DISCONNECT:
        ui->btnConnect->setEnabled(true);
        ui->btnDisconnect->setEnabled(false);
        break;
    default:
        break;
    }
}

void Connecter::InitControl()
{
    ui->btnDisconnect->setEnabled(false);
    ui->edIP->setText("127.0.0.1");
    ui->edPort->setText("9009");
    connect(ui->btnConnect, &QPushButton::clicked, this, &Connecter::Connect);
    connect(this, &Connecter::sendConnect, this, &Connecter::setState);
}
