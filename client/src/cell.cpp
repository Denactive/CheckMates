#include "include/cell.h"

Cell::Cell(int nx, int ny, const QString &ncolor, bool nhasFigure, Figure *nfigure, King * king, QWidget *parent)
    :QToolButton(parent), x(nx), y(ny), color(ncolor), hasFigure(nhasFigure), figure(nfigure), king(king) {
    setText(ncolor);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QString style = "";
    if (ncolor == "white") style += "background-color: #ffb972;";
    if (ncolor == "black") style += "background: #58310C;";

    style += "border-image: url(../img/figures/tournament_metal/wN.png) 2 no-repeat; \
                    color: transparent; \
                    background-position: center; \
                    border: 1px solid black;\
                    ";

     setStyleSheet(style);
}

void Cell::setFigure(Figure * nfigure)
{
    figure = nfigure;
    hasFigure = true;
}

bool Cell::isHasFigure()
{
    return hasFigure == true;
}

void Cell::setKing(King *king)
{
    this->king = king;
}

King *Cell::getKing()
{
    if (isHasKing()) return king;
    else return nullptr;
}

bool Cell::isHasKing()
{
    return king == nullptr ? false : true;
}

void Cell::setColor(QString ncolor)
{
    color = ncolor;
}

QString Cell::getColor()
{
    return color;
}

QSize Cell::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 30;
    //size.rwidth() = qMax(size.width(), size.height());
    size.rwidth() += 30;
    return size;
}

