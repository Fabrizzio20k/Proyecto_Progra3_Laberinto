//
// Created by Jesus on 16/02/2023.
//

#ifndef EXAMPLES_SCENES_H
#define EXAMPLES_SCENES_H

#include "menu2.h"
#include "Options.h"
#include "maze/Game.h"
#include <raylib.h>

typedef enum ScenesTypes {
    SCENE_MENU = 1,
    SCENE_BOARD,
    SCENE_OPTIONS,
} ScenesTypes;

class SceneHandler {
private:
    ScenesTypes tipos;
public:
    void *scene;
    ScenesTypes type;
    Menu* main;
    Options* optionss;
    Game* juego;
    void updateScene();
    void loadEscena( ScenesTypes type);
    void unloadEscena();
    void drawSceneHandler();
};

SceneHandler *initSceneHandler(void);



void freeScenehandler(SceneHandler *handler);


bool finishSceneHanlder(void);

#endif //EXAMPLES_SCENES_H
