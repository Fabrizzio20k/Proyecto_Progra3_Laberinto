//
// Created by leonc on 25/02/2023.
//

#ifndef MAZE_PLAYER_H
#define MAZE_PLAYER_H

#include "Bot.h"
using Pi = std::pair<int,int>;

class Player {
public:
    ~Player();
    [[nodiscard]] virtual int getX() = 0;
    [[nodiscard]] virtual int getY() = 0;



    virtual bool sig_cuadrado(Maze2& y) = 0;

    virtual bool tecla_val() = 0;

    virtual void avanz_play() = 0;

    virtual int vecinos(Maze2& y, Player* player) = 0;

    virtual bool col_play(Player* player) = 0;

    virtual void movement( Player* player, Maze2& y, Pi coords) = 0;

    virtual void smart_movement(Maze2& y ,  Player* player) = 0;

    virtual void paint_path(Maze2& y) = 0;

    virtual bool getTurn() = 0;

    virtual void setTurn(bool trn) = 0;

    virtual void DrawPlayer() = 0;

};

class Player_letras: public Player{
private:
    int x_;
    int y_;
    Color color_;
    int color_pint;
    bool turn = false;
public:
    Player_letras(int x, int y, const Color &color, int _color_pint);

    int getX() override;

    int getY() override;


    virtual ~Player_letras();

    bool sig_cuadrado(Maze2& y) override;

    bool tecla_val() override;

    void avanz_play() override;

    int vecinos(Maze2& y , Player* player) override;

    bool col_play(Player* player) override;

    void movement( Player* player   ,Maze2 &y, Pi coords) override;

    void smart_movement(Maze2& y, Player* player) override;

    bool getTurn() override;

    void setTurn(bool trn) override;

    void DrawPlayer() override;

    void paint_path(Maze2 &y) override;

};

class Player_flechas: public Player{
private:
    int x_;
    int y_;
    Color color_;
    int color_pint;
    bool turn = false;
public:
    void DrawPlayer() override;

    Player_flechas(int x, int y, const Color &color, int _color_pint);

    virtual ~Player_flechas();

    int getX() override;

    int getY() override;



    bool sig_cuadrado(Maze2& y) override;

    bool tecla_val() override;

    void avanz_play() override;

    int vecinos(Maze2& y, Player* player) override;

    bool col_play( Player* player) override;

    void movement(Player* player , Maze2 &y, Pi coords) override;

    void smart_movement(Maze2& y, Player* player) override;

    bool getTurn() override;

    void setTurn(bool trn) override;


    void paint_path(Maze2 &y) override;

};


class Adapter_Bot_Player : public Player{
private:
    GeneralPurpuseBot* bot;
public:
    explicit Adapter_Bot_Player(GeneralPurpuseBot *bot);

    void smart_movement(Maze2 &y,  Player* player) override;
    bool getTurn() override;
    void setTurn(bool trn) override;

    int getX() override;

    int getY() override;


    void DrawPlayer() override;

    bool sig_cuadrado(Maze2 &y) override;

    bool tecla_val() override;

    void avanz_play() override;

    int vecinos(Maze2 &y , Player* player) override;

    bool col_play( Player* player) override;

    void movement( Player* player  ,Maze2 &y, Pi coords) override;

    void paint_path(Maze2 &y) override;


};

#endif //MAZE_PLAYER_H
