#include "FileControl.h"

#include "ui_FileControl.h"

FileManager::FileManager(QWidget* parent) : QWidget(parent), ui(new Ui::FileManager)
{
    ui->setupUi(this);
    InitControl();
}

FileManager::~FileManager()
{
    delete ui;
}

void FileManager::SetModeStr(const QString& modeStr)
{
    ui->lbMode->setText(modeStr);
}

void FileManager::InitControl()
{
    QStringList headers;
    headers << tr("") << tr("FileName") << tr("ModifyTime") << tr("Type") << tr("Size");
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}