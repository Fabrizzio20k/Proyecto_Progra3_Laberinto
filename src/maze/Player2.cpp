#include "Player2.h"



Player::~Player() {}

Player_letras::Player_letras(int x, int y, const Color &color, int _color_pint)  {
    x_ = x;
    y_ = y;
    color_ = color;
    color_pint = _color_pint;
}

Player_letras::~Player_letras() {

}





bool Player_letras::getTurn() {
    return turn;
}

void Player_letras::setTurn(bool trn) {
    turn = trn;
}



void Player_letras::paint_path(Maze2 &y) {
    if (y(y_,x_) != color_pint)
        y(y_,x_) = color_pint;
    else if (y(y_,x_) == color_pint)
        y(y_,x_) = 1;
}

void Player_letras::DrawPlayer() {
    DrawRectangle(x_ * CELL_SIZE, y_ * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLUE);
}

bool Player_letras::sig_cuadrado(Maze2 &y) {
    if (IsKeyDown(KEY_A)) {
        if (y(y_, x_ - 1) != 0)
            return true;
    }
    else if (IsKeyDown(KEY_D)) {
        if (y(y_, x_ + 1) != 0)
            return true;
    }
    else if (IsKeyDown(KEY_W)) {
        if (y(y_ - 1, x_) != 0)
            return true;
    }
    else if (IsKeyDown(KEY_S)) {
        if (y(y_ + 1, x_) != 0)
            return true;
    }
    return false;
}

bool Player_letras::tecla_val() {
    if (IsKeyDown(KEY_A) or IsKeyDown(KEY_W) or IsKeyDown(KEY_D) or IsKeyDown(KEY_S)){
        return true;
    }
    return false;
}

void Player_letras::avanz_play() {
    if (IsKeyDown(KEY_A)){
        x_ -= 1;
    }
    else if (IsKeyDown(KEY_D)){
        x_ += 1;
    }
    else if (IsKeyDown(KEY_W)){
        y_ -= 1;
    }
    else if (IsKeyDown(KEY_S)){
        y_ += 1;
    }
}

int Player_letras::vecinos(Maze2 &y, Player *player) {
    int total_vec = 0;
    if (y(y_, x_ + 1) != 0 and (player->getX() != x_ + 1 or player->getY() != y_) and (x_ + 1 != MAZE_HEIGHT / 2 or y_ != MAZE_WIDTH / 2)){
        total_vec++;
    }
    if (y(y_, x_ - 1) != 0 and (player->getX() != x_ - 1 or player->getY() != y_) and (x_ - 1 != MAZE_HEIGHT / 2 or y_ != MAZE_WIDTH / 2)){
        total_vec++;
    }
    if (y(y_ + 1, x_) != 0 and (player->getY() != y_ + 1 or player->getX() != x_) and (y_ + 1 != MAZE_WIDTH / 2 or x_ != MAZE_HEIGHT / 2)){
        total_vec++;
    }
    if (y(y_ - 1, x_) != 0 and (player->getY() != y_ - 1 or player->getX() != x_) and (y_ - 1 != MAZE_WIDTH / 2 or x_ != MAZE_HEIGHT / 2)){
        total_vec++;
    }
    return total_vec;
}

bool Player_letras::col_play(Player *player) {
    if (IsKeyDown(KEY_A)) {
        if ((y_ != player->getY() or x_ - 1 != player->getX()) and (x_ - 1 != MAZE_HEIGHT / 2 or y_ != MAZE_WIDTH / 2))
            return true;
    }
    else if (IsKeyDown(KEY_D)) {
        if ((y_ != player->getY() or x_ + 1 != player->getX()) and (x_ + 1 != MAZE_HEIGHT / 2 or y_ != MAZE_WIDTH / 2))
            return true;
    }
    else if (IsKeyDown(KEY_W)) {
        if ((y_ - 1 != player->getY() or x_ != player->getX()) and (y_ - 1 != MAZE_WIDTH / 2 or x_ != MAZE_HEIGHT / 2))
            return true;
    }
    else if (IsKeyDown(KEY_S)) {
        if ((y_ + 1 != player->getY() or x_ != player->getX()) and (y_ + 1 != MAZE_WIDTH / 2 or x_ != MAZE_HEIGHT / 2))
            return true;
    }
    return false;
}

