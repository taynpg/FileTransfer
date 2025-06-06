#ifndef FILETRANSFERGUI_H
#define FILETRANSFERGUI_H

#include <ClientCore.h>
#include <QMainWindow>
#include <thread>
#include <QTabWidget>
#include <QFile>

#include "Control/LogControl.h"
#include "GUIUtil/GUIInterface.h"
#include "Control/FileControl.h"
#include "Control/ConnectControl.h"

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
    void InitControl();
    void ControlSignal();
    void ControlLayout();
    void LastStart();

private:
    bool thRun_{false};
    std::thread thContext_;
    asio::io_context ioContext_;
    std::shared_ptr<ClientCore> clientCore_;
    std::shared_ptr<GUIInterface> userInterface_;
    Ui::FileTransferGUI* ui;
    LogPrint* log_;
    QTabWidget* tabWidget_;
    Connecter* connecter_;
    FileManager* localFile_;
    FileManager* remoteFile_;
};
#endif   // FILETRANSFERGUI_H
