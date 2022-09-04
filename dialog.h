#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    bool isPVE;

private slots:
    void on_pvp_clicked();

    void on_exit_clicked();

    void on_pve_clicked();

signals:
    void showPVPWindow();
    void showPVEWindow();
    void quit();


private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
