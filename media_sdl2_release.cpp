//
// Created by alcicer on 6/16/2022.
//

#include <sstream>
#include "media_sdl2_release.h"
#include "resources/resources.h"

media_sdl2_release::media_sdl2_release() {
    init();
    SDL_BlitScaled(backgroundSurface, nullptr, gameSurface, nullptr);
}

bool media_sdl2_release::init() {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << GetError() << std::endl;
        return false;
    }

    if ((gameWindow = SDL_CreateWindow("TETRIS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                       SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << GetError() << std::endl;
        return false;
    }

    if ((gameSurface = SDL_GetWindowSurface(gameWindow)) == nullptr) {
        std::cout << "Surface could not be created! SDL_Error: " << GetError() << std::endl;
        return false;
    }

    SDL_RWops *rw = SDL_RWFromMem(background_png, background_png_len);
    if ((backgroundSurface = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load backgroundImage image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetris0_png, tetris0_png_len);
    if ((digits[0] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load digit0 image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetris1_png, tetris1_png_len);
    if ((digits[1] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load digit1 image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetris2_png, tetris2_png_len);
    if ((digits[2] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load digit2 image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetris3_png, tetris3_png_len);
    if ((digits[3] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load digit3 image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetris4_png, tetris4_png_len);
    if ((digits[4] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load digit4 image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetris5_png, tetris5_png_len);
    if ((digits[5] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load digit5 image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetris6_png, tetris6_png_len);
    if ((digits[6] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load digit6 image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetris7_png, tetris7_png_len);
    if ((digits[7] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load digit7 image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetris8_png, tetris8_png_len);
    if ((digits[8] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load digit8 image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetris9_png, tetris9_png_len);
    if ((digits[9] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load digit9 image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(black_png, black_png_len);
    if ((blackMino = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load black mino image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetrisDead_png, tetrisDead_png_len);
    if ((tetrisDead = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load tetris dead image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetrisNES0_png, tetrisNES0_png_len);
    if ((minos[0] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load mino0 image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetrisNES1_png, tetrisNES1_png_len);
    if ((minos[1] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load mino1 image!" << GetError() << std::endl;
        return false;
    }

    rw = SDL_RWFromMem(tetrisNES2_png, tetrisNES2_png_len);
    if ((minos[2] = IMG_Load_RW(rw, 1)) == nullptr) {
        std::cout << "Failed to load mino2 image!" << GetError() << std::endl;
        return false;
    }
    return true;
}

void media_sdl2_release::refreshScreen() {
    SDL_UpdateWindowSurface(gameWindow);
}

void media_sdl2_release::setLineScore(unsigned int score) {
    setDigitValue(linesX, linesY, linesWidth, linesHeight, linesWidth, score, 3);
}

void media_sdl2_release::setStatistics(int index, unsigned int value) {
    setDigitValue(statX, statY + (index * statGap), statWidth, statHeight, statWidth, value, 2);
}

void media_sdl2_release::setLevel(unsigned int level) {
    setDigitValue(levelX, levelY, levelWidth, levelHeight, levelWidth, level, 2);
}

void media_sdl2_release::setCurrentScore(unsigned int score) {
    setDigitValue(scoreX, currentScoreY, scoreWidth, scoreHeight, scoreWidth, score, 6);
}

void media_sdl2_release::setTopScore(unsigned int score) {
    setDigitValue(scoreX, topScoreY, scoreWidth, scoreHeight, scoreWidth, score, 6);
}

void media_sdl2_release::createMino(int x, int y, unsigned int type) {
    type %= minos.size();
    SDL_Rect rect = {gameBeginX + (y * minoLength), gameBeginY + (x * minoLength), minoLength, minoLength};
    assert(minos.size() > type && "mino type greater than expected");
    SDL_BlitScaled(minos[type], nullptr, gameSurface, &rect);
}

void media_sdl2_release::clearMino(int x, int y) {
    SDL_Rect rect = {gameBeginX + (y * minoLength), gameBeginY + (x * minoLength), minoLength, minoLength};
    SDL_BlitScaled(blackMino, nullptr, gameSurface, &rect);
}

void media_sdl2_release::setNextBlock(unsigned int type) {
    int beginX = nextBeginX;
    int beginY = nextBeginY;

    bool bl[4][4] = {};

    switch (type) {
        case 0:
            beginX += minoLength / 2;
            bl[1][0] = bl[1][1] = bl[1][2] = bl[2][1] = true;
            break;
        case 1:
            beginX += minoLength / 2;
            bl[1][0] = bl[1][1] = bl[1][2] = bl[2][2] = true;
            break;
        case 2:
            beginX += minoLength / 2;
            bl[1][0] = bl[1][1] = bl[2][1] = bl[2][2] = true;
            break;
        case 3:
            bl[1][1] = bl[1][2] = bl[2][1] = bl[2][2] = true;
            break;
        case 4:
            beginX += minoLength / 2;
            bl[1][1] = bl[1][2] = bl[2][0] = bl[2][1] = true;
            break;
        case 5:
            beginX += minoLength / 2;
            bl[1][0] = bl[1][1] = bl[1][2] = bl[2][0] = true;
            break;
        case 6:
            beginY -= minoLength / 2;
            bl[2][0] = bl[2][1] = bl[2][2] = bl[2][3] = true;
            break;
        default:
            return;
    }

    SDL_Rect rect = {nextBeginX, nextBeginY, minoLength * 4, minoLength * 4};
    SDL_BlitScaled(blackMino, nullptr, gameSurface, &rect);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (bl[i][j]) {
                rect = {beginX + (j * minoLength), beginY + (i * minoLength), minoLength, minoLength};
                SDL_BlitScaled(minos[type % minos.size()], nullptr, gameSurface, &rect);
            }
        }
    }
}

void media_sdl2_release::clearNextBlock() {
    SDL_Rect rect = {nextBeginX, nextBeginY, minoLength * 4, minoLength * 4};
    SDL_BlitScaled(blackMino, nullptr, gameSurface, &rect);
}

void media_sdl2_release::gameOver() {
    using namespace std::chrono_literals;
    playGameOverMusic();
    SDL_Rect rect;
    for (int i = 0; i < ROWS; ++i) {
        rect = {gameBeginX, gameBeginY + (i * minoLength), minoLength * COLUMNS, minoLength};
        SDL_BlitScaled(tetrisDead, nullptr, gameSurface, &rect);
        std::this_thread::sleep_for(50ms);
        SDL_UpdateWindowSurface(gameWindow);
    }
}

void media_sdl2_release::setDigitValue(int x, int y, int width, int height, int widthGap, unsigned int value,
                                       int numberOfDigits) const {
    std::ostringstream dt;
    dt << std::setfill('0') << std::setw(numberOfDigits) << value;
    std::string dts = dt.str();
    assert(dts.length() >= numberOfDigits && "number of digits greater than expected");

    for (int i = 0; i < numberOfDigits; ++i) {
        SDL_Rect rect = {x + (widthGap * i), y, width, height};
        SDL_BlitScaled(digits[dts[i] - 48], nullptr, gameSurface, &rect);
    }
}
