#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QDebug>
#include <QDesktopWidget>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget), m_gameController(new GameController),
    m_chessSize(0),   m_gap(0), m_step(0)
{
    ui->setupUi(this);
    resize(WINDOW_WIDTH_DEFAULT , WINDOW_HEIGHT_DEFAULT);
    setMinimumSize(WINDOW_WIDTH_DEFAULT , WINDOW_HEIGHT_DEFAULT);

    loadImages();
}

void Widget::loadImages()
{
    for(int i = 0; i < 14; ++i)
    {
        m_pieceImages[i].load(g_imagesSources[i]);
    }
}

Widget::~Widget()
{
    delete ui;
    delete m_gameController;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    //get window info (excluding any window frame)
    int windowWidth = this->geometry().width();
    int windowHeight = this->geometry().height();
    qDebug()<<windowWidth<<windowHeight;
    float scaleY = static_cast<float>(windowHeight) / static_cast<float>(WINDOW_HEIGHT_DEFAULT);

    //set the size of the pixmap
    m_gap = 100;
    int size = windowHeight - 100;

    QPainter painter(this);
    QPixmap pix(size , size);
    pix.fill(Qt::white);
    //新建QPainter类对象，在pix上进行绘图
    QPainter pp(&pix);

    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(4);
    pp.setPen(pen);

    m_topLeft = QPoint(m_gap / 2 * scaleY + 50,  m_gap / 2 * scaleY);

    m_step = size / 10;
    for(int i = 0; i < 10; ++i)
    {
        pp.drawLine(m_topLeft.x(), m_topLeft.y() +  m_step * i, m_topLeft.x() + m_step * 8, m_topLeft.y() + m_step * i);
    }

    pp.drawLine(m_topLeft.x(), m_topLeft.y() , m_topLeft.x(), m_topLeft.y() + m_step * 9);
    pp.drawLine(m_topLeft.x() + 8 * m_step, m_topLeft.y(), m_topLeft.x() + 8 * m_step, m_topLeft.y() + m_step * 9);
    for(int i = 1; i < 8; ++i)
    {
        pp.drawLine(m_topLeft.x() + m_step * i, m_topLeft.y(), m_topLeft.x() + m_step * i,  m_topLeft.y() + m_step * 4);
        pp.drawLine(m_topLeft.x() + m_step * i, m_topLeft.y() + 9 * m_step, m_topLeft.x() + m_step * i, m_topLeft.y() + m_step * 5);
    }

    pp.drawLine(m_topLeft.x() + m_step * 3, m_topLeft.y(), m_topLeft.x() + m_step * 5, m_topLeft.y() + m_step * 2);
    pp.drawLine(m_topLeft.x() + m_step * 5, m_topLeft.y(), m_topLeft.x() + m_step * 3, m_topLeft.y() + m_step * 2);

    pp.drawLine(m_topLeft.x() + m_step * 3, m_topLeft.y() + m_step * 9, m_topLeft.x() + m_step * 5, m_topLeft.y() + m_step * 7);
    pp.drawLine(m_topLeft.x() + m_step * 5, m_topLeft.y() + m_step * 9, m_topLeft.x() + m_step * 3, m_topLeft.y() + m_step * 7);


    drawBoard2(pp, 3, 0, 2);
    drawBoard2(pp, 3, 8, 1);

    drawBoard2(pp, 6, 0, 2);
    drawBoard2(pp, 6, 8, 1);

    for(int i = 2; i < 8; i += 2)
    {
        drawBoard2(pp, 3, i , 3);
        drawBoard2(pp, 6, i , 3);
    }

    drawBoard2(pp, 2, 1, 3);
    drawBoard2(pp, 2, 7, 3);
    drawBoard2(pp, 7, 1, 3);
    drawBoard2(pp, 7, 7, 3);


      //draw pieces
    m_chessSize = m_step;

    for(int r = 0; r < 10; ++r)
    {
        for(int c = 0; c < 9; ++c)
        {
            PIECE_TYPE type = m_gameController->getBoard()->getPieceType(r, c);
            if(type != NO_PIECE)
            {
                pp.drawPixmap(m_topLeft.x() + m_step * c - m_chessSize / 2
                              , m_topLeft.y() + m_step * r - m_chessSize / 2,
                              m_chessSize , m_chessSize , m_pieceImages[type]);
            }
        }
    }


    if(m_gameController->getGameState() == WAIT_MOVE)
    {
        drawBoard3(pp, pen, m_gameController->getChosePos().first, m_gameController->getChosePos().second);
        qDebug()<<m_gameController->getChosePos().first<<m_gameController->getChosePos().second;
    }

    painter.drawPixmap(m_gap / 2, m_gap / 2, pix);
}


