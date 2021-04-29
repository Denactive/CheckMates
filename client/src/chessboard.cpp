#include <algorithm>
#include <random>
#include <QAbstractListModel>
#include <QGridLayout>
#include <QDebug>

#include  "../include/chessboard.h"

ChessBoard::ChessBoard(const size_t newSize, QWidget *parent)
    :QGridLayout(parent), size(newSize) {
//    cells.resize(size * size);
//    std::iota(cells.begin(), cells.end(), 1);
    for (int i = 0; i < 64; ++i) {
        QString color;
        //if ((i % 2 && (i / 8)) % 2 || (!(i % 2) && !((i / 8) % 2))) color = "black";
        if ((i + i / 8) % 2) color = "black";
        else color = "white";

        m_cells[i] = createCell(color, SLOT(cellClicked()));
    }

//    mainLayout->addWidget(m_lineup, 1, 1);
//    mainLayout->addWidget(m_sign, 2, 1);
//    mainLayout->addWidget(m_linedown, 3, 1);

    for (int i = 0; i < 64; ++i) {
        int row = i / 8;
        int col = i % 8;
        addWidget(m_cells[i], row, col);
    }

    setSpacing(0);
}

void ChessBoard::displayOnScreen()
{

}

//int ChessBoard::rowCount(const QModelIndex &parent) const
//{
//    Q_UNUSED(parent)
//    return cells.size();
//}

//QVariant ChessBoard::data(const QModelIndex &index, int role) const
//{
////    if (!index.isValid() || role != Qt::DisplayRole) {
////        return {};
////    }

//    const auto rowIndex {index.row()};

//    return QVariant::fromValue(cells[rowIndex].value);
//}

bool ChessBoard::move(int index)
{
//    if (static_cast<size_t>(index) >= size * size - 1) {
//        return false;
//    }

    /*move, захардкожено*/
//    std::swap(cells[index].value, cells[index + 8].value);
//    emit dataChanged(createIndex(index, 0), createIndex(index, size));

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
    int cell = btn->text().toInt();
    qDebug() << "In cell: " << cell;

    //m_lineup->clear();
    //m_lineup->setText(QString::number(cell));
}

ChessBoard::Position ChessBoard::getPosition(size_t index)
{
    return std::make_pair(index / size, index % size);
}

size_t ChessBoard::getSize() const
{
    return size;
}

bool ChessBoard::isBorderOfBoard(const size_t index)
{
    return index >= size;
}

Cell::Cell(int nx, int ny, const QString &ncolor, bool nhasFigure, Figure *nfigure, QWidget *parent)
    :QToolButton(parent), x(nx), y(ny), color(ncolor), hasFigure(nhasFigure), figure(nfigure) {
    setText(ncolor);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

    QString style = "";
    if (ncolor == "white") style += "background-color: #ffb972;";
    if (ncolor == "black") style += "background: #58310C;";

    style += "border-image: url(../img/figures/tournament_metal/wN.png) 0 0 0 0 scretch; \
                    color: transparent; \
                    background-position: center; \
                    border: 1px solid black;\
                    ";

    setStyleSheet(style);
}

QSize Cell::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 30;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}

Cell* ChessBoard::createCell(const QString &text, const char *member)
{
    Cell *cell = new Cell(0, 0, text, false, nullptr);
    connect(cell, SIGNAL(clicked()), this, member);
    return cell;
}

