//
// Created by alcicer on 6/15/2022.
//

#ifndef TETRIS_MEDIA_SDL2_H
#define TETRIS_MEDIA_SDL2_H

#include <iostream>
#include <array>
#include <iomanip>
#include <cassert>
#include <thread>
#include "media.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

class media_sdl2 : public media {
public:

    media_sdl2();

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

    void playMoveMusic() override;

    void playRotateMusic() override;

    void playLandingMusic() override;

    void playTetrisMusic() override;

    void playClearingMusic() override;

    void playLevelUpMusic() override;

    void playGameOverMusic() override;

    void playEntryMusic() override;

    void stopMusic() override;

private:
    bool init();

    void setDigitValue(int x, int y, int width, int height, int widthGap, unsigned value,
                       int numberOfDigits) const;

    static void playMusic(Mix_Chunk *chunk, int loops = 0);

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

    /** musics */
    Mix_Chunk *entryMusic{};
    Mix_Chunk *rotateMusic{};
    Mix_Chunk *moveMusic{};
    Mix_Chunk *landingMusic{};
    Mix_Chunk *gameOverMusic{};
    Mix_Chunk *tetrisMusic{};
    Mix_Chunk *tetrisClearMusic{};
    Mix_Chunk *tetrisLevelUpMusic{};

    /** paths */
    const char *backgroundImagePath = R"(D:\Users\alcicer\CLionProjects\tetris\resources\background.png)";
    const char *entryMusicPath = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetris-gameboy-02.wav)";
    const char *rotateMusicPath = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetrisTurn.wav)";
    const char *moveMusicPath = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetrisMove.wav)";
    const char *landingMusicPath = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetrisLand.wav)";
    const char *gameOverMusicPath = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetrisGameOver.wav)";
    const char *tetrisMusicPath = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetris.wav)";
    const char *tetrisClearMusicPath = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetrisClear.wav)";
    const char *tetrisLevelUpMusicPath = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetrisLevelUp.wav)";
    const char *digitImagePathPrefix = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetris)";
    const char *minoBlackPath = R"(D:\Users\alcicer\CLionProjects\tetris\resources\black.png)";
    const char *mino0Path = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetrisNES0.png)";
    const char *mino1Path = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetrisNES1.png)";
    const char *mino2Path = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetrisNES2.png)";
    const char *tetrisDeadPath = R"(D:\Users\alcicer\CLionProjects\tetris\resources\tetrisDead.png)";

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

#endif //TETRIS_MEDIA_SDL2_H
