#include "include/figures.h"

King::King(QString color, QString path) :Figure(color, false)
{
    setImage(path);
}

void King::setImage(QString path)
{
   image.load(path != "" ? path : initialPath + (this->getColor() == "white" ? "w" : "b") + "K.png");
}

Bishop::Bishop(QString color, QString path) :Figure(color, false)
{
    setImage(path);
}

void Bishop::setImage(QString path)
{
    image.load(path != "" ? path : initialPath + (this->getColor() == "white" ? "w" : "b") + "B.png");
}

Rook::Rook(QString color, QString path) :Figure(color, false)
{
    setImage(path);
}

void Rook::setImage(QString path)
{
    image.load(path != "" ? path : initialPath + (this->getColor() == "white" ? "w" : "b") + "R.png");
}

Queen::Queen(QString color, QString path) :Figure(color, false)
{
    setImage(path);
}

void Queen::setImage(QString path)
{
    image.load(path != "" ? path : initialPath + (this->getColor() == "white" ? "w" : "b") + "Q.png");
}

Horse::Horse(QString color, QString path) :Figure(color, false)
{
    setImage(path);
}

void Horse::setImage(QString path)
{
    image.load(path != "" ? path : initialPath + (this->getColor() == "white" ? "w" : "b") + "N.png");
}

Pawn::Pawn(QString color, QString path) :Figure(color, false)
{
    setImage(path);
}

void Pawn::setImage(QString path)
{
    image.load(path != "" ? path : initialPath + (this->getColor() == "white" ? "w" : "b") + "P.png");
}
