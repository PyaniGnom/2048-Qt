#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), gameOverview(nullptr)
{
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    setFixedSize(551, 962);
    updateBackground();
    centerWindow();

    initUI();
    StartNewGame();
}

MainWindow::~MainWindow()
{
    for (auto& row : board) {
        for (Tile* tile : row) {
            delete tile;
        }
        row.clear();
    }
    board.clear();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateBackground();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (gameOverview) {
        return;
    }

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
    setWindowTitle("2048");

    board.resize(4);
    for (int row = 0; row < 4; ++row) {
        board[row].resize(4);
    }

    restartButton = new QPushButton(this);
    restartButton->setFixedSize(QSize(55, 55));
    restartButton->move(QPoint(478, 236));
    restartButton->setStyleSheet(
        "QPushButton {"
        "   border: none;"
        "   border-radius: 16px;"
        "}"
    );
    restartButton->setFocusPolicy(Qt::NoFocus);
    restartButton->show();

    QObject::connect(restartButton, &QPushButton::clicked, this, &MainWindow::onRestartGame);
}

void MainWindow::StartNewGame()
{
    QIcon icon(":/images/restartIcon");
    restartButton->setIcon(icon);
    restartButton->setIconSize(QSize(55, 55));

    if (gameOverview) {
        gameOverview->deleteLater();
        gameOverview = nullptr;
    }

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] != nullptr) {
                board[row][col]->deleteLater();
                board[row][col] = nullptr;
            }
        }
    }

    addRandomTile();
    addRandomTile();
}

void MainWindow::addRandomTile()
{
    ReloadEmptyTilesVec();

    if (!emptyTiles.isEmpty()) {
        int index = QRandomGenerator::global()->bounded(emptyTiles.size());
        QPair<int, int> position = emptyTiles[index];
        board[position.first][position.second] = new Tile(2, this);
        board[position.first][position.second]->show();
        board[position.first][position.second]->lower();
        board[position.first][position.second]->move(33 + position.second * 125, 322 + position.first * 125);
    }
}

void MainWindow::moveUp()
{
    for (int row = 1; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] != nullptr) {
                int newRow = row;
                while (newRow > 0 && board[newRow - 1][col] == nullptr) {
                    newRow--;
                }
                if (newRow != 0 && board[row][col]->getValue() == board[newRow - 1][col]->getValue()) {
                    moveTile(board[row][col], true, newRow - 1, col);
                    board[newRow - 1][col]->setValue(board[row][col]->getValue() * 2);
                    board[row][col] = nullptr;

                    continue;
                }
                else if (newRow != row) {
                    moveTile(board[row][col], false, newRow, col);
                    std::swap(board[newRow][col], board[row][col]);
                }
            }
        }
    }

    canCreateTile = true;
}

void MainWindow::moveDown()
{
    for (int row = 2; row >= 0; --row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] != nullptr) {
                int newRow = row;
                while (newRow < 3 && board[newRow + 1][col] == nullptr) {
                    newRow++;
                }
                if (newRow != 3 && board[row][col]->getValue() == board[newRow + 1][col]->getValue()) {
                    moveTile(board[row][col], true, newRow + 1, col);
                    board[newRow + 1][col]->setValue(board[row][col]->getValue() * 2);
                    board[row][col] = nullptr;

                    continue;
                }
                else if (newRow != row) {
                    moveTile(board[row][col], false, newRow, col);
                    std::swap(board[newRow][col], board[row][col]);
                }
            }
        }
    }

    canCreateTile = true;
}

void MainWindow::moveLeft()
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 1; col < 4; ++col) {
            if (board[row][col] != nullptr) {
                int newCol = col;
                while(newCol > 0 && board[row][newCol - 1] == nullptr) {
                    newCol--;
                }
                if (newCol != 0 && board[row][col]->getValue() == board[row][newCol - 1]->getValue()) {
                    moveTile(board[row][col], true, row, newCol - 1);
                    board[row][newCol - 1]->setValue(board[row][col]->getValue() * 2);
                    board[row][col] = nullptr;

                    continue;
                }
                else if (newCol != col) {
                    moveTile(board[row][col], false, row, newCol);
                    std::swap(board[row][newCol], board[row][col]);
                }
            }
        }
    }

    canCreateTile = true;
}

void MainWindow::moveRight()
{
    for (int row = 0; row < 4; ++row) {
        for (int col = 2; col >= 0; --col) {
            if (board[row][col] != nullptr) {
                int newCol = col;
                while (newCol < 3 && board[row][newCol + 1] == nullptr) {
                    newCol ++;
                }
                if (newCol != 3 && board[row][col]->getValue() == board[row][newCol + 1]->getValue()) {
                    moveTile(board[row][col], true, row, newCol);
                    board[row][newCol + 1]->setValue(board[row][col]->getValue() * 2);
                    board[row][col] = nullptr;

                    continue;
                }
                else if (newCol != col) {
                    moveTile(board[row][col], false, row, newCol);
                    std::swap(board[row][newCol], board[row][col]);
                }
            }
        }
    }

    canCreateTile = true;
}

