#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent):
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    startMusicPlayer();
    InitGame();
    StartGame();
}

Game::~Game()
{
    delete ui;
}

int item1[4][4]=
{
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0},
    {0,0,0,0}
};
int item2[4][4]=
{
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,0,0}
};
int item3[4][4]=
{
    {0,0,1,0},
    {0,0,1,0},
    {0,1,1,0},
    {0,0,0,0}
};
int item4[4][4]=
{
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,0,0}
};
int item5[4][4]=
{
    {0,0,1,0},
    {0,1,1,0},
    {0,1,0,0},
    {0,0,0,0}
};
int item6[4][4]=
{
    {1,1,1,0},
    {0,1,0,0},
    {0,0,0,0},
    {0,0,0,0}
};
int item7[4][4]=
{
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0}
};

inline GameState operator|(GameState a, GameState b)
{return static_cast<GameState>(static_cast<int>(a) | static_cast<int>(b));}

inline void block_cpy(int dblock[4][4],int sblock[4][4])
{
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            dblock[i][j]=sblock[i][j];
        }
    }
}


void Debug(Game *obj){
    int temp_block1[4][4];
    block_cpy(temp_block1, item7);
    Border temp_border1;
    obj->GetBorder(temp_block1,temp_border1);
    int i = 0;
}

void Game::startMusicPlayer(){
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/src/audio/theme.mp3"));
    player->setVolume(50);
    player->play();
}

void Game::InitGame()
{
    for(int i=0;i<AREA_ROW;i++){
        for(int j=0;j<AREA_COL;j++){
            game_area[i][j]=0;
        }
    }

    speed_ms=800;
    refresh_ms=3;
    srand(time(0));
    score=0;
    loadUI();
}

void Game::StartGame()
{
    game_state = FreeRun;

    game_timer=startTimer(speed_ms);
    paint_timer=startTimer(refresh_ms);
    int block_id=rand()%7;
    CreateBlock(next_block,block_id);
    ResetBlock();
    Debug(this);
}

void Game::GameOver()
{
    game_state = Game_Over;

    killTimer(game_timer);
    killTimer(paint_timer);
    QMessageBox::information(this,"failed","game over");
}

void Game::loadUI(){

}

void Game::ResetBlock()
{
    block_cpy(cur_block,next_block);
    GetBorder(cur_block,cur_border);

    int block_id=rand()%7;
    CreateBlock(next_block,block_id);

    block_point start_point;
    start_point.pos_x = AREA_COL / 2 - 2;
    start_point.pos_y = -4;
    block_pos=start_point;
}

