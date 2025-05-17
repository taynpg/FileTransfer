#include "FileControl.h"
#include "ui_FileControl.h"

FileManager::FileManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileManager)
{
    ui->setupUi(this);
}

FileManager::~FileManager()
{
    delete ui;
}
