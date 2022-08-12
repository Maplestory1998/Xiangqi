#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDialog>
#include "board.h"
#include "gamecontroller.h"
#include "msgdialog.h"

#define WINDOW_WIDTH_DEFAULT    1920
#define WINDOW_HEIGHT_DEFAULT   1080


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr, GAME_MODE mode = PVP);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void loadImages();
    void drawBoard2(QPainter &painter, int r, int c, int tag);
    void drawBoard3(QPainter &pp, QPen &oldPen, int r, int c);

    void showGameResult(GAME_STATE gameState);


private:
    //new Widget to show the result
    QDialog *n;
    Ui::Widget *ui;
    
    GameController *m_gameController;
    GAME_MODE game_mode;

    QPixmap m_pieceImages[14];

    int m_chessSize;
    int m_gap;
    QPoint m_topLeft;
    int m_step;

};
#endif // WIDGET_H
