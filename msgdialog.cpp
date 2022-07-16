#include "msgdialog.h"
#include "ui_msgdialog.h"

MsgDialog::MsgDialog(QWidget *parent, QString _str) :
    QDialog(parent),
    ui(new Ui::MsgDialog), str(_str)
{
    ui->setupUi(this);
    QMessageBox::information(this, tr("Result:"), str);
}

MsgDialog::~MsgDialog()
{
    delete ui;
}

void MsgDialog::on_quitGame_clicked()
{
    qApp->quit();
}
