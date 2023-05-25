//
// Created by Jesus on 25/02/2023.
//
static bool finished = false;

using namespace std;
#include "Game.h"
Game* initGame(){
    cout << "INICIALIZO GAME";
    resetValues();
    Game* juego = new Game;
    juego->maze2 = initBoard();
    if (globalData.mode == BOT_VS_BOT){
        cout << "BOT VS BOT " << endl;
        vector<Bot_Factory> Robots;
        Robots.emplace_back(*juego->maze2,DFS_BOT, 0 ,0 );
        Robots.emplace_back(*juego->maze2,BFS_BOT, MAZE_HEIGHT-2 ,MAZE_WIDTH-2 );
        for (auto &r:Robots) {
            juego->Instancias_bots.emplace_back(r.Instanciar_Bot());
        }
    }
    else if(globalData.mode == PLAYER_VS_PLAYER){
        cout << "PLAYER VS PLAYER" <<endl;
        juego->player1 = new Player_letras(2,2 , BLUE, 4);
        juego->player2 = new Player_flechas(MAZE_WIDTH -2, MAZE_HEIGHT - 2 , BLUE, 5);
    }
    else{
        cout << "PLAYER VS BOT" << endl;
        GeneralPurpuseBot* Robot = new Bot_BFS(0,0,*juego->maze2);
        juego->player1 = new Adapter_Bot_Player(Robot);
        juego->player2 = new Player_flechas(MAZE_WIDTH -2, MAZE_HEIGHT - 2 , BLUE, 5);
    }
    juego->maze2->show = false;

    return juego;
}

void Game::DRAWGAME() {
    drawMaze2(maze2);
    if (maze2->show){
        if(globalData.mode == BOT_VS_BOT){
            for (auto bo:Instancias_bots) {
                 bo->GeneralBehaivor();
                 bo->BoT_move();
             }
        }
        else if(globalData.mode == PLAYER_VS_PLAYER){
            if (player2->getX() == maze2->target.second and player2->getY() == maze2->target.first){
                cout << "GANO PLAYER 2" << endl;
                Win = true;
            }
            else if(player1->getX() == maze2->target.second and player1->getY() == maze2->target.first){
                cout << "GANO PLAYER 1" <<endl;
                Win = true;
            }
            player1->smart_movement(*maze2,player2);
            player2->smart_movement(*maze2, player1);
            player1->DrawPlayer();
            player2->DrawPlayer();
        }
        else{
            if (player2->getX() == maze2->target.second and player2->getY() == maze2->target.first){
                cout << "GANO";
                Win = true;
            }
            player1->movement(player2,*maze2,{0,0});
            player1->smart_movement(*maze2,player2 );
            player2->smart_movement(*maze2, player1);
            player2->DrawPlayer();
        }
    }
}

static void resetValues(void) {
    finished = false;
}


void Game::updateGAMES() {
    if (IsKeyPressed(KEY_ESCAPE) || Win) {
        cout << "finalizo GAME";
        finished = true;
    }
}

bool finishGAME(void) {
    return finished;
}

void freeGame2(Game *game){
    if (game != NULL) {
//        free(game->bot);
        free(game);
    }
}