void MainWindow::moveTile(Tile *tile, bool isMerge, int newRow, int newCol)
{
    QPoint newPos = QPoint(33 + newCol * 125, 322 + newRow * 125);
    QPropertyAnimation *animation = new QPropertyAnimation(tile, "pos");
    animation->setDuration(120);
    animation->setStartValue(tile->pos());
    animation->setEndValue(newPos);

    QObject::connect(animation, &QPropertyAnimation::stateChanged, [this, tile, isMerge](QAbstractAnimation::State newState, QAbstractAnimation::State oldState) {
        this->onAnimationStateChanged(tile, isMerge, newState, oldState);
    });

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::ReloadEmptyTilesVec()
{
    emptyTiles.clear();
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (board[row][col] == nullptr) {
                emptyTiles.append(qMakePair(row, col));
            }
        }
    }
}

bool MainWindow::IsBoardFill()
{
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            // Проверяем соседа сверху, если это не первый ряд
            if (row > 0 && board[row][col]->getValue() == board[row - 1][col]->getValue()) {
                return false;
            }
            // Проверяем соседа снизу, если это не последний ряд
            if (row < boardSize - 1 && board[row][col]->getValue() == board[row + 1][col]->getValue()) {
                return false;
            }
            // Проверяем соседа слева, если это не первый столбец
            if (col > 0 && board[row][col]->getValue() == board[row][col - 1]->getValue()) {
                return false;
            }
            // Проверяем соседа справа, если это не последний столбец
            if (col < boardSize - 1 && board[row][col]->getValue() == board[row][col + 1]->getValue()) {
                return false;
            }
        }
    }

    return true; // Ни один элемент не имеет равного соседа
}

void MainWindow::onAnimationStateChanged(Tile* tile, bool isMerge, QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if (oldState == QAbstractAnimation::Stopped && newState == QAbstractAnimation::Running) {
        tile->lower();
    }
    else if (oldState == QAbstractAnimation::Running && newState == QAbstractAnimation::Stopped) {
        if (isMerge) {
            tile->deleteLater();
            if (tile->getValue() * 2 == 2048) {
                emit onGameWin();
            }
        }
        if (canCreateTile) {
            addRandomTile();
            canCreateTile = false;
            ReloadEmptyTilesVec();
            if (emptyTiles.isEmpty()) {
                if (IsBoardFill()) {
                    emit onGameOver();
                }
            }
        }
    }
}

void MainWindow::onRestartGame()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Сбросить игру?");
    msgBox.setText("Вы уверены, что хотите начать сначала?");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Reset);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    msgBox.button(QMessageBox::Cancel)->setText("ОТМЕНА");
    msgBox.button(QMessageBox::Reset)->setText("СБРОС");

    msgBox.setStyleSheet(
        "QMessageBox {"
        "   background-color: #ffffff;"     // Цвет фона окна
        "   border: 0px;"   // Граница окна
        "}"
        "QMessageBox QLabel {"
        "   min-width: 342px;"  // получается 385 на 177 px
        "   min-height: 77px;"
        "   color: #202020;"    // Цвет текста
        "   font: normal normal 17px \"Open Sans\";"   // Размер шрифта текста
        "   text-align: center;"
        "}"
        "QMessageBox QPushButton {"
        "   background-color: #ffffff;"     // Цвет фона кнопок
        "   font: normal bold 15px \"Open Sans\";"
        "   color: #008578;"
        "   border: 1px solid #8f8f8f;"     // Граница кнопок
        "   min-width: 94px;"       // Минимальная ширина кнопок
        "   min-height: 35px;"      // Минимальная высота кнопок
        "}"
        "QMessageBox QPushButton:pressed {"
        "   background-color: #e5e5e5;"     // Фон при нажатии
        "}"
    );

    if (msgBox.exec() == QMessageBox::Reset) {
        StartNewGame();
    }
}

void MainWindow::onGameOver()
{
    QIcon icon(":/images/restartIcon-Active");
    restartButton->setIcon(icon);
    restartButton->setIconSize(QSize(55, 55));

    if (!gameOverview) {
        gameOverview = new GameOverviewWidget(this);
        gameOverview->setFillColor(QColor(199, 187, 177, 255 * 0.5));
        gameOverview->setTextColor(QColor(120, 110, 101));
        gameOverview->setGeometry(18, 307, 515, 515);
        gameOverview->setText("Игра окончена!");
        gameOverview->setVisible(true);
    }
}

void MainWindow::onGameWin()
{
    QIcon icon(":/images/restartIcon-Active");
    restartButton->setIcon(icon);
    restartButton->setIconSize(QSize(55, 55));

    if (!gameOverview) {
        gameOverview = new GameOverviewWidget(this);
        gameOverview->setFillColor(QColor(237, 206, 115, 255 * 0.5));
        gameOverview->setTextColor(QColor(250, 246, 243));
        gameOverview->setGeometry(18, 307, 515, 515);
        gameOverview->setText("Вы победили!");
        gameOverview->setVisible(true);
    }
}
