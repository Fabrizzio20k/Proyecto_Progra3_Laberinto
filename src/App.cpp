//
// Created by Jesus on 16/02/2023.
//

#include "App.h"
#include <stdlib.h>
#include "iostream"
static bool finished = false;
static bool showFPS = false;

static void settingApp(void);
static void updateFullScreen(void);

static void freeInternalApp(App *app);

Global globalData;

// FUNCIONES PUBLICAS
App *initApp() {
    finished = false;
    App* app = new App;
    if (app == NULL) {
        return NULL;
    }
    InitAudioDevice();
    initGlobal(&globalData);
    settingApp();
    SetWindowPosition(640,360);
    //app->sounds.push_back(sond2);
    app->sceneHandler = initSceneHandler();
    return app;
}

void runApp(App *const app) {
    PlayMusicStream(globalData.music[globalData.theme]);
    bool pause = false;

    while (!WindowShouldClose() && !finished) {
        UpdateMusicStream(globalData.music[globalData.theme]);
        if (IsKeyPressed(KEY_P))
        {
            pause = !pause;
            if (pause) PauseMusicStream(globalData.music[globalData.theme]);
            else ResumeMusicStream(globalData.music[globalData.theme]);
        }
        app->updateApp();
        app->drawApp();
    }
    std::cout << "cerrado app" << std::endl;
}

void freeApp(App **app) {
    if (*app != NULL) {
        freeGlobal(&globalData);
        freeInternalApp(*app);
        free(*app);
        *app = NULL;
#ifdef PONG_DEBUG
        TraceLog(LOG_INFO, PONG_APP_DELETED);
#endif
    }
}



static void settingApp() {
    InitWindow(globalData.screen_width, globalData.screen_height , "MARISA MAZE");
    HideCursor();
    Image iconKAWAI = LoadImage("../textures/icon_windowscompress.png");
    SetWindowIcon(iconKAWAI);
    SetExitKey(KEY_F8);
    SetTargetFPS(500);
}


void App::updateApp() {
    getScene()->updateScene();
    finished = finishSceneHanlder();
}

void App::drawApp() {
    BeginDrawing();
    ClearBackground(BLACK);
    sceneHandler->drawSceneHandler();
    EndDrawing();
}

static void freeInternalApp(App *const app) {
    freeScenehandler(app->sceneHandler);
    CloseAudioDevice();
    CloseWindow();
}

static void updateFullScreen(void) {
    if (globalData.fullScreen && !IsWindowFullscreen()) {
        ToggleFullscreen();
    } else if (!globalData.fullScreen && IsWindowFullscreen()) {
        ToggleFullscreen();
    }
}

