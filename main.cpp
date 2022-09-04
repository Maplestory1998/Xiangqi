#include "widget.h"
#include "dialog.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog  dlg;
    Widget pvp(nullptr, PVP);
    Widget pve(nullptr, PVE);
    dlg.show();
    QObject::connect(&dlg, SIGNAL(showPVPWindow()), &pvp, SLOT(showWindow()));
    QObject::connect(&dlg, SIGNAL(showPVEWindow()), &pve, SLOT(showWindow()));
    QObject::connect(&dlg, SIGNAL(quit()), &a, SLOT(quit()));
    return a.exec();
}
