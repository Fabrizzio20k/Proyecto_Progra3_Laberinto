#include "scenes.h"
#include <stdlib.h>
#include "iostream"
#include "maze/Game.h"
using namespace std;
static bool finished = false;

SceneHandler *initSceneHandler() {
    /// RESERVANDO ESPACIO DE MEMORIA AL HANDLER
    finished = false;
    SceneHandler* handler = new SceneHandler;
    handler->scene = NULL;
    handler->loadEscena(SCENE_MENU);
    return handler;
}



void freeScenehandler(SceneHandler *handler) {
    if (handler != NULL) {
        cout << "maze eliminado" << endl;
        handler->unloadEscena();
        free(handler);
        handler = NULL;
    }
}

bool finishSceneHanlder(void) {
    return finished;
}

void SceneHandler::loadEscena( ScenesTypes types) {
    unloadEscena();
    tipos = types;
    switch (types) {
        case SCENE_MENU:
            cout << "MENU";
            main = initMenu();
            break;
        case SCENE_BOARD:
            cout << "iniciando juego";
            juego = initGame();
            break;
        case SCENE_OPTIONS:
            cout << "OPTIONS";
            optionss = initOptions();
    }
}




void SceneHandler::unloadEscena() {
    switch (tipos) {
        case SCENE_MENU:
            cout << "cerrando menu XDDDD";
            freeMenu2(main);
            break;
        case SCENE_BOARD:
            cout << "Maze cerrado";
            freeGame2(juego);
            break;
        case SCENE_OPTIONS:
            freeOptions2(optionss);
            cout << "cerrar options";
    }
}

void SceneHandler::updateScene() {
    const OptionEvent event = finishMenu();
    switch (tipos) {
        case SCENE_MENU:
            main->updateMENU();
            if (event!= OPT_EMPTY) {
                if (event == OPT_START) {
                    loadEscena(SCENE_BOARD);
                } else if (event == OPT_OPTIONS) {
                    loadEscena(SCENE_OPTIONS);
                } else if (event == OPT_EXIT) {
                    finished = true;
                }
            }
            break;
        case SCENE_BOARD:
            juego->updateGAMES();
            if (finishGAME()) {
                loadEscena( SCENE_MENU);
            }
            break;
        case SCENE_OPTIONS:
            optionss->updateOPTIONS();
            if (finishOptions()) {
                loadEscena( SCENE_MENU);

            }
    }
}
/// USANDO
void SceneHandler::drawSceneHandler() {
    switch (tipos) {
        case SCENE_MENU:
            main->drawMENU();
            break;
        case SCENE_BOARD:
            juego->DRAWGAME();
            break;
        case SCENE_OPTIONS:
            optionss->DrawOPTIONS();
            break;
    }
}




