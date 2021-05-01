#include <algorithm>
#include <random>
#include <QAbstractListModel>
#include <QGridLayout>
#include <QDebug>
#include <QLabel>
#include <QFrame>

#include  "include/chessboard.h"

ChessBoard::ChessBoard(const size_t newSize, QWidget *parent)
    :QFrame(parent), size(newSize) {
//    cells.resize(size * size);
//    std::iota(cells.begin(), cells.end(), 1);

    setStyleSheet("background-color: white;");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mainLayout = new QGridLayout();
    mainLayout->setAlignment(Qt::AlignCenter);

    initBoard();
    drawBoardLabels();

    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void ChessBoard::arrangeFigures() {

}

void ChessBoard::initBoard()
{
    for (int i = 0; i < 64; ++i) {
        QString color;
        if ((i + i / 8) % 2) color = "black";
        else color = "white";

        m_cells[i] = createCell(color, SLOT(cellClicked()));
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
}

//ChessBoard::Position ChessBoard::getPosition(size_t index)
//{
//    return std::make_pair(index / size, index % size);
//}

size_t ChessBoard::getSize() const
{
    return size;
}

bool ChessBoard::isBorderOfBoard(const size_t index)
{
    return index >= size;
}


Cell* ChessBoard::createCell(const QString &text, const char *member)
{
    Cell *cell = new Cell(0, 0, text, false, nullptr);
    connect(cell, SIGNAL(clicked()), this, member);
    return cell;
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
        //qDebug() << "letter: " << letterText << "\n";

        QLabel *number = new QLabel(numberText);
        number->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        number->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        QLabel *letter = new QLabel(letterText);
        letter->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(number, i + 1, 0);
        mainLayout->addWidget(letter, 0, i + 1);
        mainLayout->addWidget(number, i + 1, 10);
        mainLayout->addWidget(letter, 10, i + 1);
    }

}

