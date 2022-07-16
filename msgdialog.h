#ifndef MSGDIALOG_H
#define MSGDIALOG_H

#include <QDialog>

namespace Ui {
class MsgDialog;
}

class MsgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MsgDialog(QWidget *parent = nullptr);
    ~MsgDialog();

private:
    Ui::MsgDialog *ui;
};

#endif // MSGDIALOG_H
