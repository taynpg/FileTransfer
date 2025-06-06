#include <QApplication>

#include "FileTransferGUI.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

#ifdef _WIN32
    // QFont font("Microsoft YaHei", 9);
    // a.setFont(font);
    // a.setStyle("Windows");
#endif

    FileTransferGUI w;
    w.show();
    return a.exec();
}
