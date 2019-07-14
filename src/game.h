#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <time.h>
#include <QMessageBox>
#include <QPainter>
#include <QKeyEvent>

const int BLOCK_SIZE = 25;
const int MARGIN     = 5 ;
const int AREA_ROW   = 20;
const int AREA_COL   = 12;
const int FONT_SIZE  = 10;

//direction
enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE
};

struct Border
{
    int ubound;
    int dbound;
    int lbound;
    int rbound;
};

struct block_point
{
    int pos_x;
    int pos_y;
};

enum GameState
{
    FreeRun = 1,
    Wait = 2,
    Game_Over = 3
};

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    void InitGame();
    void StartGame();
    void GameOver();

    void ResetBlock();
    void BlockMove(Direction dir);
    void BlockRotate(int block[4][4]);
    void CreateBlock(int block[4][4],int block_id);
    void GetBorder(int block[4][4],Border &border);
    void ConvertStable(int x,int y);
    bool IsCollide(int x,int y,Direction dir);

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

    virtual void paintEvent(QPaintEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::Game *ui;

private:
    GameState game_state;
    int game_area[AREA_ROW][AREA_COL];
    block_point block_pos;
    int cur_block[4][4];
    Border cur_border;
    int next_block[4][4];
    int score;
    int game_timer;
    int paint_timer;
    int speed_ms;
    int refresh_ms;
};
#endif // GAME_H
