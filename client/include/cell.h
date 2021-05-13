#ifndef CELL_H
#define CELL_H
#include <QAbstractListModel>
#include <string>
#include <QToolButton>
#include <QSize>
#include <QGridLayout>
#include <QWidget>
#include <QFrame>
#include <QResizeEvent>


#include "include/figures.h"

class Cell : public QToolButton {
    Q_OBJECT
private:
    int x;
    int y;
    QString style;
    QString color;
    Figure *figure;
public:
    Cell(int nx = 0, int ny = 0, const QString & ncolor = "white", Figure * figure = nullptr,
         QWidget *parent = nullptr);
    size_t value {};

    void setFigure(Figure * figure = nullptr);
    Figure * getFigure() { return figure; }
    bool isHasFigure();
    void cellClick(bool click);

    void setStyle(QString clr = "white", int px = 0, int py = 0);
    QString getStyle();
    QSize sizeHint() const;
    void resizeEvent(QResizeEvent * event);

    QPair<int, int> getPosition() { return qMakePair(x, y); }
};
#endif // CELL_H
