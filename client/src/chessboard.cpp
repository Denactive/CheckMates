#include <algorithm>
#include <random>
#include <QAbstractListModel>

#include  "../include/chessboard.h"

ChessBoard::ChessBoard(const size_t newSize, QObject *parrent)
    :QAbstractListModel{parrent}, size{newSize} {
    cells.resize(size * size);
    std::iota(cells.begin(), cells.end(), 1);
}

void ChessBoard::displayOnScreen()
{

}

int ChessBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return cells.size();
}

QVariant ChessBoard::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    const auto rowIndex {index.row()};

    return QVariant::fromValue(cells[rowIndex].value);
}

bool ChessBoard::move(int index)
{
//    if (static_cast<size_t>(index) >= size * size - 1) {
//        return false;
//    }

    /*move, захардкожено*/
    std::swap(cells[index].value, cells[index + 8].value);
    emit dataChanged(createIndex(index, 0), createIndex(index, size));

    return true;
}

bool ChessBoard::isKingUnderMat(King * king)
{
    if (king != nullptr) return true;
    return false;
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
