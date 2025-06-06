#ifndef FILECONTROL_H
#define FILECONTROL_H

#include <QWidget>
#include <Util.h>

namespace Ui {
class FileManager;
}

class LogPrint;
class FileManager : public QWidget
{
    Q_OBJECT

public:
    explicit FileManager(QWidget* parent = nullptr);
    ~FileManager();

public:
    void SetModeStr(const QString& modeStr, int type = 0);
    void SetLogPrint(LogPrint* log);

private:
    void InitControl();
    void ShowPath(const std::wstring& path);
    void ShowFile(const DirFileInfoVec& info);

private:
    void evtHome();
    void evtFile();

private:
    Ui::FileManager* ui;
    LogPrint* log_;
    std::shared_ptr<DirFileHelper> fileHelper_;
};

#endif   // FILECONTROL_H