void Game::BlockMove(Direction dir)
{
    switch (dir) {
    case UP:
        if(IsCollide(block_pos.pos_x,block_pos.pos_y,UP)){
            break;
        }

        BlockRotate(cur_block);

        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(block_pos.pos_y+i >=0 &&   game_area[block_pos.pos_y+i][block_pos.pos_x+j] != 2){
                    game_area[block_pos.pos_y+i][block_pos.pos_x+j]=cur_block[i][j];
                }
            }
        }
        GetBorder(cur_block,cur_border);
        break;
    case DOWN:
        if(block_pos.pos_y+cur_border.dbound==AREA_ROW-1)
        {
            game_state = Wait;

            ConvertStable(block_pos.pos_x,block_pos.pos_y);
            ResetBlock();

            game_state = FreeRun;

            break;
        }
        if(IsCollide(block_pos.pos_x,block_pos.pos_y,DOWN))
        {

            game_state = Wait;

            ConvertStable(block_pos.pos_x,block_pos.pos_y);
            ResetBlock();

            game_state = FreeRun;

            break;
        }
        for(int j=cur_border.lbound;j<=cur_border.rbound;j++){
            if(block_pos.pos_y >=0){
                game_area[block_pos.pos_y][block_pos.pos_x+j]=0;
            }
        }
        block_pos.pos_y+=1;
        for(int i=0;i<4;i++){
            for(int j=cur_border.lbound;j<=cur_border.rbound;j++){
                if(block_pos.pos_y+i<=AREA_ROW-1&&game_area[block_pos.pos_y+i][block_pos.pos_x+j]!=2){
                    if(block_pos.pos_y+i >=0){
                        game_area[block_pos.pos_y+i][block_pos.pos_x+j]=cur_block[i][j];
                    }
                }
            }
        }
        break;
    case LEFT:
        if(block_pos.pos_x+cur_border.lbound==0||IsCollide(block_pos.pos_x,block_pos.pos_y,LEFT))
            break;
        for(int i=cur_border.ubound;i<=cur_border.dbound;i++){
            if(block_pos.pos_y+i >=0){
                game_area[block_pos.pos_y+i][block_pos.pos_x+3]=0;
            }
        }
        block_pos.pos_x-=1;
        for(int i=cur_border.ubound;i<=cur_border.dbound;i++){
            for(int j=0;j<4;j++){
                if(block_pos.pos_x+j>=0&&game_area[block_pos.pos_y+i][block_pos.pos_x+j]!=2){
                    if(block_pos.pos_y+i >=0){
                        game_area[block_pos.pos_y+i][block_pos.pos_x+j]=cur_block[i][j];
                    }
                }
            }
        }
        break;
    case RIGHT:
        if(block_pos.pos_x+cur_border.rbound==AREA_COL-1||IsCollide(block_pos.pos_x,block_pos.pos_y,RIGHT))
            break;
        for(int i=cur_border.ubound;i<=cur_border.dbound;i++){
            if(block_pos.pos_y+i >=0){
                game_area[block_pos.pos_y+i][block_pos.pos_x]=0;
            }
        }
        block_pos.pos_x+=1;
        for(int i=cur_border.ubound;i<=cur_border.dbound;i++){
            for(int j=0;j<4;j++){
                if(block_pos.pos_x+j<=AREA_COL-1&&game_area[block_pos.pos_y+i][block_pos.pos_x+j]!=2){
                    if(block_pos.pos_y+i >=0){
                        game_area[block_pos.pos_y+i][block_pos.pos_x+j]=cur_block[i][j];
                    }
                }
            }
        }
        break;
    case SPACE:
        game_state = Wait;

        while(block_pos.pos_y+cur_border.dbound<AREA_ROW-1&&!IsCollide(block_pos.pos_x,block_pos.pos_y,DOWN))
        {
            for(int j=cur_border.lbound;j<=cur_border.rbound;j++){
                if(block_pos.pos_y >=0){
                    game_area[block_pos.pos_y][block_pos.pos_x+j]=0;
                }
            }
            block_pos.pos_y+=1;
            for(int i=0;i<4;i++){
                for(int j=cur_border.lbound;j<=cur_border.rbound;j++){
                    if(block_pos.pos_y+i<=AREA_ROW-1&&game_area[block_pos.pos_y+i][block_pos.pos_x+j]!=2){
                        if(block_pos.pos_y+i >=0){
                            game_area[block_pos.pos_y+i][block_pos.pos_x+j]=cur_block[i][j];
                        }
                    }
                }
            }
        }
        ConvertStable(block_pos.pos_x,block_pos.pos_y);
        ResetBlock();

        game_state = FreeRun;

        break;
    default:
        break;
    }


    int i=AREA_ROW-1;
    int line_count=0;
    while(i>=1)
    {
        bool is_line_full=true;
        for(int j=0;j<AREA_COL;j++)
            if(game_area[i][j]==0)
            {
                is_line_full=false;
                i--;
                break;
            }
        if(is_line_full)
        {
            for(int k=i;k>=1;k--){
                for(int j=0;j<AREA_COL;j++){
                    game_area[k][j]=game_area[k-1][j];
                }
            }
            line_count++;
        }
    }

    score+=line_count*10;
    for(int j=0;j<AREA_COL;j++)
        if(game_area[0][j]==2){
            GameOver();
        }
}

void Game::BlockRotate(int block[4][4])
{
    int temp_block[4][4];

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            temp_block[3-j][i]=block[i][j];
        }
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            block[i][j]=temp_block[i][j];
        }
    }
}

