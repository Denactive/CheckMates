#include <algorithm>
#include <random>
#include <QAbstractListModel>
#include <QGridLayout>
#include <QDebug>
#include <QLabel>
#include <QFrame>

#include  "include/chessboard.h"
#include "include/cell.h"

ChessBoard::ChessBoard(const size_t newSize, QWidget *parent)
    :QFrame(parent), size(newSize) {
    setStyleSheet("background-color: white;");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mainLayout = new QGridLayout();
    mainLayout->setAlignment(Qt::AlignCenter);

    initBoard();
    drawBoardLabels();
    arrangeFigures();

    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    clickCell = nullptr;
}

void ChessBoard::arrangeFigures() {
    King *wking = new King("white"), *bking = new King("black");
    Queen *wqueen = new Queen("white"), *bqueen = new Queen("black");
    Horse *whorse = new Horse("white"), *bhorse = new Horse("black");
    Horse *whorse2 = new Horse("white"), *bhorse2 = new Horse("black");
    Rook *wrook = new Rook("white"), *brook = new Rook("black");
    Rook *wrook2 = new Rook("white"), *brook2 = new Rook("black");
    Bishop *wbishop = new Bishop("white"), *bbishop =  new Bishop("black");
    Bishop *wbishop2 = new Bishop("white"), *bbishop2 =  new Bishop("black");
    Pawn *wpawns[8];
    Pawn *bpawns[8];
    for (size_t i = 0; i < 8; ++i) {
       wpawns[i] =  new Pawn("white");
       bpawns[i] =  new Pawn("black");
    }


    m_cells[makeIndex(0, 0)]->setFigure(brook);
    m_cells[makeIndex(0, 1)]->setFigure(bhorse);
    m_cells[makeIndex(0, 2)]->setFigure(bbishop);
    m_cells[makeIndex(0, 3)]->setFigure(bking);
    m_cells[makeIndex(0, 4)]->setFigure(bqueen);
    m_cells[makeIndex(0, 5)]->setFigure(bbishop2);
    m_cells[makeIndex(0, 6)]->setFigure(bhorse2);
    m_cells[makeIndex(0, 7)]->setFigure(brook2);

    for (size_t i = 0; i < 8; ++i) {
       m_cells[makeIndex(1, i)]->setFigure(bpawns[i]);
       m_cells[makeIndex(6, i)]->setFigure(wpawns[i]);
    }

    m_cells[makeIndex(7, 0)]->setFigure(wrook);
    m_cells[makeIndex(7, 1)]->setFigure(whorse);
    m_cells[makeIndex(7, 2)]->setFigure(wbishop);
    m_cells[makeIndex(7, 3)]->setFigure(wking);
    m_cells[makeIndex(7, 4)]->setFigure(wqueen);
    m_cells[makeIndex(7, 5)]->setFigure(wbishop2);
    m_cells[makeIndex(7, 6)]->setFigure(whorse2);
    m_cells[makeIndex(7, 7)]->setFigure(wrook2);
}

void ChessBoard::initBoard()
{
    for (int i = 0; i < 64; ++i) {
        QString color;
        if ((i + i / 8) % 2) color = "black";
        else color = "white";


        m_cells[i] = createCell(color, i / 8, i % 8, SLOT(cellClicked()));
    }
}

bool ChessBoard::move(int index)
{
    return true;
}

bool ChessBoard::isKingUnderMat(King * king)
{
    if (king != nullptr) return true;
    return false;
}

void ChessBoard::cellClicked()
{
    Cell *btn = (Cell*) sender();
    QString cell = btn->text();

    qDebug() << "In cell: " << cell;
    qDebug() << "Pos: " << btn->getPosition().first << " " << btn->getPosition().second;
    qDebug() << btn->getStyle();

    if (clickCell == nullptr) {
        btn->cellClick(true);
        clickCell = btn;
     } else {
        if (btn == clickCell) {
            btn->cellClick(false);
            clickCell = nullptr;
        } else {
            if (!btn->isHasFigure()) {
               clickCell->cellClick(false);
               btn->setFigure(clickCell->getFigure());
               clickCell->setFigure(nullptr);
               clickCell = nullptr;
            }
        }
    }
}

Cell* ChessBoard::createCell(const QString &color, int x, int y, const char *member)
{
    Cell * cell = new Cell(x, y, color);
    connect(cell, SIGNAL(clicked()), this, member);
    return cell;
}

size_t ChessBoard::getSize() const
{
    return size;
}

bool ChessBoard::isBorderOfBoard(const size_t index)
{
    return index >= size;
}

void ChessBoard::drawBoardLabels()
{
    QGridLayout *boardContainer = new QGridLayout();

    for (int i = 0; i < 64; ++i) {
        int row = i / 8;
        int col = i % 8;
         mainLayout->addWidget(m_cells[i], row + 1, col + 1);
    }

    boardContainer->setSpacing(0);


    for (int i = 0; i < 8; ++i) {
        QString numberText = QString::number(i);
        QString letterText = QString(QChar(65 + i));

        QLabel *number = new QLabel(numberText);
        number->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        number->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        QLabel *letter = new QLabel(letterText);
        letter->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(number, i + 1, 0);
        mainLayout->addWidget(letter, 0, i + 1);
    }

}

