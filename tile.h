#ifndef TILE_H
#define TILE_H

class Tile {
public:
    Tile(int value = 0);

    int getValue() const;
    void setValue(int newValue);
    bool isEmpty() const;

private:
    int m_value;
};

#endif // TILE_H
