#include "LogControl.h"
#include "ui_LogControl.h"

LogPrint::LogPrint(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LogPrint)
{
    ui->setupUi(this);
}

LogPrint::~LogPrint()
{
    delete ui;
}
