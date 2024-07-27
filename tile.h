#ifndef TILE_H
#define TILE_H

#include <QWidget>
#include <QPropertyAnimation>

class Tile : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPoint position READ position WRITE setPosition)

public:
    Tile(int value, QWidget *parent = nullptr);

    int getValue() const;
    void setValue(int newValue);
    bool isEmpty() const;

    QPoint position() const;
    void setPosition(const QPoint &pos);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_value;
    QPoint m_position;
    QPropertyAnimation *m_animation;
    QColor getBackgroundForValue(int value);
    QColor getForegroundForValue(int value);
};

#endif // TILE_H
