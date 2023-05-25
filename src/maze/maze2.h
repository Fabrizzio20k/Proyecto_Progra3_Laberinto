
#ifndef EXAMPLES_MAZE2_H
#define EXAMPLES_MAZE2_H

//using Pi = std::pair<int,int>;
#include <iostream>
#include <stack>
#include <raylib.h>
#include "algorithm"
#include <vector>
#include <raylib.h>
#include "../global.h"
extern Global globalData;

//using Pi = std::pair<int,int>;
using I = int;
class Maze2 {
private:
    inline static int * tam;
// La instancia unica
    inline static Maze2* _inst;
    Maze2(int x,int y) {
        Maze2::tam = new int[x*y];
    }

public:
    static Maze2* getInstance(int H,int W);
    std::stack<std::pair<I,I> >  Visited_Coordinates;

    std::pair<int,int> target = {MAZE_HEIGHT/2,MAZE_WIDTH/2};
    I &operator()(int i_row, int i_col) ;
    I operator()(int i_row, int i_col) const;
    bool show = false;
    //    Rectangle recRight;
};

void backtraking(Maze2& Alfa);
Maze2 *initBoard(void);
void drawMaze2(Maze2 *const maze);

#endif //EXAMPLES_MAZE2_H
