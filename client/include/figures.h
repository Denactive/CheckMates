#ifndef FIGURES_H
#define FIGURES_H
#include "graphics.h"

class Figure {
private:
    std::string color;
    bool isDead;
public:
    void setColor(std::string color);
    std::string getColor();
    void setImage(std::string);
    bool move();
};

class Bishop : public Figure {
private:
    QPixmap image;
public:
    void setImage(QPixmap image);
    bool move();
};

class Rook : public Figure {
private:
    QPixmap image;
public:
    void setImage(QPixmap image);
    bool move();
};

class Queen : public Figure {
private:
    QPixmap image;
public:
    void setImage(QPixmap image);
    bool move();
};

class King : public Figure {
private:
    QPixmap image;
public:
    void setImage(QPixmap image);
    bool move();
    bool underMat();
};

class Horse : public Figure {
private:
    QPixmap image;
public:
    void setImage(QPixmap image);
    bool move();
};

class Pawn : public Figure {
private:
    QPixmap image;
public:
    void setImage(QPixmap image);
    bool move();
    bool endWay();
};

#endif // FIGURES_H
