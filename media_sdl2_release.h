//
// Created by alcicer on 6/16/2022.
//

#ifndef TETRIS_MEDIA_SDL2_RELEASE_H
#define TETRIS_MEDIA_SDL2_RELEASE_H

#include <iostream>
#include <array>
#include <iomanip>
#include <cassert>
#include <thread>
#include "media.h"
#include "SDL.h"
#include "SDL_image.h"

class media_sdl2_release : public media {
public:

    media_sdl2_release();

    void refreshScreen() override;

    void setLineScore(unsigned int score) override;

    void setStatistics(int index, unsigned int value) override;

    void setLevel(unsigned int level) override;

    void setCurrentScore(unsigned int score) override;

    void setTopScore(unsigned int score) override;

    void createMino(int x, int y, unsigned int type) override;

    void clearMino(int x, int y) override;

    void setNextBlock(unsigned int type) override;

    void clearNextBlock() override;

    void gameOver() override;

    void playMoveMusic() override {};

    void playRotateMusic() override {};

    void playLandingMusic() override {};

    void playTetrisMusic() override {};

    void playClearingMusic() override {};

    void playLevelUpMusic() override {};

    void playGameOverMusic() override {};

    void playEntryMusic() override {};

    void stopMusic() override {};

private:
    bool init();

    void setDigitValue(int x, int y, int width, int height, int widthGap, unsigned value,
                       int numberOfDigits) const;

    SDL_Window *gameWindow{};
    SDL_Surface *gameSurface{};
    int SCREEN_WIDTH = 672;
    int SCREEN_HEIGHT = 543;

    static const int ROWS = 20;
    static const int COLUMNS = 10;

    /** images */
    SDL_Surface *backgroundSurface{};
    std::array<SDL_Surface *, 10> digits{};
    SDL_Surface *blackMino{};
    std::array<SDL_Surface *, 3> minos{};
    SDL_Surface *tetrisDead{};

    /** coordinates and dimensions */
    int linesX = 410;
    int linesY = 25;
    int linesHeight = 23;
    int linesWidth = 20;

    int statX = 158;
    int statY = 210;
    int statHeight = 20;
    int statWidth = 20;
    int statGap = 42;

    int levelX = 552;
    int levelY = 412;
    int levelHeight = 22;
    int levelWidth = 20;

    int scoreX = 508;
    int topScoreY = 72;
    int currentScoreY = 136;
    int scoreWidth = 22;
    int scoreHeight = 22;

    int gameBeginX = 254;
    int gameBeginY = 94;
    int minoLength = 21;

    int nextBeginX = 509;
    int nextBeginY = 265;

    [[nodiscard]] static const char *GetError() {
        return SDL_GetError();
    }
};

#endif //TETRIS_MEDIA_SDL2_RELEASE_H
