#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#define DEBUGCHESS 0

#include <QAbstractListModel>
#include <string>
#include <QToolButton>
#include <QSize>
#include <QGridLayout>
#include <QWidget>
#include <QFrame>
#include <QStackedWidget>
#include <QMessageBox>

#include "include/cell.h"
#include "include/figures.h"
#include "include/database.h"
#include "include/graphics.h"

class IChessBoard {
    virtual void arrangeFigures(bool isWhite) = 0;
    virtual int getSize() const = 0;
    virtual void isKingUnderMat() = 0;
};

class ChessBoard : public QWidget,  public IChessBoard
{
    Q_OBJECT
public:
    ChessBoard(QStackedWidget * main = nullptr, std::shared_ptr<GameInfo> gameInfo = std::make_shared<GameInfo>(),
               int newSize = 0, GlobalNet * globalNet = nullptr, QWidget * parent = nullptr);
    void arrangeFigures(bool isWhite) override;;
    int getSize() const override { return size; }
    void setSize(int newSize) { size = newSize; }
    void isKingUnderMat() override;
    QSize sizeHint() const;

private slots:
    void cellClicked();

private:
    QStackedWidget * main;
    QGridLayout *mainLayout;
    Cell* m_cells[64];
    Cell *clickCell;
    int size;

    std::shared_ptr<GameInfo> gameInfo;
    int kingPos;

    GlobalNet * globalNet;

    Cell* createCell(const QString &color, int x, int y, const char *member);
    void drawBoardLabels();
    void initBoard();
    int makeIndex(int i, int j) { return i*8 + j; }
};

#endif // CHESSBOARD_H
