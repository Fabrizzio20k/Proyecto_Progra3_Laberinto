#include "global.h"

void initGlobal(Global *const globalData) {
    globalData->dificultad = BFS_BOT;
    globalData->theme = MUSIC_1;
    globalData->mode = PLAYER_VS_PLAYER;
    globalData->ptos = 5;
    globalData->fullScreen = false;
    globalData->leftSound = LoadSound("../assets/sound/left.wav");
    globalData->rightSound = LoadSound("../assets/sound/right.wav");
    globalData->resetMusic();

    SetSoundVolume(globalData->leftSound, 1.0);
    SetSoundVolume(globalData->rightSound, 1.0);
}

void freeGlobal(Global *const globalData) {
    UnloadSound(globalData->leftSound);
    UnloadSound(globalData->rightSound);
}


void Global::resetMusic() {
    std::vector<Music> temp;
    Music sond1 = LoadMusicStream("../sounds/sound1.mp3");
    Music sond2 = LoadMusicStream("../sounds/sound2.mp3");
    Music sond3 = LoadMusicStream("../sounds/sound3.mp3");
    Music sond4 = LoadMusicStream("../sounds/sound4.mp3");
    temp.push_back(sond1);
    temp.push_back(sond2);
    temp.push_back(sond3);
    temp.push_back(sond4);
    music = temp;
}