void Game::CreateBlock(int block[4][4],int block_id)
{
    switch (block_id)
    {
    case 0:
        block_cpy(block,item1);
        break;
    case 1:
        block_cpy(block,item2);
        break;
    case 2:
        block_cpy(block,item3);
        break;
    case 3:
        block_cpy(block,item4);
        break;
    case 4:
        block_cpy(block,item5);
        break;
    case 5:
        block_cpy(block,item6);
        break;
    case 6:
        block_cpy(block,item7);
        break;
    default:
        break;
    }
}

void Game::GetBorder(int block[4][4],Border &border)
{
    //Calculate border of UP, DOWN, LEFT, RIGHT
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(block[i][j]==1){
                border.dbound=i;
                break;
            }
        }
    }

    for(int i=3;i>=0;i--){
        for(int j=0;j<4;j++){
            if(block[i][j]==1){
                border.ubound=i;
                break;
            }
        }
    }

    for(int j=0;j<4;j++){
        for(int i=0;i<4;i++){
            if(block[i][j]==1){
                border.rbound=j;
                break;
            }
        }
    }

    for(int j=3;j>=0;j--){
        for(int i=0;i<4;i++){
            if(block[i][j]==1){
                border.lbound=j;
                break;
            }
        }
    }
}


void Game::ConvertStable(int x,int y)
{
    for(int i=cur_border.ubound;i<=cur_border.dbound;i++){
        for(int j=cur_border.lbound;j<=cur_border.rbound;j++){
            if(y+i >= 0 && cur_block[i][j]==1){
                game_area[y+i][x+j]=2; //x and y is reverse
            }
        }
    }
}

bool Game::IsCollide(int x,int y,Direction dir)
{
    int temp_block[4][4];
    block_cpy(temp_block,cur_block);
    Border temp_border;
    GetBorder(temp_block,temp_border);

    switch(dir)
    {
    case UP:
        BlockRotate(temp_block);
        GetBorder(temp_block,temp_border); //Recompute border atfer rotate.
        break;
    case DOWN:
        y+=1;
        break;
    case LEFT:
        x-=1;
        break;
    case RIGHT:
        x+=1;
        break;
    default:
        break;
    }

    for(int i=temp_border.ubound;i<=temp_border.dbound;i++){
        for(int j=temp_border.lbound;j<=temp_border.rbound;j++){
            if(game_area[y+i][x+j]==2&&temp_block[i][j]==1
                    ||x+temp_border.lbound<0
                    ||x+temp_border.rbound>AREA_COL-1){
                return true;}
        }
    }

    return false;
}

void Game::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter.drawRect(MARGIN,MARGIN,AREA_COL*BLOCK_SIZE,AREA_ROW*BLOCK_SIZE);
    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(next_block[i][j]==1){
                painter.drawRect(MARGIN*3+AREA_COL*BLOCK_SIZE+j*BLOCK_SIZE,MARGIN+i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);
            }
        }
    }

    QFontDatabase::addApplicationFont(":/src/font/pixel.ttf");
    painter.setPen(Qt::black);
    painter.setFont(QFont(font_family, font_size));
    painter.drawText(QRect(MARGIN*3+AREA_COL*BLOCK_SIZE,MARGIN*2+4*BLOCK_SIZE,BLOCK_SIZE*4,BLOCK_SIZE*4),
                     Qt::AlignCenter,
                     "SCORE: "+ QString::number(score));
    for(int i=0;i<AREA_ROW;i++)
        for(int j=0;j<AREA_COL;j++)
        {
            if(game_area[i][j]==1)
            {
                painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
            else if(game_area[i][j]==2)
            {
                painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
        }
}

void Game::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==game_timer && game_state != Game_Over){
        BlockMove(DOWN);
    }
    if(event->timerId()==paint_timer){
        update();
    }
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if( game_state == FreeRun){

        switch(event->key())
        {
        case Qt::Key_Up:
            BlockMove(UP);
            break;
        case Qt::Key_Down:
            BlockMove(DOWN);
            break;
        case Qt::Key_Left:
            BlockMove(LEFT);
            break;
        case Qt::Key_Right:
            BlockMove(RIGHT);
            break;
        case Qt::Key_Space:
            BlockMove(SPACE);
            break;
        default:
            break;
        }

    }
}
