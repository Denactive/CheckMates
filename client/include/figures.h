#ifndef FIGURES_H
#define FIGURES_H
#include <QPixmap>

class Figure {
private:
    std::string color;
    bool isDead;
public:
    Figure(std::string n_color = "white", bool n_isDead = false) :color(n_color), isDead(n_isDead) {};
    void setColor(std::string color);
    std::string getColor();
    void setImage(std::string);
    bool move();
};

class King {
private:
    QPixmap image;
    bool isUnderMat;
public:
    void setImage(QPixmap image);
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