void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return ;


    int posX = event->pos().x() - m_gap / 2;
    int posY = event->pos().y() - m_gap / 2;

    int cIdx = static_cast<float>(posX - m_topLeft.x()) / static_cast<float>(m_step) + 0.5f;
    int rIdx = static_cast<float>(posY - m_topLeft.y()) / static_cast<float>(m_step) + 0.5f;

    PIECE_TYPE type = m_gameController->getBoard()->getPieceType(rIdx, cIdx);

    qDebug()<<rIdx<<cIdx;
    qDebug()<<type;

    GAME_STATE currentState = m_gameController->controller(rIdx, cIdx);
    update();
}

// draw "#" on board.  tag: 1- left, 2- right, 3-full
void Widget::drawBoard2(QPainter &painter, int r, int c, int tag)
{
    int gapLine = 5;
    int lineLength = 5;
    int x = m_topLeft.x() + m_step * c;
    int y = m_topLeft.y() + m_step * r;

    if(tag & 0x1)
    {
        //left top
        painter.drawLine(x - gapLine - lineLength,  y - gapLine, x - gapLine, y - gapLine);
        painter.drawLine(x - gapLine, y - gapLine, x - gapLine, y - gapLine - lineLength);

        //left bottom
        painter.drawLine(x - gapLine, y + gapLine, x - gapLine - lineLength, y + gapLine);
        painter.drawLine(x - gapLine, y + gapLine, x - gapLine, y + gapLine + lineLength);
    }

    if(tag & 0x2)
    {
        //right top
        painter.drawLine(x + gapLine, y - gapLine, x + gapLine + lineLength, y - gapLine);
        painter.drawLine(x + gapLine, y - gapLine, x + gapLine, y - gapLine - lineLength);

        //right bottom
        painter.drawLine(x + gapLine, y + gapLine, x + gapLine + lineLength, y + gapLine);
        painter.drawLine(x + gapLine, y + gapLine, x + gapLine, y + gapLine + lineLength);
    }
}

void Widget::drawBoard3(QPainter &pp, QPen &oldPen, int r, int c)
{
    QPen pen;
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(4);
    pp.setPen(pen);

    int x = m_topLeft.x() + c * m_step;
    int y = m_topLeft.y() + r * m_step;
    int lineLength = m_chessSize / 3;

    //left top
    pp.drawLine(x - m_chessSize / 2, y - m_chessSize / 2, x - m_chessSize / 2 + lineLength, y - m_chessSize / 2);
    pp.drawLine(x - m_chessSize / 2, y - m_chessSize / 2, x - m_chessSize / 2, y - m_chessSize / 2 + lineLength);

    //right top
    pp.drawLine(x + m_chessSize / 2, y - m_chessSize / 2, x + m_chessSize / 2 - lineLength, y - m_chessSize / 2);
    pp.drawLine(x + m_chessSize / 2, y - m_chessSize / 2, x + m_chessSize / 2, y - m_chessSize / 2 + lineLength);

    //right bottom
    pp.drawLine(x + m_chessSize / 2, y + m_chessSize / 2, x + m_chessSize / 2 - lineLength, y + m_chessSize / 2);
    pp.drawLine(x + m_chessSize / 2, y + m_chessSize / 2, x + m_chessSize / 2, y + m_chessSize / 2 - lineLength);

    //left bottom
    pp.drawLine(x - m_chessSize / 2, y + m_chessSize / 2, x - m_chessSize / 2 + lineLength, y + m_chessSize / 2);
    pp.drawLine(x - m_chessSize / 2, y + m_chessSize / 2, x - m_chessSize / 2, y + m_chessSize / 2 - lineLength);

    pp.setPen(oldPen);

}



















