//
// Created by Jesus on 16/02/2023.
//

#ifndef EXAMPLES_APP_H
#define EXAMPLES_APP_H

#include "scenes.h"
#include "vector"



class App {
public:
    SceneHandler *sceneHandler;
    void updateApp();
    void drawApp();
    [[nodiscard]] SceneHandler* getScene() const{
        return sceneHandler;
    }
};

App *initApp();

void runApp(App *const app);
void freeApp(App **app);

#endif //EXAMPLES_APP_H