void Player_letras::movement(Player *player, Maze2 &y, Pi coords) {
    while (vecinos(y, player) == 2){
        if (y(y_ - 1, x_) != 0 and coords.first != y_ - 1 and col_play(player)){
            coords.first = y_;
            coords.second = x_;
            y_ -= 1;
            paint_path(y);

        }
        else if (y(y_, x_ + 1) != 0 and coords.second != x_ + 1 and col_play(player)){
            coords.second = x_;
            coords.first = y_;
            x_ += 1;
            paint_path(y);


        }
        else if (y(y_ + 1, x_) != 0 and coords.first != y_ + 1 and col_play(player)){
            coords.first = y_;
            coords.second = x_;
            y_ += 1;
            paint_path(y);


        }
        else if (y(y_, x_ - 1) != 0 and coords.second != x_ - 1 and col_play(player)){
            coords.second = x_;
            coords.first = y_;
            x_ -= 1;
            paint_path(y);

        }
    }
}

void Player_letras::smart_movement(Maze2 &y, Player *player) {

    if (IsKeyDown(KEY_G)){
        this->setTurn(false);
        player->setTurn(true);
    }
    std::pair<int,int> coords_ac {y_,x_};
    if (tecla_val()  and sig_cuadrado(y) and col_play(player) and turn)
    {
        avanz_play();
        paint_path(y);
        DrawPlayer();
        movement( player ,y, coords_ac);
        DrawPlayer();
        turn = !turn;
    }
}


int Player_letras::getX() {
    return x_;
}

int Player_letras::getY() {
    return y_;
}






//Player Flechas


Player_flechas::Player_flechas(int x, int y, const Color &color, int _color_pint)  {
    x_ = x;
    y_  = y;
    color_ = color;
    color_pint = _color_pint;
}

Player_flechas::~Player_flechas() {

}



bool Player_flechas::sig_cuadrado(Maze2& y) {
    if (IsKeyDown(KEY_LEFT)) {
        if (y(y_, x_ - 1) != 0)
            return true;
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        if (y(y_, x_ + 1) != 0)
            return true;
    }
    else if (IsKeyDown(KEY_UP)) {
        if (y(y_ - 1, x_) != 0)
            return true;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        if (y(y_ + 1, x_) != 0)
            return true;
    }
    return false;
}

bool Player_flechas::tecla_val() {
    if (IsKeyDown(KEY_LEFT) or IsKeyDown(KEY_UP) or IsKeyDown(KEY_RIGHT) or IsKeyDown(KEY_DOWN)){
        return true;
    }
    return false;
}

void Player_flechas::avanz_play() {
    if (IsKeyDown(KEY_LEFT)){
        x_ -= 1;
    }
    else if (IsKeyDown(KEY_RIGHT)){
        x_ += 1;
    }
    else if (IsKeyDown(KEY_UP)){
        y_ -= 1;
    }
    else if (IsKeyDown(KEY_DOWN)){
        y_ += 1;
    }
}

int Player_flechas::getX() {
    return x_;
}

int Player_flechas::getY() {
    return y_;
}

int Player_flechas::vecinos(Maze2& y, Player* player) {
    int total_vec = 0;
    if (y(y_, x_ + 1) != 0 and (player->getX() != x_ + 1 or player->getY() != y_) and (x_ + 1 != MAZE_HEIGHT / 2 or y_ != MAZE_WIDTH / 2)){
        total_vec++;
    }
    if (y(y_, x_ - 1) != 0 and (player->getX() != x_ - 1 or player->getY() != y_) and (x_ - 1 != MAZE_HEIGHT / 2 or y_ != MAZE_WIDTH / 2)){
        total_vec++;
    }
    if (y(y_ + 1, x_) != 0 and (player->getY() != y_ + 1 or player->getX() != x_) and (y_ + 1 != MAZE_WIDTH / 2 or x_ != MAZE_HEIGHT / 2)){
        total_vec++;
    }
    if (y(y_ - 1, x_) != 0 and (player->getY() != y_ - 1 or player->getX() != x_) and (y_ - 1 != MAZE_WIDTH / 2 or x_ != MAZE_HEIGHT / 2)){
        total_vec++;
    }
    return total_vec;
}

