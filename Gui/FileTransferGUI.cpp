#include "FileTransferGUI.h"

#include <QSplitter>

#include "./ui_FileTransferGUI.h"

FileTransferGUI::FileTransferGUI(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::FileTransferGUI)
{
    ui->setupUi(this);
    InitControl();
    ControlSignal();
    ControlLayout();
    LastStart();
}

FileTransferGUI::~FileTransferGUI()
{
    ioContext_.stop();
    if (thContext_.joinable()) {
        thContext_.join();
    }
    delete ui;
}

void FileTransferGUI::InitControl()
{
    log_ = new LogPrint(this);
    userInterface_ = std::make_shared<GUIInterface>();
    userInterface_->SetLogControl(log_);

    clientCore_ = std::make_shared<ClientCore>(ioContext_);
    clientCore_->SetUserInterface(userInterface_);
}

void FileTransferGUI::ControlSignal()
{
}

void FileTransferGUI::ControlLayout()
{
    auto* splitter = new QSplitter(Qt::Vertical);
    auto* topHorizon = new QSplitter(Qt::Horizontal);
    topHorizon->addWidget(log_);
    splitter->addWidget(topHorizon);
    setCentralWidget(splitter);
}

void FileTransferGUI::LastStart()
{
    thContext_ = std::thread([this]() { ioContext_.run(); });
}
