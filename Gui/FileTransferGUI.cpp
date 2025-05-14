#include "FileTransferGUI.h"

#include "./ui_FileTransferGUI.h"

FileTransferGUI::FileTransferGUI(QWidget* parent) : QMainWindow(parent), ui(new Ui::FileTransferGUI)
{
    ui->setupUi(this);

    QString data("中文测试。");
    auto d = data.toStdString();
    int a = 0;
}

FileTransferGUI::~FileTransferGUI()
{
    delete ui;
}
