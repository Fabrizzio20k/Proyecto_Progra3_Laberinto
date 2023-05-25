//
// Created by Jesus on 25/02/2023.
//

#ifndef EXAMPLES_BOTBORRADOR_H
#define EXAMPLES_BOTBORRADOR_H
#include "stack"
#include "maze2.h"
#include <queue>
#include <iomanip>
#include <map>
#include <set>
using I = int;
using Pi = std::pair<int,int>;
class GeneralPurpuseBot{
protected:
    bool turn = false;
public:
    virtual void GeneralBehaivor()=0; // Target Search and Path making
    virtual void draw_pathSeeking()=0; // Draw the bot
    virtual void BoT_move() =0;// Once a path has being made the bot will start heding to its target
    virtual bool StopTurn()=0; // Gives inormation about the movement status to other players //to be implemented
    virtual bool getTurn() = 0;
    virtual std::set<Pi> getVisited() = 0;
    virtual std::stack<Pi> getMovement() = 0;
    virtual void setTurn(bool trn) = 0;
};



class Bot_BFS:public GeneralPurpuseBot{
private:
    float x_{};
    float y_{};
    std::stack<Pi>Visited_coords; //needed in DFS and BFS
    std::queue<std::pair<int , int>> Frontier; // needed in BFS
    Pi Target;      //META -->//needed in DFS and BFS
    std::map<Pi,Pi> Path;//needed in DFS(to be included) and BFS
    bool PathAvaliable= false; //needed in DFS(to be included) and BFS
    bool PathReady = false;//needed in DFS(to be included) and BFS

    size_t SearchNumber=0;//needed in DFS(to be included) and BFS
    Maze2 maze;
    std::set<Pi> Visited_algot;
public:
    std::set<Pi> Visited;
    std::stack<Pi> Movement;//needed in DFS(to be included) and BFS

    Bot_BFS(float x , float y, Maze2& Mmaze):x_(x),y_(y),maze(Mmaze){
        Visited_coords.push({x, y});

        Frontier.push({x,y});//set irst possition as visited
        Target={MAZE_HEIGHT/2,MAZE_WIDTH/2};
        Path[{x,y}]={x,y};//Mark first position as its own root
    }
    void draw();
    void BFS(Maze2& Maze);
    void GeneratePath(Pi coord);
    void BotMove(Maze2 & Maze);
    //overriding unctions
    void GeneralBehaivor()override;
    void draw_pathSeeking()override;
    void BoT_move() override;
    bool StopTurn() override;
    bool getTurn() override;
    void setTurn(bool trn) override;
    std::set<Pi> getVisited() override;
    std::stack<Pi> getMovement() override;

};
class Bot_DFS:public GeneralPurpuseBot{


private:
    float x_{};
    float y_{};
    std::stack<Pi>Visited_coords; //needed in DFS and BFS
    std::queue<std::pair<int , int>> Frontier; // needed in BFS
    Pi Target;      //META -->//needed in DFS and BFS
    std::map<Pi,Pi> Path;//needed in DFS(to be included) and BFS
    bool PathAvaliable= false; //needed in DFS(to be included) and BFS
    bool PathReady = false;//needed in DFS(to be included) and BFS

    size_t SearchNumber=0;//needed in DFS(to be included) and BFS
    Maze2 maze;
    std::set<Pi> Visited_algot;
public:
    std::set<Pi> Visited;
    std::stack<Pi> Movement;//needed in DFS(to be included) and BFS

    Bot_DFS(float x , float y, Maze2 Mmaze):x_(x),y_(y),maze(Mmaze){
        Visited_coords.push({x, y});
        Visited_algot.insert({x,y});
        Frontier.push({x,y});//set irst possition as visited
        Target={MAZE_HEIGHT/2,MAZE_WIDTH/2};
        Path[{x,y}]={x,y};//Mark first position as its own root

    }

    void draw();
    void DFS(Maze2& Maze);
    void GeneratePath(Pi coord);
    void Botmove(Maze2 & Maze);
    //overriding unctions
    void GeneralBehaivor()override;
    void draw_pathSeeking()override;
    void BoT_move() override;
    bool StopTurn() override;
    bool getTurn() override;
    void setTurn(bool trn) override;
    std::set<Pi> getVisited() override;
    std::stack<Pi> getMovement() override;

};
class Bot_Factory{
public:
    Bot_Factory(Maze2 MMaze,dificult dif,int x=0 , int y=0);
    GeneralPurpuseBot* Instanciar_Bot();


private:
    Maze2 maze_;
    GeneralPurpuseBot* new_bot_instantiation;


};



#endif //EXAMPLES_BOTBORRADOR_H
