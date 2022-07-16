#include "widget.h"
#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog  dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        Widget w(nullptr, PVP);
        w.show();
        return a.exec();
    }
    else if(dlg.exec() == QDialog::Rejected){
        Widget w(nullptr, PVE);
        w.show();
        return a.exec();
    }

    return 0;
}
