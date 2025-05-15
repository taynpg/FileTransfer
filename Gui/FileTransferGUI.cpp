#include "FileTransferGUI.h"

#include "./ui_FileTransferGUI.h"

FileTransferGUI::FileTransferGUI(QWidget* parent) : QMainWindow(parent), ui(new Ui::FileTransferGUI)
{
    ui->setupUi(this);
}

FileTransferGUI::~FileTransferGUI()
{
    delete ui;
}
