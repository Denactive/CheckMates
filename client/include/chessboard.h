#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QAbstractListModel>
#include <string>
//#include "../graphics.h"
#include "../include/figures.h"

//class Cell;
//class Figure;
//class ChessBoard;
//class King;

class Cell {
private:
    int x;
    int y;
    std::string color;
    bool hasFigure;
    Figure *figure;
public:
    Cell(int nx = 0, int ny = 0, std::string ncolor = "white", bool nhasFigure = false, Figure * nfigure = nullptr): x(nx), y(ny), color(ncolor), hasFigure(nhasFigure), figure(nfigure) {}
    size_t value {};
    Cell& operator=(const size_t newValue) {
        value = newValue;
        return *this;
    }
    bool operator ==(const size_t other) {
        return other == value;
    }

    void setFigure(Figure *) { hasFigure = true; };
    Figure * getFigure();
    bool isHasFigure() { return hasFigure == true; }
    void setColor(std::string ncolor) { color = ncolor; }
    std::string getColor() { return color; }
};

class IChessBoard {
    virtual void displayOnScreen() = 0;
    virtual bool move(int index) = 0;
    virtual bool isBorderOfBoard(const size_t index) = 0;
    virtual size_t getSize() const = 0;
    virtual bool isKingUnderMat(King * king) = 0;
};

class ChessBoard : public QAbstractListModel, public IChessBoard
{
    Q_OBJECT
    Q_PROPERTY(int size READ getSize CONSTANT)
public:
    static constexpr size_t defaultSize = {8};
    using Position = std::pair<size_t, size_t> const;

    ChessBoard(const size_t newSize = defaultSize, QObject * parrent = nullptr);
    void displayOnScreen() override;

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;


    Q_INVOKABLE bool move(int index) override;
    Position getPosition(size_t index);
    bool isBorderOfBoard(const size_t index) override;
    size_t getSize() const override;
    bool isKingUnderMat(King * king) override;

private:
    std::vector<Cell> cells;
    const size_t size;
    King *king;
};

#endif // CHESSBOARD_H
