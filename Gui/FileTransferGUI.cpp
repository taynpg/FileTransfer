#include "FileTransferGUI.h"

#include <QSplitter>

#include "./ui_FileTransferGUI.h"

FileTransferGUI::FileTransferGUI(QWidget* parent) : QMainWindow(parent), ui(new Ui::FileTransferGUI)
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

    connecter_ = new Connecter(this);
    connecter_->SetClientCore(clientCore_);
    connecter_->SetLogPrint(log_);

    localFile_ = new FileManager(this);
    remoteFile_ = new FileManager(this);
    localFile_->SetModeStr(tr("Local File:"));
    remoteFile_->SetModeStr(tr("Remote File:"));

    tabWidget_ = new QTabWidget(this);
}

void FileTransferGUI::ControlSignal()
{
}

void FileTransferGUI::ControlLayout()
{
    auto* splitter = new QSplitter(Qt::Vertical);
    splitter->setHandleWidth(1);
    auto* sTop = new QSplitter(Qt::Horizontal);
    auto* sConnect = new QSplitter(Qt::Vertical);
    auto* sFile = new QSplitter(Qt::Horizontal);

    sTop->setHandleWidth(1);
    sConnect->setHandleWidth(1);
    sFile->setHandleWidth(1);

    sTop->addWidget(log_);
    sTop->addWidget(connecter_);
    sFile->addWidget(localFile_);
    sFile->addWidget(remoteFile_);
    splitter->addWidget(sTop);
    splitter->addWidget(tabWidget_);

    tabWidget_->addTab(sFile, tr("Direct Transfer"));
    setCentralWidget(splitter);
}

void FileTransferGUI::LastStart()
{
    thContext_ = std::thread([this]() { ioContext_.run(); });
}
