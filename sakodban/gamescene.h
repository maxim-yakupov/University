#pragma once

#include <QGraphicsScene>

#include "field.h"
#include "player.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene();
    ~GameScene();
signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *event);
private:
    Player* player;
    Field* field;
    int currentMap;
    bool onMenu;
    QPoint lastStep;
    bool boxMoved;

    void loadSave();
    void saveGame();
    void loadMap(int map);
    void startGame(int map);
    void menu();
    void help();
    void updatePlayerPos();
    void shiftField(int dx, int dy);
    void reset();
    void restart();
    void onLevelComplite();
    void chooseMap();
    void undo();
};
