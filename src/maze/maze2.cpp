//
// Created by Jesus on 16/02/2023.
//

#include "maze2.h"
#include "iostream"
#include "Player2.h"
#include "Bot.h"
#include "iomanip"

using namespace std;
Global Data;
using Pi = std::pair<int,int>;
static const int32_t MAX_COUNTER = 5;
static int32_t counter = MAX_COUNTER;
static int32_t prevCounter = 0;
static void drawCounterScreen(void);
static void UpdateCounter (void);
static bool showCounter = true;
static void resetValues(void);
//Player* zeta = new Player(1,1,GREEN);
//Player* Beta = new Player(MAZE_HEIGHT-1,MAZE_WIDTH-1,PURPLE);



Maze2* initBoard() {
    cout << "INICIALIZO MAZE" << endl;
    std::cout << "gola";
    resetValues();
    Maze2* maze = Maze2::getInstance(MAP_HEIGHT,MAZE_WIDTH);
    backtraking(*maze);

    (*maze)(MAZE_HEIGHT/2, MAZE_WIDTH/2) = 1;
    (*maze)((MAZE_HEIGHT/2)-1, MAZE_WIDTH/2) = 1;
    (*maze)((MAZE_HEIGHT/2)+1, MAZE_WIDTH/2) = 1;
    (*maze)(MAZE_HEIGHT/2, (MAZE_WIDTH/2)-1) = 1;
    (*maze)(MAZE_HEIGHT/2, (MAZE_WIDTH/2)+1) = 1;
    cout << endl;
    return maze;
}


static void resetValues(void) {
    showCounter = true;
    counter = MAX_COUNTER;
    prevCounter = 0;
}
I &Maze2::operator()(int i_row, int i_col) {
    return tam[MAZE_WIDTH*i_row+(MAZE_WIDTH-(MAZE_WIDTH-i_col))];
}

I Maze2::operator()(int i_row, int i_col) const {
    return tam[MAZE_WIDTH*i_row+(MAZE_WIDTH-(MAZE_WIDTH-i_col))];
}

void drawMaze2(Maze2 *const maze) {
    if (showCounter){
        UpdateCounter();
        drawCounterScreen();
    }
    else{
        maze->show = true;
        DrawRectangle(maze->target.first * TILE_SIZE_WIDTH, maze->target.first*TILE_SIZE_HEIGHT, TILE_SIZE_WIDTH, TILE_SIZE_HEIGHT, RED);
        for (int i = 0; i < MAZE_HEIGHT; i++)
        {
            for (int j = 0; j < MAZE_WIDTH; j++)
            {
                if ((*maze)(i,j) == 0)
                {
                    DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, DARKGRAY);
                }
                else
                {
                    DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
                }

                if((*maze)(i,j)==2)
                {
                    DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, PINK);
                }
                if((*maze)(i,j)==3)
                {
                    DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, PURPLE);
                }
                if((*maze)(i,j)==4)
                {
                    DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, YELLOW);
                }
                if((*maze)(i,j)==5)
                {
                    DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
                }
            }
        }

        DrawRectangle(float(Data.screen_width/2),float(Data.screen_height/2),CELL_SIZE, CELL_SIZE,
                      RED
        );
    }


}
void backtraking(Maze2& Alfa) {
    if(!Alfa.Visited_Coordinates.empty())
    {
        I current_x=Alfa.Visited_Coordinates.top().first;
        I current_y=Alfa.Visited_Coordinates.top().second;
        std::vector<std::pair<std::pair<I,I>, I>> Neighbors;  // 1 represents a vertical and 2 represents an horizontal movement
        // The second pair indicates if movement is vertical or horizontal
        if(Alfa(current_x+2,current_y)!=1 and current_x+2<MAZE_HEIGHT) // Check South
        {
            Neighbors.push_back({{current_x+2,current_y},1});
        }
        if(Alfa(current_x,current_y+2)!=1 and current_y+2<MAZE_WIDTH) // Check East
        {
            Neighbors.push_back({{current_x,current_y+2},2});
        }
        if(Alfa(current_x,current_y-2)!=1 and current_y-2>=1 )       //Check West
        {
            Neighbors.push_back({{current_x,current_y-2},-2});

        }
        if(Alfa(current_x-2,current_y)!=1 and current_x-2>=1 )   //Check North
        {
            Neighbors.push_back({{current_x-2,current_y},-1});


        }

        if(!Neighbors.empty())
        {
            auto Next_coordinate=Neighbors[rand()%Neighbors.size()];// Choose an avaliable neighbor randomdly
            Alfa.Visited_Coordinates.push(Next_coordinate.first); // Push new coordinate in the stack
            Alfa(Next_coordinate.first.first,Next_coordinate.first.second)=1; // marked the new coordinate as visited
            if(abs(Next_coordinate.second)==1) // check if the movement was vertical or not
            {
                Alfa(current_x+Next_coordinate.second,current_y)=1;//marked middle as visited

            }else{
                auto add=(Next_coordinate.second>0)?1:-1;
                Alfa(current_x,current_y+add)=1;//marked middle as visited
            }
            backtraking(Alfa);

        }else {

            Alfa.Visited_Coordinates.pop();
            backtraking(Alfa);
        }


    }else{

        std::cout<<"MAZE SUCCESFULLY GENERATED !!!"<<std::endl;
    }

}
static void drawCounterScreen(void) {
    DrawRectangle(
            0,
            0,
            GetScreenWidth(),
            GetScreenHeight(),
            Fade((Color){ 43, 43, 38, 255 }, 0.6)
    );
    vector<const char* > v = {"","START","1","2","3","4"};
    const int32_t fontSize = 120;
    const char* value = TextFormat("%s",v[counter]);
    const int32_t posX = GetScreenWidth() / 2 - MeasureText(value, fontSize) / 2;
    const int32_t posY = GetScreenHeight() / 2 - (fontSize / 2);
    DrawText(value, posX, posY, fontSize, (Color){ 224, 219, 205, 255 });

}
static void UpdateCounter (void) {
    if (counter > 0) {
        const int32_t time = (int32_t) GetTime();
        if (time != prevCounter) {
            prevCounter = time;
            counter--;
        }
    } else {
        showCounter = false;
        counter = MAX_COUNTER;
        prevCounter = 0;
    }
}

Maze2* Maze2::getInstance(int H,int W){
    if (_inst == nullptr){
        cout << "creando" << endl;
        _inst = new Maze2(H,W);
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                (*_inst)(x,y) = 0;
            }
        }
        _inst->Visited_Coordinates.push({(MAZE_HEIGHT%2==0)?0:1,(MAZE_WIDTH%2==0)?0:1});
        cout << _inst->Visited_Coordinates.size() << endl;
    }
    else{
        cout << "RESET" << endl;
        for (int x = 0; x < H; ++x) {
            for (int y = 0; y < W; ++y) {
                (*_inst)(x,y) = 0;
            }
        }
        cout << _inst->Visited_Coordinates.size() << endl;
        _inst->Visited_Coordinates.push({(MAZE_HEIGHT%2==0)?0:1,(MAZE_WIDTH%2==0)?0:1});
    }
    return _inst;

}