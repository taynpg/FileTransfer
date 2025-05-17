#include "ConnectControl.h"

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
    connceted_ = clientCore_->Connect(ip.toStdString(), port.toInt());
}

void Connecter::InitControl()
{
    ui->edIP->setText("127.0.0.1");
    ui->edPort->setText("9009");
    connect(ui->btnConnect, &QPushButton::clicked, this, &Connecter::Connect);
}
