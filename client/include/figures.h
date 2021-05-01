#ifndef FIGURES_H
#define FIGURES_H
#include <QPixmap>
#include <QWidget>

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

class King : public QWidget {
private:
    QPixmap image;
    bool isUnderMat;
public:
    King(QPixmap pixmap, QWidget * parent = nullptr);
    void setImage(QPixmap image);
    bool move();
};

class Bishop : public QWidget, public Figure {
private:
    QPixmap image;
public:
    void setImage(QPixmap image, QWidget * parent = nullptr);
    bool move();
};

class Rook : public QWidget, public Figure {
private:
    QPixmap image;
public:
    void setImage(QPixmap image);
    bool move();
};

class Queen : public QWidget, public Figure {
private:
    QPixmap image;
public:
    void setImage(QPixmap image);
    bool move();
};

class Horse : public QWidget, public Figure {
private:
    QPixmap image;
public:
    void setImage(QPixmap image);
    bool move();
};

class Pawn : public QWidget, public Figure {
private:
    QPixmap image;
public:
    void setImage(QPixmap image);
    bool move();
    bool endWay();
};

#endif // FIGURES_H
