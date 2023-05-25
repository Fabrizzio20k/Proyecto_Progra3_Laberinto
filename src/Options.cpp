#include "Options.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "iostream"

extern Global globalData;

using namespace std;
#define SONG1 "Megalovania "
#define SONG2 "MusumeOST 1"
#define SONG3 "MusumeOST 2"
#define SONG4 "Bad Apple"
#define OPTION_GAME_MODE_PVP "Player vs Player"
#define OPTION_GAME_MODE_PVIA "Player vs IA"
#define OPTION_GAME_MODE_IAVIA "IA vs IA"
static bool finished = false;
static const int32_t FONTSIZE = 24;
static int32_t internalPto = 0;
static GLMusic internalTheme = static_cast<GLMusic>(-1);
static GlMode internalMode = static_cast<GlMode>(-1);

static void resetValue(void);
static void drawTitle(void);
//static void drawOptionPtos(const Options *const options, const int32_t posY);
static void drawOptionTheme(const Options *const options, const int32_t posY);
static void drawOptionGameMode(const Options *const options, const int32_t posY);
//static void drawOptionFullScreen(const Options *const options, const int32_t posY);
//static void updateItemSelected(Options *const options);
static void closeOptions(void);
//static void changeValueItem(Options *const options);
//static void changePtos(void);
//static void updatePtos(void);
//static void initPtos(void);
//static void freePtos(void);
static void initMusic(void);
static void freeMusic(void);
static void updateItemSelected(Options *const options);
static void updateTheme( Options *const options);
static void updateThemeData();
static void updateMode(const Options *const options);
static void updateModeData(void);
static void initGameMode();
static void freeGameMode();
//static void updateFullScreen(const Options *const options);

// Variables globales validas solo en dicho archivo
static char *ptoData = NULL;
static char *musicData = NULL;
static char *modeData = NULL;

const static char *LEFT = "< ";
const static char *RIGHT = " >";
const static int32_t DIFF_LEFT = 60;
const static int32_t DIFF_RIGHT = 60;

Options *initOptions(void) {
    cout << "iniciando options" << endl;
    resetValue();
    //Options *options = static_cast<Options *>(malloc(sizeof(Options)));
    Options* options = new Options;
    if (options == NULL) {
        return NULL;
    }

    //initPtos();
    initMusic();
    initGameMode();

    options->item = ITEM_MUSIC;

    return options;
}


void Options::updateOPTIONS() {
    updateItemSelected(this);
    //changeValueItem(options);
    updateTheme(this);
    updateThemeData();
    updateMode(this);
    updateModeData();
    //updateFullScreen(options);
    closeOptions();
}


bool finishOptions(void) {
    return finished;
}
void Options::DrawOPTIONS() {
    int32_t posY = 100;
    drawTitle();
    //drawOptionPtos(options, posY);
    posY += FONTSIZE + 10;
    drawOptionTheme(this, posY);
    posY += FONTSIZE + 10;
    drawOptionGameMode(this, posY);
    posY += FONTSIZE + 10;
    //drawOptionFullScreen(options, posY);
}

void freeOptions2(Options *options) {
    if (options != NULL) {
        //freePtos();
        freeMusic();
        freeGameMode();
        free(options);
        options = NULL;
    }
}

static void resetValue() {
    finished = false;
}

static void drawTitle() {
    const int32_t middle = GetScreenWidth() / 2;
    const int32_t posX = middle - TextLength("Options") * (FONTSIZE / 2) / 2;

    DrawText("Options", posX, 10, FONTSIZE,  (Color){ 168, 159, 148, 255 });
}



static void drawOptionTheme(const Options *const options, const int32_t posY) {
    Color selected = options->item == ITEM_MUSIC ? (Color){224, 219, 205, 255 } : (Color){112, 107, 102, 255 };;
    DrawText("Theme:", DIFF_LEFT, posY, FONTSIZE, selected);
    DrawText(musicData, GetScreenWidth() - MeasureText(musicData, FONTSIZE) - DIFF_RIGHT, posY, FONTSIZE, selected);
}

static void drawOptionGameMode(const Options *const options, const int32_t posY) {
    Color selected = options->item == ITEM_GAME_MODE ? (Color){ 224, 219, 205, 255 } : (Color){ 112, 107, 102, 255 };;
    DrawText("GAME MODE:", DIFF_LEFT, posY, FONTSIZE, selected);
    DrawText(modeData, GetScreenWidth() - MeasureText(modeData, FONTSIZE) - DIFF_RIGHT, posY, FONTSIZE, selected);
}



