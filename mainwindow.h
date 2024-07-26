#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tile.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void updateBackground();
    void centerWindow();

    enum class Direction {
        Up,
        Down,
        Left,
        Right
    };

    QVector<QVector<Tile>> tiles;

    void initUI();
    void addRandomTile();
    void drawGrid(QPainter &painter);
    void drawTiles(QPainter &painter);
    void moveTiles(Direction direction);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    /*QWidget *boardWidget;
    QVector<Tile*> tiles;

    int gridSize = 4;       // Размер сетки 4x4
    int tileSpacing = 15;   // Промежуток между плитками
    int margin = 20;        // Отступы от краёв окна
    int boardSize = 485;    // Размер поля для плиток

    void initializeBoard();
    void moveTile(Tile *tile, int newRow, int newCol);
    void moveLeft();
    QPoint getTilePosition(int row, int col);*/
};

#endif // MAINWINDOW_H
