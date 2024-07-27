#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setFixedSize(551, 962);
    updateBackground();
    centerWindow();

    initUI();

    addRandomTile();
    addRandomTile();
    /*for (int i = 0; i < 16; ++i) {
        addRandomTile();
    }*/
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateBackground();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
        case Qt::Key_Up:
            moveUp();
            break;
        case Qt::Key_Down:
            moveDown();
            break;
        case Qt::Key_Left:
            moveLeft();
            break;
        case Qt::Key_Right:
            moveRight();
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
    board.resize(4);
    for (int row = 0; row < 4; ++row) {
        board[row].resize(4);
    }

    setWindowTitle("2048");
}

void MainWindow::addRandomTile()
{
    QVector<QPair<int, int>> emptyTiles;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] == nullptr) {
                emptyTiles.append(qMakePair(row, col));
            }
        }
    }

    if (!emptyTiles.isEmpty()) {
        int index = QRandomGenerator::global()->bounded(emptyTiles.size());
        QPair<int, int> position = emptyTiles[index];
        board[position.first][position.second] = new Tile(2, this);
        board[position.first][position.second]->show();
        board[position.first][position.second]->move(33 + position.second * 125, 322 + position.first * 125);
        //std::cout << index << std::endl;
        //std::cout << position.first << " , " << position.second << std::endl;
    }
}

void MainWindow::moveUp()
{
    bool needToAddTile = false;

    for (int row = 1; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] != nullptr) {
                int newRow = row;
                while (newRow > 0 && board[newRow - 1][col] == nullptr) {
                    newRow--;
                }
                if (newRow != 0 && board[row][col]->getValue() == board[newRow - 1][col]->getValue()) {
                    mergeTile(board[row][col], newRow - 1, col);
                    board[newRow - 1][col]->setValue(board[row][col]->getValue() * 2);
                    board[row][col] = nullptr;

                    needToAddTile = true;
                    continue;
                }
                else if (newRow != row) {
                    moveTile(board[row][col], newRow, col);
                    std::swap(board[newRow][col], board[row][col]);

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
            if (board[row][col] != nullptr) {
                int newRow = row;
                while (newRow < 3 && board[newRow + 1][col] == nullptr) {
                    newRow++;
                }
                if (newRow != 3 && board[row][col]->getValue() == board[newRow + 1][col]->getValue()) {
                    mergeTile(board[row][col], newRow + 1, col);
                    board[newRow + 1][col]->setValue(board[row][col]->getValue() * 2);
                    board[row][col] = nullptr;

                    needToAddTile = true;
                    continue;
                }
                else if (newRow != row) {
                    moveTile(board[row][col], newRow, col);
                    std::swap(board[newRow][col], board[row][col]);

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
            if (board[row][col] != nullptr) {
                int newCol = col;
                while(newCol > 0 && board[row][newCol - 1] == nullptr) {
                    newCol--;
                }
                if (newCol != 0 && board[row][col]->getValue() == board[row][newCol - 1]->getValue()) {
                    mergeTile(board[row][col], row, newCol - 1);
                    board[row][newCol - 1]->setValue(board[row][col]->getValue() * 2);
                    board[row][col] = nullptr;

                    needToAddTile = true;
                    continue;
                }
                else if (newCol != col) {
                    moveTile(board[row][col], row, newCol);
                    std::swap(board[row][newCol], board[row][col]);

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
            if (board[row][col] != nullptr) {
                int newCol = col;
                while (newCol < 3 && board[row][newCol + 1] == nullptr) {
                    newCol ++;
                }
                if (newCol != 3 && board[row][col]->getValue() == board[row][newCol + 1]->getValue()) {
                    mergeTile(board[row][col], row, newCol + 1);
                    board[row][newCol + 1]->setValue(board[row][col]->getValue() * 2);
                    board[row][col] = nullptr;

                    needToAddTile = true;
                    continue;
                }
                else if (newCol != col) {
                    moveTile(board[row][col], row, newCol);
                    std::swap(board[row][newCol], board[row][col]);

                    needToAddTile = true;
                }
            }
        }
    }

    if (needToAddTile) {
        addRandomTile();
    }
}

void MainWindow::moveTile(Tile *tile, int newRow, int newCol)
{
    // Перемещение плитки в новое положение
    QPoint newPos = QPoint(33 + newCol * 125, 322 + newRow * 125);
    QPropertyAnimation *animation = new QPropertyAnimation(tile, "pos");
    animation->setDuration(150);
    animation->setStartValue(tile->pos());
    animation->setEndValue(newPos);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::mergeTile(Tile *tile, int newRow, int newCol)
{
    // Перемещение плитки в новое положение с последующим слиянием
    QPoint newPos = QPoint(33 + newCol * 125, 322 + newRow * 125);
    QPropertyAnimation *animation = new QPropertyAnimation(tile, "pos");
    animation->setDuration(150);
    animation->setStartValue(tile->pos());
    animation->setEndValue(newPos);

    QObject::connect(animation, &QPropertyAnimation::stateChanged, [this, tile](QAbstractAnimation::State newState, QAbstractAnimation::State oldState) {
        this->onAnimationStateChanged(tile, newState, oldState);
    });

    animation->start(QAbstractAnimation::DeleteWhenStopped);

    /*QObject::connect(animation, &QPropertyAnimation::finished, [this, tile, needToDelete]() {
        if (needToDelete) {
            tile->deleteLater();
        }
        //addRandomTile();
    });*/
}

void MainWindow::onAnimationStateChanged(Tile* tile, QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if (oldState == QAbstractAnimation::Stopped && newState == QAbstractAnimation::Running) {
        tile->lower();
    }
    else if (oldState == QAbstractAnimation::Running && newState == QAbstractAnimation::Stopped) {
        tile->deleteLater();
    }
}
