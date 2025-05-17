#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#if defined(USE_QT_GUI)
// #include <QObject>
// #define tr(str) QObject::tr(str)
#else
#define tr(str) (str)
#endif

#endif   // GLOBALDEFINE_H