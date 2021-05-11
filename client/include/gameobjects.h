#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <QToolButton>
#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QObject>
#include <QLabel>

class MyButton : public QToolButton
{
    Q_OBJECT
public:
    MyButton(const QString & text = "", QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

// imagelabel2.h

class ImageLabel2 : public QWidget
{
Q_OBJECT

public:
explicit ImageLabel2(QWidget *parent = 0);
const QPixmap* pixmap() const;

public slots:
void setPixmap(const QPixmap&);

protected:
void paintEvent(QPaintEvent *);

private:
QPixmap pix;
};

#endif // GAMEOBJECTS_H