static void closeOptions(void) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (!IsMusicStreamPlaying(globalData.music[internalTheme])){
            UnloadMusicStream(globalData.music[globalData.theme]);
            globalData.theme = internalTheme;
            globalData.resetMusic();
            PlayMusicStream(globalData.music[globalData.theme]);
        }
        finished = true;
    }
}

static void initMusic() {
    const int32_t size = 20;
    musicData = new char[size];
    musicData[size - 1] = '\0';
}
static void freeMusic() {
    free(musicData);
    musicData = NULL;
    internalTheme = static_cast<GLMusic>(-1);
}

static void initGameMode() {
    const int32_t size = 4;
    modeData = new char[size];
    modeData[size - 1] = '\0';
}

static void freeGameMode() {
    free(modeData);
    modeData = NULL;
    internalMode = static_cast<GlMode>(-1);
}
static void updateItemSelected(Options *const options) {
    const int32_t min = (int32_t) ITEM_PTOS;
    const int32_t max = (int32_t) ITEM_FULLSCREEN;
    if (IsKeyPressed(KEY_UP)) {
        PlaySound(globalData.leftSound);
        const int32_t value = options->item - 1;
        if (value >= min) {
            options->item = static_cast<OptionItems>(options->item - 1);
        } else {
            options->item = (OptionItems) max;
        }
    } else if (IsKeyPressed(KEY_DOWN)) {
        PlaySound(globalData.leftSound);
        const int32_t value = options->item + 1;
        if (value <= max) {
            options->item = static_cast<OptionItems>(options->item + 1);
        } else {
            options->item = (OptionItems) min;
        }
    }
}
static void updateTheme(Options *const options) {
    if (options->item == ITEM_MUSIC) {
        const auto minTheme = (int32_t) MUSIC_1;
        const auto maxTheme = (int32_t) MUSIC_4;
        const auto theme = (int32_t) temas;
        if (IsKeyPressed(KEY_LEFT) && theme > minTheme) {
            temas = static_cast<GLMusic>(temas - 1);
        } else if (IsKeyPressed(KEY_RIGHT) && theme < maxTheme) {
            temas = static_cast<GLMusic>(temas + 1);
        }
    }
}

static void updateThemeData() {
    if (internalTheme != temas ) {
        internalTheme = temas;
        cout << (int32_t)internalTheme;
        const auto minTheme = (int32_t) MUSIC_1;
        const auto maxTheme = (int32_t) MUSIC_4;

        strcpy(musicData, "");
        if ((int32_t)internalTheme > minTheme) {
            strcat(musicData, LEFT);
        }

        switch (internalTheme) {
            case MUSIC_1:
                strcat(musicData, SONG1);
                break;
            case MUSIC_2:
                strcat(musicData, SONG2);
                break;
            case MUSIC_3:
                strcat(musicData, SONG3);
                break;
            case MUSIC_4:
                strcat(musicData, SONG4);
                break;
        }

        if ((int32_t)internalTheme < maxTheme) {
            strcat(musicData, RIGHT);
        }
    }
}
static void updateMode(const Options *const options) {
    if (options->item == ITEM_GAME_MODE) {
        const auto minMode = (int32_t) PLAYER_VS_PLAYER;
        const auto maxMode = (int32_t) BOT_VS_BOT;
        const auto mode = (int32_t) globalData.mode;
        if (IsKeyPressed(KEY_LEFT) && mode > minMode) {
            globalData.mode = static_cast<GlMode>(globalData.mode - 1);
        } else if (IsKeyPressed(KEY_RIGHT) && mode < maxMode) {
            globalData.mode = static_cast<GlMode>(globalData.mode + 1);
        }
    }
}


static void updateModeData() {
    if (internalMode != globalData.mode) {
        internalMode = globalData.mode;
        strcpy(modeData, "");
        const auto minMode = (int32_t) PLAYER_VS_PLAYER;
        const auto maxMode = (int32_t) BOT_VS_BOT;
        if ((int32_t)internalMode > minMode) {
            strcat(modeData, LEFT);
        }
        switch (internalMode) {
            case PLAYER_VS_PLAYER:
                strcat(modeData, OPTION_GAME_MODE_PVP);
                globalData.dificultad = BFS_BOT;
                break;
            case PLAYER_VS_BOT:
                strcat(modeData, OPTION_GAME_MODE_PVIA);
                globalData.dificultad = DFS_BOT;
                break;
            case BOT_VS_BOT:
                strcat(modeData, OPTION_GAME_MODE_IAVIA);
                break;
        }
        if ((int32_t)internalMode < maxMode) {
            strcat(modeData, RIGHT);
        }
    }
}



