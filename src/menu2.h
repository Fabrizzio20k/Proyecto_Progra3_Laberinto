//
// Created by Jesus on 15/02/2023.
//

#ifndef EXAMPLES_MENU2_H
#define EXAMPLES_MENU2_H

#include "global.h"

class Menu {
public:
    OptionEvent option;
    void updateMENU();
    void updateMENUOPTIONS();
    void drawMENU();
    void drawMENUOPTIONS();
};

Menu *initMenu(void);
void freeMenu2(Menu *menu);
OptionEvent finishMenu(void);

#endif //EXAMPLES_MENU2_H
