#include "LogControl.h"

#include <QDateTime>
#include <QStandardItem>

#include "ui_LogControl.h"

LogPrint::LogPrint(QWidget* parent) : QWidget(parent), ui(new Ui::LogPrint)
{
    ui->setupUi(this);
    InitControl();
}

void LogPrint::InitControl()
{
    model_ = new QStandardItemModel(this);
    ui->listView->setModel(model_);
}

LogPrint::~LogPrint() { delete ui; }

void LogPrint::Info(const QString& message) { Print(message, Qt::black); }
void LogPrint::Warn(const QString& message) { Print(message, Qt::yellow); }
void LogPrint::Error(const QString& message) { Print(message, Qt::red); }
void LogPrint::Debug(const QString& message) { Print(message, Qt::blue); }
void LogPrint::Print(const QString& message, const QBrush& color)
{
    auto* item = new QStandardItem(message);
    item->setForeground(color);
    model_->appendRow(item);
    ui->listView->scrollToBottom();
}
