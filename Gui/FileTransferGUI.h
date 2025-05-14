#ifndef FILETRANSFERGUI_H
#define FILETRANSFERGUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class FileTransferGUI;
}
QT_END_NAMESPACE

class FileTransferGUI : public QMainWindow
{
    Q_OBJECT

public:
    FileTransferGUI(QWidget* parent = nullptr);
    ~FileTransferGUI();

private:
    Ui::FileTransferGUI* ui;
};
#endif   // FILETRANSFERGUI_H
