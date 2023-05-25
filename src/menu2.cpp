#include "menu2.h"

#include <stdlib.h>
#include <stdint.h>

extern Global globalData;

static OptionEvent onOptionEvent = OPT_EMPTY;
static void drawTitle();

Menu *initMenu() {
    onOptionEvent = OPT_EMPTY;
    Menu* menu = new Menu;

    menu->option = OPT_START;

    return menu;
}

void Menu::updateMENU() {
    updateMENUOPTIONS();
    if (IsKeyPressed(KEY_ENTER)) {
        if (option == OPT_START) {
            onOptionEvent = OPT_START;      // ACTUALIZA EL EVENTO QUE SE ABRE
        }
        else if (option == OPT_OPTIONS) {
            onOptionEvent = OPT_OPTIONS;
        }
        else if (option == OPT_EXIT) {
            onOptionEvent = OPT_EXIT;
        }
    }
}
void Menu::drawMENU() {
    drawTitle();
    drawMENUOPTIONS();
}

void freeMenu2(Menu *menu) {
    if (menu != NULL) {
        free(menu);
        menu = NULL;
    }
}
OptionEvent finishMenu(void) {
    return onOptionEvent;   // RETORNA EL EVENTO
}
void Menu::drawMENUOPTIONS() {
    const int32_t middleWidth = GetScreenWidth() / 2;
    const int32_t middleHeight = GetScreenHeight() / 2;
    const int32_t fontSize = 24;
    const int32_t posY = middleHeight + 45;
    const int32_t posXStart = middleWidth - MeasureText("START", fontSize) / 2;
    const int32_t posXOptions = middleWidth - MeasureText("OPTIONS", fontSize) / 2;
    const int32_t posXExit = middleWidth - MeasureText("EXIT", fontSize) / 2;

    const Color startColor = (option == OPT_START) ? (Color){ 224, 219, 205, 255 } : (Color){ 112, 107, 102, 255 };
    const Color optionsColor = (option == OPT_OPTIONS) ? (Color){ 224, 219, 205, 255 } : (Color){ 112, 107, 102, 255 };
    const Color endColor = (option == OPT_EXIT) ? (Color){ 224, 219, 205, 255 } : (Color){ 112, 107, 102, 255 };

    DrawText("START", posXStart, posY, fontSize, startColor);
    DrawText("OPTIONS", posXOptions, posY + fontSize + 5, fontSize, optionsColor);
    DrawText("EXIT", posXExit, posY + (fontSize * 2) + 10, fontSize, endColor);
}
void Menu::updateMENUOPTIONS() {
    const auto min = (int32_t) OPT_START;
    const auto max = (int32_t) OPT_EXIT;
    if (IsKeyPressed(KEY_UP)) {
        const int32_t value = option - 1;
        if (value >= min) {
            option = static_cast<OptionEvent>(option - 1);
        } else {
            option = OPT_EXIT;
        }
    } else if (IsKeyPressed(KEY_DOWN)) {
        const int32_t value = option + 1;
        if (value <= max) {
            option = static_cast<OptionEvent>(option + 1);
        } else {
            option = OPT_START;
        }
    }
}




static void drawTitle() {
    const int32_t fontSize = 128;
    const int32_t middle = GetScreenWidth() / 2;
    const int32_t titleLen = MeasureText("MAZE", fontSize);
    const int32_t posX = middle - titleLen / 2;
    const int32_t posYBase = 20;
    const int32_t posY = 30;
    const int32_t height = 15;
    DrawRectangle(posX, posYBase + 20, titleLen, height, (Color){ 168, 159, 148, 255 });
    DrawText("MAZE", posX, posYBase + posY, fontSize, (Color){ 112, 107, 102, 255 });
    DrawRectangle(posX, posYBase + fontSize + 10, titleLen, height, (Color){ 168, 159, 148, 255 });
}

