#include <QApplication>

#include "FileTransferGUI.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    FileTransferGUI w;
    w.show();
    return a.exec();
}
