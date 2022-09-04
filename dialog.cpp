#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

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
    this->hide();
    emit showPVPWindow();
}

void Dialog::on_exit_clicked()
{
    this->hide();
    emit quit();
}


void Dialog::on_pve_clicked()
{
    this->hide();
    emit showPVEWindow();
}
