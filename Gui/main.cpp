#include <QApplication>
#include <QFile>

#include "FileTransferGUI.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

#ifdef _WIN32
    // QFont font("Microsoft YaHei", 9);
    // a.setFont(font);
    // a.setStyle("Windows");
#endif

    QFile file(":/QtTheme/theme/Flat/Light/Green/Cyan.qss");
    if (file.open(QFile::ReadOnly)) {
        a.setStyleSheet(file.readAll());
    }

    FileTransferGUI w;
    w.show();
    return a.exec();
}
