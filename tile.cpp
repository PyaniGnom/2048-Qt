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
    QFont font("Open Sans", 33, 70, false);
    painter.setFont(font);

    // Отрисовка значения в центре плитки
    painter.drawText(rect, Qt::AlignCenter, QString::number(m_value));
}

QColor Tile::getBackgroundForValue(int value)
{
    switch (value) {
        case 2: return QColor("#eee4da");
        case 4: return QColor("#ece0c8");
        case 8: return QColor("#f2b179");
        case 16: return QColor("#f59563");
        case 32: return QColor("#f57c5f");
        case 64: return QColor("#f65d3b");
        case 128: return QColor("#edce71");
        case 256: return QColor("#edcc61");
        case 512: return QColor("#ecc850");
        case 1024: return QColor("#edc53f");
        case 2048: return QColor("#eec22e");
        default: return QColor(255, 0, 0);
    }
}

QColor Tile::getForegroundForValue(int value)
{
    switch (value) {
        case 2:
        case 4: return QColor("#776e65");
        case 8:
        case 16:
        case 32:
        case 64:
        case 128:
        case 256:
        case 512:
        case 1024:
        case 2048: return QColor("#f9f6f1");
        default: return QColor(255, 0, 0);
    }
}
