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
    virtual int getSize() const = 0;
    virtual void isKingUnderMat() = 0;
};

class ChessBoard : public QWidget,  public IChessBoard
{
    Q_OBJECT
public:
    ChessBoard(bool kingUnderMat = true, bool isPlayer = true, int newSize = 0, QWidget * parent = nullptr);
    void arrangeFigures() override;;
    int getSize() const override { return size; }
    void setSize(int newSize) { size = newSize; }
    void isKingUnderMat() override;
    QSize sizeHint() const;

private slots:
    void cellClicked();

private:
    QGridLayout *mainLayout;
    Cell* m_cells[64];
    Cell *clickCell;
    int size;

    bool isPlayer; // true - you, false - friend
    bool kingUnderMat;
    int kingPos;

    Cell* createCell(const QString &color, int x, int y, const char *member);
    void drawBoardLabels();
    void initBoard();
    int makeIndex(int i, int j) { return i*8 + j; }
};

#endif // CHESSBOARD_H
