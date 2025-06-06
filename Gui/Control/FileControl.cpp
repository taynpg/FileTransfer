#include "FileControl.h"

#include <LocalFile.h>
#include <QDateTime>
#include <QHeaderView>
#include <QTableWidgetItem>

#include "LogControl.h"
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

void FileManager::SetModeStr(const QString& modeStr, int type)
{
    ui->lbMode->setText(modeStr);
    if (type == 0) {
        fileHelper_ = std::make_shared<LocalFile>();
    } else {
    }
    fileHelper_->registerPathCall([this](const std::wstring& path) { ShowPath(path); });
    fileHelper_->registerFileCall([this](const DirFileInfoVec& info) { ShowFile(info); });
}

void FileManager::SetLogPrint(LogPrint* log)
{
    log_ = log;
}

void FileManager::InitControl()
{
    QStringList headers;
    headers << tr("") << tr("FileName") << tr("ModifyTime") << tr("Type") << tr("Size");
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->comboBox->setEditable(true);

    connect(ui->btnHome, &QPushButton::clicked, this, &FileManager::evtHome);
    connect(ui->btnVisit, &QPushButton::clicked, this, &FileManager::evtFile);
}

void FileManager::ShowPath(const std::wstring& path)
{
    QString qPath = QString::fromStdWString(path);
    int existingIndex = ui->comboBox->findText(qPath);
    if (existingIndex != -1) {
        ui->comboBox->removeItem(existingIndex);
    } else if (ui->comboBox->count() >= 20) {
        ui->comboBox->removeItem(ui->comboBox->count() - 1);
    }
    ui->comboBox->insertItem(0, qPath);
    ui->comboBox->setCurrentIndex(0);
}

void FileManager::ShowFile(const DirFileInfoVec& info)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    ui->tableWidget->setRowCount(info.vec.size());

    for (int i = 0; i < info.vec.size(); ++i) {
        const DirFileInfo& fileInfo = info.vec[i];

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdWString(fileInfo.name)));
        QDateTime modifyTime = QDateTime::fromMSecsSinceEpoch(fileInfo.lastModifyTime);
        QString timeStr = modifyTime.toString("yyyy-MM-dd hh:mm:ss");
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(timeStr));

        QString typeStr;
        switch (fileInfo.type) {
        case File:
            typeStr = "File";
            break;
        case Dir:
            typeStr = "Dir";
            break;
        case Link:
            typeStr = "Link";
            break;
        case Other:
            typeStr = "Other";
            break;
        default:
            typeStr = "Unknown";
            break;
        }
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(typeStr));
        QString sizeStr;
        if (fileInfo.size < 1024) {
            sizeStr = QString::number(fileInfo.size) + " B";
        } else if (fileInfo.size < 1024 * 1024) {
            sizeStr = QString::number(fileInfo.size / 1024.0, 'f', 2) + " KB";
        } else {
            sizeStr = QString::number(fileInfo.size / (1024.0 * 1024.0), 'f', 2) + " MB";
        }
        if (fileInfo.type == File) {
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(sizeStr));
        } else {
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(""));
        }
    }
    // ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
}

void FileManager::evtHome()
{
    auto r = fileHelper_->GetHome();
    log_->Debug(QString("%1 get home ret:%2").arg(__FUNCTION__).arg(r));
}

void FileManager::evtFile()
{
    auto curPath = ui->comboBox->currentText();
    auto r = fileHelper_->GetDirFile(curPath.toStdWString());
    log_->Debug(QString("%1 get files ret:%2").arg(__FUNCTION__).arg(r));
}
