#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
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
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    QGridLayout *gridLayout;
    QWidget *tilesField;

    QVector<QVector<Tile*>> board;
    void moveTile(Tile *tile, int newRow, int newCol);
    void mergeTile(Tile *tile, int newRow, int newCol);

private slots:
    void onAnimationStateChanged(Tile* tile, QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
};

#endif // MAINWINDOW_H
