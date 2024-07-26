#include "tile.h"

Tile::Tile(int value) : m_value(value)
{

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

/*QColor Tile::getColorForValue(int value)
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
}*/
