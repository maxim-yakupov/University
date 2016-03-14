#include "gamescene.h"

#include <QInputDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTextStream>

GameScene::GameScene()
{
    loadSave();
    startGame(currentMap);
    menu();
}

GameScene::~GameScene()
{
    saveGame();
    delete player;
    delete field;
}

// 0 - NONE
// 1 - WALL
// 2 - BUTTON
// 3 - BOX
void GameScene::loadMap(int map)
{
    int width = 10;
    int height = 10;
    int playerX = 3;
    int playerY = 5;
    int** data;
    QFile file("./maps/" + QString::number(map) + ".txt");
    if (file.open(QIODevice::ReadOnly))
    {
        width = QString(file.readLine()).toInt();
        height = QString(file.readLine()).toInt();
        data = new int*[height];
        for (int i = 0; i < height; i++)
        {
            data[i] = new int[width];
            QString t(file.readLine());
            for (int j = 0; j < width; j++)
            {
                data[i][j] = (int) (t[j].toLatin1() - '0');
            }
        }
        playerX = QString(file.readLine()).toInt();
        playerY = QString(file.readLine()).toInt();
        file.close();
    }
    else
    {
        int data0[10][10] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 3, 2, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        };
        data = new int*[height];
        for (int i = 0; i < height; i++)
        {
            data[i] = new int[width];
            for (int j = 0; j < width; j++)
            {
                data[i][j] = data0[i][j];
            }
        }
    }

    field = new Field(0, width, height);
    for (int y = 0; y < field->getHeight(); y++)
    {
        for (int x = 0; x < field->getWidth(); x++)
        {
            field->getTile(x, y)->setType(
                        static_cast<Tile::TileType>(data[y][x] % 3)
                        );
            if (data[y][x] == 3)
            {
                field->getTile(x, y)->putBox();
            }
            else if (data[y][x] == 2)
            {
                field->lookAfter(field->getTile(x, y));
            }
        }
    }
    player = new Player(field, playerX, playerY);
    for (int i = 0; i < height; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}

void GameScene::updatePlayerPos()
{
    player->setPos(
                field
                ->getTile(player->getX(),
                          player->getY())
                ->pos()
                );
}

void GameScene::shiftField(int dx, int dy)
{
    field->setPos(field->pos() + QPointF(- dx * GameParams::tileSize, - dy * GameParams::tileSize));
}

void GameScene::reset()
{
    delete player;
    delete field;
    clear();
}

void GameScene::restart()
{
    reset();
    startGame(currentMap);
}

void GameScene::onLevelComplite()
{
    QMessageBox congratBox;
    congratBox.setWindowTitle("Victory!");
    congratBox.setText("Congratulations!\nYou completed map " + QString::number(currentMap));
    congratBox.exec();
}

void GameScene::chooseMap()
{
    bool mapChoosen = false;
    int map = QInputDialog::getInt(0,
                                   "Choose map",
                                   "Enter number of map:",
                                   1, 0, 20000, 1,
                                   &mapChoosen);
    if (mapChoosen)
    {
        reset();
        startGame(map);
        currentMap = map;
    }
}

void GameScene::undo()
{
    int x = player->getX();
    int y = player->getY();
    player->setX(x - lastStep.x());
    player->setY(y - lastStep.y());
    updatePlayerPos();
    shiftField(- lastStep.x(), - lastStep.y());
    if (boxMoved)
    {
        field->getTile(x, y)->putBox();
        field->getTile(x + lastStep.x(), y + lastStep.y())->removeBox();
    }
    lastStep = QPoint(0, 0);
    boxMoved = false;
}

void GameScene::startGame(int map)
{
    clear();

    loadMap(map);

    lastStep = QPoint(0, 0);
    boxMoved = false;

    setBackgroundBrush(QBrush(QColor(128,128,128)));
    field->setPos(0, 0);
    updatePlayerPos();
    addItem(field);
}

void GameScene::menu()
{
    onMenu = true;
    field->hide();
    bool selected = false;
    int selection = QInputDialog::getInt(0,
                                   "Menu",
                                   "Current map: " + QString::number(currentMap) + "\n\n"
                                   "0. Continue\n"
                                   "1. Help\n"
                                   "2. Restart map\n"
                                   "3. Choose map",
                                   0, 0, 3, 1,
                                   &selected);
    if (selected)
    {
        switch (selection) {
        case 0:
            break;
        case 1:
            help();
            break;
        case 2:
            restart();
            break;
        case 3:
            chooseMap();
            break;
        default:
            break;
        }
    }
    field->show();
    onMenu = false;
}

void GameScene::help()
{
    QMessageBox helpBox;
    helpBox.setWindowTitle("Help");
    helpBox.setText("arrows - movement\n"
                    "WASD - camera movement\n[do not forget enable latin keyboard]\n\n"
                    "stand close to push box\n"
                    "you can push ONLY ONE box in a row\n\n"
                    "F1 - this help\n\n"
                    "BackSpace - undo last move (only one)\n\n"
                    "F5 - restart this map\n\n"
                    "Esc - show menu");
    helpBox.exec();
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if (onMenu) return;
    int dx = 0;
    int dy = 0;
    switch (event->key())
    {
        case Qt::Key_Left:
            dx = -1;
            player->setDirection(Player::LEFT);
            break;
        case Qt::Key_Right:
            dx = 1;
            player->setDirection(Player::RIGHT);
            break;
        case Qt::Key_Up:
            dy = -1;
            player->setDirection(Player::UP);
            break;
        case Qt::Key_Down:
            dy = 1;
            player->setDirection(Player::DOWN);
            break;
        case Qt::Key_A:
            shiftField(-1, 0);
            break;
        case Qt::Key_D:
            shiftField(1, 0);
            break;
        case Qt::Key_W:
            shiftField(0, -1);
            break;
        case Qt::Key_S:
            shiftField(0, 1);
            break;
        case Qt::Key_F1:
            help();
            break;
        case Qt::Key_Backspace:
            undo();
            break;
        case Qt::Key_F5:
            restart();
            break;
        case Qt::Key_Escape:
            menu();
            break;
        default:
            break;
    }
    if (dx || dy)
    {
        int x = player->getX();
        int y = player->getY();
        if (field->isWalkable(x + dx, y + dy))
        {
            player->setX(x + dx);
            player->setY(y + dy);
            updatePlayerPos();
            shiftField(dx, dy);
            lastStep = QPoint(dx, dy);
            boxMoved = false;
        }
        else if (field->getTile(x + dx, y + dy)->isBoxOn())
        {
            if (field->isWalkable(x + 2 * dx, y + 2 * dy))
            {
                field->getTile(x + 2 * dx, y + 2 * dy)->putBox();
                field->getTile(x + dx, y + dy)->removeBox();
                player->setX(x + dx);
                player->setY(y + dy);
                updatePlayerPos();
                shiftField(dx, dy);
                lastStep = QPoint(dx, dy);
                boxMoved = true;
            }
        }
        player->setDirection(Player::STAY);
        if (field->checkWin())
        {
            onLevelComplite();
            reset();
            startGame(currentMap + 1);
            currentMap++;
        }
    }
}

void GameScene::loadSave()
{
    QFile file("./save.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        currentMap = QString(file.readLine()).toInt();
        file.close();
    }
    else
    {
        currentMap = 0;
    }
}

void GameScene::saveGame()
{
    QFile file("./save.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << currentMap << "\r\n";
        file.close();
    }
}
