#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <QToolButton>
#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QPalette>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QCheckBox>
#include <memory>
#include <QGraphicsDropShadowEffect>

#include "community.h"

class MyButton : public QToolButton
{
    Q_OBJECT
public:
    MyButton(const QString & text = "", QWidget *parent = nullptr);

    QSize sizeHint() const override;
    void addStyle(QString newStyle);
private:
    QString style;
};

class FrameButton :  public QFrame
{
    Q_OBJECT
signals:
    void clicked();
public:
    FrameButton(QWidget *parent = nullptr, std::shared_ptr<Chat> chat = std::make_shared<Chat>());

    void mousePressEvent(QMouseEvent *event);
    std::shared_ptr<Chat> getChat() { return chat; }
    void setChat(std::shared_ptr<Chat> chat) { this->chat = chat; }
private:
    std::shared_ptr<Chat> chat;
};

class PhotoWidget : public QLabel
{
    Q_OBJECT
public:
    PhotoWidget(QPixmap photo, QSize size = QSize(50,50), QWidget *parent = nullptr);

    QSize sizeHint() const override;
private:
    QPixmap photo;
    QSize size;
};

class LabelImage: public QLabel {

  private:
    QPixmap _qPixmap, _qPixmapScaled;

  public:
    void setPixmap(const QPixmap &qPixmap) { setPixmap(qPixmap, size()); }

  public:
    void resizeLabel(QResizeEvent * event);
    void resizeEvent(QResizeEvent * event);
    QSize getSize() { return _size; }
    void setSize(QSize newSize) { _size = newSize; }

  private:
    void setPixmap(const QPixmap &qPixmap, const QSize &size);

    QSize _size;
};

class CheckBoxUser : public QCheckBox {
    Q_OBJECT
public:
    CheckBoxUser(QWidget *parent = nullptr, int index = 0) :QCheckBox(parent), index(index) {};
    int getIndex() { return index; }
    void setIndex(int index) { this->index = index; }
private:
    int index;
};


#endif // GAMEOBJECTS_H
