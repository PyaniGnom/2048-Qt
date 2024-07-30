#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QScreen>
#include <QKeyEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QPushButton>
#include <QMessageBox>
//#include <iostream>
#include "tile.h"
#include "gameoverviewwidget.h"

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

    void initUI();
    void StartNewGame();
    void addRandomTile();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveTile(Tile *tile, bool isMerge, int newRow, int newCol);
    void ReloadEmptyTilesVec();

    bool BoardIsFill();

    const int boardSize = 4;
    bool canCreateTile = false;
    QVector<QPair<int, int>> emptyTiles;
    QVector<QVector<Tile*>> board;
    QPushButton *restartButton;
    GameOverviewWidget *gameOverview;

private slots:
    void onAnimationStateChanged(Tile* tile, bool needToDelete, QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
    void onRestartGame();
    void onGameOver();
};

#endif // MAINWINDOW_H
