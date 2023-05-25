//
// Created by Jesus on 16/02/2023.
//

#ifndef EXAMPLES_OPTIONS_H
#define EXAMPLES_OPTIONS_H
#include <raylib.h>
#include "global.h"


typedef enum OptionItems {
    ITEM_PTOS = 0,
    ITEM_MUSIC,
    ITEM_GAME_MODE,
    ITEM_FULLSCREEN,
} OptionItems;
class Options {
public:
    OptionItems item;
    void updateOPTIONS();
    void DrawOPTIONS();
};

Options *initOptions(void);
void freeOptions2(Options *options);
bool finishOptions(void);


#endif //EXAMPLES_OPTIONS_H
