#ifndef FIGURES_H
#define FIGURES_H
#include <QPixmap>
#include <QWidget>

class Figure : public QWidget {
private:
    QString color;
    bool isClick;
public:
    const QString initialPath = "../img/figures/tournament_metal/";

    Figure(QString ncolor = "", bool nisClick = false, QWidget * parent = nullptr)
        :QWidget(parent), color(ncolor), isClick(nisClick) {};

    QString getColor() { return color; }
    virtual void setImage(QString path) = 0;
    virtual QPixmap getImage() const = 0;
};

class King : public Figure {
private:
    QPixmap image;
    bool isUnderMat;
public:
    King(QString color = "", QString path = "");
    void setImage(QString path = "");
    QPixmap getImage() const { return image; }
};

class Bishop : public Figure {
private:
    QPixmap image;
public:
    Bishop(QString color = "", QString path = "");
    void setImage(QString path = "");
    QPixmap getImage() const { return image; }
};

class Rook : public Figure {
private:
    QPixmap image;
public:
    Rook(QString color = "", QString path = "");
    void setImage(QString path = "");
    QPixmap getImage() const { return image; }
};

class Queen : public Figure {
private:
    QPixmap image;
public:
    Queen(QString color = "", QString path = "");
    void setImage(QString path = "");
    QPixmap getImage() const { return image; }
};

class Horse : public Figure {
private:
    QPixmap image;
public:
    Horse(QString color = "", QString path = "");
    void setImage(QString path = "");
    QPixmap getImage() const { return image; }
};

class Pawn : public Figure {
private:
    QPixmap image;
public:
    Pawn(QString color = "", QString path = "");
    void setImage(QString path = "");
    QPixmap getImage() const { return image; }
};

#endif // FIGURES_H
