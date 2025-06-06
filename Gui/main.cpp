#include <QApplication>

#include "FileTransferGUI.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

#ifdef _WIN32
    QFont font("Microsoft YaHei", 10);
    a.setFont(font);
    a.setStyle("windows");
#endif

    FileTransferGUI w;
    w.show();
    return a.exec();
}
