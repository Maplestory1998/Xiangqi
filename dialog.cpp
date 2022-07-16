#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent), isPVE(true),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pvp_clicked()
{
    accept();
}

void Dialog::on_exit_clicked()
{
    qApp->quit();
}


void Dialog::on_pve_clicked()
{
    reject();
}
