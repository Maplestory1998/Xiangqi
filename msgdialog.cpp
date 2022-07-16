#include "msgdialog.h"
#include "ui_msgdialog.h"

MsgDialog::MsgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgDialog)
{
    ui->setupUi(this);
}

MsgDialog::~MsgDialog()
{
    delete ui;
}
