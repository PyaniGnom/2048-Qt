#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QScreen>
#include <QKeyEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <iostream>
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

    void initUI();
    void addRandomTile();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    bool canCreateTile = false;
    QVector<QVector<Tile*>> board;
    void moveTile(Tile *tile, int newRow, int newCol);
    void mergeTile(Tile *tile, int newRow, int newCol);

private slots:
    void onAnimationStateChanged(Tile* tile, bool needToDelete, QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
};

#endif // MAINWINDOW_H
