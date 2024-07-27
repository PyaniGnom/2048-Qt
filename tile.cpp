#include "tile.h"

Tile::Tile(int value, QWidget *parent) : QWidget(parent), m_value(value), m_animation(new QPropertyAnimation(this, "position"))
{
    setFixedSize(110, 110);
}

int Tile::getValue() const
{
    return m_value;
}

void Tile::setValue(int newValue)
{
    m_value = newValue;
}

bool Tile::isEmpty() const
{
    return m_value == 0;
}

QPoint Tile::position() const
{
    return m_position;
}

void Tile::setPosition(const QPoint &pos)
{
    m_position = pos;
    move(m_position);
}

void Tile::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect = this->rect();

    QColor color = getBackgroundForValue(m_value);  // Установка цвета фона плитки в зависимости от значения
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect, 6.5, 6.5);
    //painter.fillRect(rect, color);

    // Установка цвета и размера текста
    painter.setPen(getForegroundForValue(m_value));
    QFont font;
    font.setFamily("Open Sans");
    font.setPointSize(33);
    font.setWeight(70);
    font.setStyle(QFont::StyleNormal);
    painter.setFont(font);

    // Отрисовка значения в центре плитки
    painter.drawText(rect, Qt::AlignCenter, QString::number(m_value));
}

QColor Tile::getBackgroundForValue(int value)
{
    switch (value) {
        case 2: return QColor(238, 228, 218);
        case 4: return QColor(236, 224, 200);
        case 8: return QColor(242, 177, 121);
        case 16: return QColor(245, 149, 99);
        case 32: return QColor(245, 124, 95);
        case 64: return QColor(246, 93, 59);
        case 128: return QColor(237, 206, 113);
        case 256: return QColor(237, 204, 97);
        case 512: return QColor(236, 200, 80);
        case 1024: return QColor(237, 197, 63);
        case 2048: return QColor(238, 194, 46);
        default: return QColor(255, 0, 0);
    }
}

QColor Tile::getForegroundForValue(int value)
{
    switch (value) {
        case 2: return QColor(119, 110, 101);
        case 4: return QColor(119, 110, 101);
        case 8: return QColor(249, 246, 241);
        case 16: return QColor(249, 246, 241);
        case 32: return QColor(249, 246, 241);
        case 64: return QColor(249, 246, 241);
        case 128: return QColor(249, 246, 241);
        case 256: return QColor(249, 246, 241);
        case 512: return QColor(249, 246, 241);
        case 1024: return QColor(249, 246, 241);
        case 2048: return QColor(249, 246, 241);
        default: return QColor(255, 0, 0);
    }
}
