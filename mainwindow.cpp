#include "mainwindow.h"
#include <QApplication>
#include <QScreen>
#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>
//ахахахахахах ты это не увидешь, лошок
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setFixedSize(551, 962);
    updateBackground();
    centerWindow();

    initUI();
    addRandomTile();
    addRandomTile();
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateBackground();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //drawGrid(painter);
    drawTiles(painter);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
        case Qt::Key_Up:
            moveTiles(Direction::Up);
            break;
        case Qt::Key_Down:
            moveTiles(Direction::Down);
            break;
        case Qt::Key_Left:
            moveTiles(Direction::Left);
            break;
        case Qt::Key_Right:
            moveTiles(Direction::Right);
            break;
    }

    // Обновление интерфейса после каждого хода
    update();
}

void MainWindow::updateBackground()
{
    QPixmap background(":/images/background");
    background = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(background));
    setPalette(palette);
}

void MainWindow::centerWindow()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();

    int x = (screenWidth - width()) / 2;

    move(x, 25);
}

void MainWindow::initUI()
{
    tiles.resize(4);
    for (int row = 0; row < 4; ++row) {
        tiles[row].resize(4);
    }

    setWindowTitle("2048");
}

void MainWindow::addRandomTile()
{
    QVector<QPair<int, int>> emptyTiles;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (tiles[row][col].isEmpty()) {
                emptyTiles.append(qMakePair(row, col));
            }
        }
    }

    if (!emptyTiles.isEmpty()) {
        int index = QRandomGenerator::global()->bounded(emptyTiles.size());
        QPair<int, int> position = emptyTiles[index];
        tiles[position.first][position.second].setValue(2);
    }
}

void MainWindow::drawGrid(QPainter &painter)
{
    painter.setPen(Qt::black);
    for (int row = 0; row <= 4; ++row) {
        painter.drawLine(0, row * 100, 400, row * 100);
    }
    for (int col = 0; col <= 4; ++col) {
        painter.drawLine(col * 100 , 0, col * 100, 400);
    }
}

void MainWindow::drawTiles(QPainter &painter)
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (!tiles[row][col].isEmpty()) {
                painter.setBrush(Qt::lightGray);
                painter.drawRect(col * 100, row * 100, 100, 100);
                painter.setPen(Qt::black);
                painter.drawText(col * 100, row * 100, 100, 100, Qt::AlignCenter, QString::number(tiles[row][col].getValue()));
            }
        }
    }
}

void MainWindow::moveTiles(Direction direction)
{
    switch (direction) {
        case Direction::Up:
            moveUp();
            break;
        case Direction::Down:
            moveDown();
            break;
        case Direction::Left:
            moveLeft();
            break;
        case Direction::Right:
            moveRight();
            break;
    }
}

void MainWindow::moveUp()
{
    bool needToAddTile = false;

    for (int row = 1; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (!tiles[row][col].isEmpty()) {
                int newRow = row;
                // поиск новой свободной строки для плитки
                while (newRow > 0 && tiles[newRow - 1][col].isEmpty()) {
                    newRow--;
                }
                // слияние плиток, если возможно
                if (newRow != 0 && tiles[row][col].getValue() == tiles[newRow - 1][col].getValue()) {
                    tiles[newRow - 1][col].setValue(tiles[row][col].getValue() * 2);
                    tiles[row][col].setValue(0);
                    needToAddTile = true;
                    continue;
                }
                if (newRow != row) {
                    tiles[newRow][col].setValue(tiles[row][col].getValue());
                    tiles[row][col].setValue(0);
                    needToAddTile = true;
                }
            }
        }
    }

    if (needToAddTile) {
        addRandomTile();
    }
}

void MainWindow::moveDown()
{
    bool needToAddTile = false;

    for (int row = 2; row >= 0; --row) {
        for (int col = 0; col < 4; ++col) {
            if (!tiles[row][col].isEmpty()) {
                int newRow = row;
                while (newRow < 3 && tiles[newRow + 1][col].isEmpty()) {
                    newRow++;
                }
                if (newRow != 3 && tiles[row][col].getValue() == tiles[newRow + 1][col].getValue()) {
                    tiles[newRow + 1][col].setValue(tiles[row][col].getValue() * 2);
                    tiles[row][col].setValue(0);
                    needToAddTile = true;
                    continue;
                }
                if (newRow != row) {
                    tiles[newRow][col].setValue(tiles[row][col].getValue());
                    tiles[row][col].setValue(0);
                    needToAddTile = true;
                }
            }
        }
    }

    if (needToAddTile) {
        addRandomTile();
    }
}

void MainWindow::moveLeft()
{
    bool needToAddTile = false;

    for (int row = 0; row < 4; ++row) {
        for (int col = 1; col < 4; ++col) {
            if (!tiles[row][col].isEmpty()) {
                int newCol = col;
                while (newCol > 0 && tiles[row][newCol - 1].isEmpty()) {
                    newCol--;
                }
                if (newCol != 0 && tiles[row][col].getValue() == tiles[row][newCol - 1].getValue()) {
                    tiles[row][newCol - 1].setValue(tiles[row][col].getValue() * 2);
                    tiles[row][col].setValue(0);
                    needToAddTile = true;
                    continue;
                }
                if (newCol != col) {
                    tiles[row][newCol].setValue(tiles[row][col].getValue());
                    tiles[row][col].setValue(0);
                    needToAddTile = true;
                }
            }
        }
    }

    if (needToAddTile) {
        addRandomTile();
    }
}

void MainWindow::moveRight()
{
    bool needToAddTile = false;

    for (int row = 0; row < 4; ++row) {
        for (int col = 2; col >= 0; --col) {
            if (!tiles[row][col].isEmpty()) {
                int newCol = col;
                while (newCol < 3 && tiles[row][newCol + 1].isEmpty()) {
                    newCol++;
                }
                if (newCol != 3 && tiles[row][col].getValue() == tiles[row][newCol + 1].getValue()) {
                    tiles[row][newCol + 1].setValue(tiles[row][col].getValue() * 2);
                    tiles[row][col].setValue(0);
                    needToAddTile = true;
                    continue;
                }
                if (newCol != col) {
                    tiles[row][newCol].setValue(tiles[row][col].getValue());
                    tiles[row][col].setValue(0);
                    needToAddTile = true;
                }
            }
        }
    }

    if (needToAddTile) {
        addRandomTile();
    }
}