bool Player_flechas::col_play( Player* player) {
    if (IsKeyDown(KEY_LEFT)) {
        if ((y_ != player->getY() or x_ - 1 != player->getX()) and (x_ - 1 != MAZE_HEIGHT / 2 or y_ != MAZE_WIDTH / 2))
            return true;
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        if ((y_ != player->getY() or x_ + 1 != player->getX()) and (x_ + 1 != MAZE_HEIGHT / 2 or y_ != MAZE_WIDTH / 2))
            return true;
    }
    else if (IsKeyDown(KEY_UP)) {
        if ((y_ - 1 != player->getY() or x_ != player->getX()) and (y_ - 1 != MAZE_WIDTH / 2 or x_ != MAZE_HEIGHT / 2))
            return true;
    }
    else if (IsKeyDown(KEY_DOWN)) {
        if ((y_ + 1 != player->getY() or x_ != player->getX()) and (y_ + 1 != MAZE_WIDTH / 2 or x_ != MAZE_HEIGHT / 2))
            return true;
    }
    return false;
}

void Player_flechas::movement(Player* player,Maze2 &y, Pi coords) {
    while (vecinos(y, player) == 2){
        if (y(y_ - 1, x_) != 0 and coords.first != y_ - 1 and col_play(player)){
            coords.first = y_;
            coords.second = x_;
            y_ -= 1;
            paint_path(y);

        }
        else if (y(y_, x_ + 1) != 0 and coords.second != x_ + 1 and col_play(player)){
            coords.second = x_;
            coords.first = y_;
            x_ += 1;
            paint_path(y);


        }
        else if (y(y_ + 1, x_) != 0 and coords.first != y_ + 1 and col_play(player)){
            coords.first = y_;
            coords.second = x_;
            y_ += 1;
            paint_path(y);


        }
        else if (y(y_, x_ - 1) != 0 and coords.second != x_ - 1 and col_play(player)){
            coords.second = x_;
            coords.first = y_;
            x_ -= 1;
            paint_path(y);

        }


    }
}

void Player_flechas::smart_movement(Maze2& y, Player* player) {

    if (IsKeyDown(KEY_F)){
        player->setTurn(true);
    }

    std::pair<int,int> coords_ac {y_,x_};
    if (tecla_val()  and sig_cuadrado(y) and col_play(player) and turn)
    {
        avanz_play();
        paint_path(y);
        DrawPlayer();
        movement( player ,y, coords_ac);
        DrawPlayer();
        turn = !turn;
    }
}

bool Player_flechas::getTurn() {
    return turn;
}



void Player_flechas::setTurn(bool trn) {
    turn = trn;
}

void Player_flechas::paint_path(Maze2 &y) {
    if (y(y_,x_) != color_pint)
        y(y_,x_) = color_pint;
    else if (y(y_,x_) == color_pint)
        y(y_,x_) = 1;
}

void Player_flechas::DrawPlayer() {
    DrawRectangle(x_ * CELL_SIZE, y_ * CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
}


void Adapter_Bot_Player::smart_movement(Maze2 &y , Player* player) {
    if(IsKeyPressed(KEY_F)){
        player->setTurn(true);
    }
    bot->BoT_move();
}

bool Adapter_Bot_Player::getTurn() {
    return bot->getTurn();
}

void Adapter_Bot_Player::setTurn(bool trn) {
    bot->setTurn(trn);
}

Adapter_Bot_Player::Adapter_Bot_Player(GeneralPurpuseBot *bot) : bot(bot) {}

int Adapter_Bot_Player::getX() {
    return 0;
}

int Adapter_Bot_Player::getY() {
    return 0;
}



bool Adapter_Bot_Player::sig_cuadrado(Maze2 &y) {
    return false;
}

bool Adapter_Bot_Player::tecla_val() {
    return false;
}

void Adapter_Bot_Player::avanz_play() {

}

int Adapter_Bot_Player::vecinos(Maze2 &y, Player* player) {
    return 0;
}

bool Adapter_Bot_Player::col_play(  Player* player) {
    return false;
}

void Adapter_Bot_Player::movement( Player* player  ,Maze2 &y, Pi coords) {
    bot->GeneralBehaivor();
}

void Adapter_Bot_Player::paint_path(Maze2 &y) {

}

void Adapter_Bot_Player::DrawPlayer() {

}