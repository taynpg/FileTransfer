#ifndef FILECONTROL_H
#define FILECONTROL_H

#include <QWidget>

namespace Ui {
class FileManager;
}

class FileManager : public QWidget
{
    Q_OBJECT

public:
    explicit FileManager(QWidget *parent = nullptr);
    ~FileManager();

public:
    void SetModeStr(const QString& modeStr);

private:
    Ui::FileManager *ui;
};

#endif // FILECONTROL_H
