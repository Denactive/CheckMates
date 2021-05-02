#include "include/cell.h"
#include <QDebug>

Cell::Cell(int nx, int ny, const QString &ncolor, Figure * figure, QWidget *parent)
    :QToolButton(parent), x(nx), y(ny), color(ncolor), figure(figure) {
    setText(ncolor);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    style = "";
    setStyle(ncolor, nx, ny);
    if (figure) setFigure(figure);
    this->setIconSize(this->sizeHint());
}

void Cell::setFigure(Figure * nfigure)
{
    if (nfigure != nullptr) {
        figure = nfigure;
        this->setIcon(nfigure->getImage());
    } else {
        figure = nullptr;
        this->setIcon(QIcon());
    }
}

bool Cell::isHasFigure()
{
    return figure != nullptr;
}

void Cell::cellClick(bool click)
{
    style = "";
    if (click) setStyle("red", x, y);
    else setStyle(color, x, y);
}


void Cell::setStyle(QString clr, int px, int py)
{
    if (clr == "white") style += "background-color: #ffb972; ";
    else if (clr == "black") style += "background: #58310C; ";
    else style += "background: " + clr + "; ";

    qDebug() << "x " << px << " y " << py;
    style += " border-left: 2px solid black; ";
    style += " border-top: 2px solid black; ";
    if (py == 7) style += " border-right: 2px solid black; ";
    if (px == 7) style += " border-bottom: 2px solid black; ";

    style += "color: transparent; \
              background-position: center;";

     setStyleSheet(style);
}

QString Cell::getStyle()
{
    return style;
}

QSize Cell::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    //size.rheight() += 20;
    //size.rwidth() = qMax(size.width(), size.height());
    //size.rwidth() += 20;
    size.rheight() = size.rwidth();
    return size;
}

