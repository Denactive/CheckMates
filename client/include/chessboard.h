#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QAbstractListModel>
#include <string>
#include <QToolButton>
#include <QSize>
#include <QGridLayout>
#include <QWidget>
#include <QFrame>

#include "include/cell.h"
#include "include/figures.h"

class IChessBoard {
    virtual void arrangeFigures() = 0;
    virtual bool move(int index) = 0;
    virtual bool isBorderOfBoard(const size_t index) = 0;
    virtual size_t getSize() const = 0;
    virtual bool isKingUnderMat(King * king) = 0;
};

class ChessBoard : public QFrame,  public IChessBoard
{
    Q_OBJECT
public:
    static constexpr size_t defaultSize = {8};
    ChessBoard(const size_t newSize = defaultSize, QWidget * parent = nullptr);
    void arrangeFigures() override;;
    bool move(int index) override;
    bool isBorderOfBoard(const size_t index) override;
    size_t getSize() const override;
    bool isKingUnderMat(King * king) override;

private slots:
    void cellClicked();

private:
    QGridLayout *mainLayout;
    Cell* m_cells[64];
    Cell *clickCell;
    const size_t size;

    Cell* createCell(const QString &color, int x, int y, const char *member);
    void drawBoardLabels();
    void initBoard();
    int makeIndex(int i, int j) { return i*8 + j; }
};

#endif // CHESSBOARD_H
