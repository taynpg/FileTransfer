#include <QApplication>

#include "FileTransferGUI.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, ".utf-8");
    QApplication a(argc, argv);

#ifdef _WIN32
    QFont font("Microsoft YaHei", 9);
    a.setFont(font);
    //a.setStyle("windows");
#endif

    FileTransferGUI w;
    w.show();
    return a.exec();
}
