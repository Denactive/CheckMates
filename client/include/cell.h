#ifndef CELL_H
#define CELL_H
#include <QAbstractListModel>
#include <string>
#include <QToolButton>
#include <QSize>
#include <QGridLayout>
#include <QWidget>
#include <QFrame>

#include "include/figures.h"

class Cell : public QToolButton {
    Q_OBJECT
private:
    int x;
    int y;
    QString color;
    bool hasFigure;
    Figure *figure;
    King * king;
public:
    Cell(int nx = 0, int ny = 0, const QString & ncolor = "white", bool nhasFigure = false, Figure * nfigure = nullptr, King * king = nullptr,
         QWidget *parent = nullptr);
    size_t value {};

    void setFigure(Figure * figure);
    Figure * getFigure();
    bool isHasFigure();

    void setKing(King * king);
    King * getKing();
    bool isHasKing();

    void setColor(QString ncolor);
    QString getColor();
    QSize sizeHint() const;
};
#endif // CELL_H
