#ifndef MSGDIALOG_H
#define MSGDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class MsgDialog;
}

class MsgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MsgDialog(QWidget *parent = nullptr, QString _str = "");
    ~MsgDialog();

private slots:
    void on_quitGame_clicked();

private:
    Ui::MsgDialog *ui;

    QString str;
};

#endif // MSGDIALOG_H
