//
// Created by alcicer on 6/15/2022.
//
#include <sstream>
#include "media_sdl2.h"

media_sdl2::media_sdl2() {
    init();
    SDL_BlitScaled(backgroundSurface, nullptr, gameSurface, nullptr);
}

bool media_sdl2::init() {

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << GetError() << std::endl;
        return false;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << GetError() << std::endl;
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

    if ((entryMusic = Mix_LoadWAV(entryMusicPath)) == nullptr) {
        std::cout << "Failed to load entry music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if ((rotateMusic = Mix_LoadWAV(rotateMusicPath)) == nullptr) {
        std::cout << "Failed to load rotate music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if ((moveMusic = Mix_LoadWAV(moveMusicPath)) == nullptr) {
        std::cout << "Failed to load move music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if ((landingMusic = Mix_LoadWAV(landingMusicPath)) == nullptr) {
        std::cout << "Failed to load land music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if ((gameOverMusic = Mix_LoadWAV(gameOverMusicPath)) == nullptr) {
        std::cout << "Failed to load game over music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if ((tetrisMusic = Mix_LoadWAV(tetrisMusicPath)) == nullptr) {
        std::cout << "Failed to load tetris music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if ((tetrisClearMusic = Mix_LoadWAV(tetrisClearMusicPath)) == nullptr) {
        std::cout << "Failed to load tetris clearLines music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if ((tetrisLevelUpMusic = Mix_LoadWAV(tetrisLevelUpMusicPath)) == nullptr) {
        std::cout << "Failed to load level up music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if ((backgroundSurface = IMG_Load(backgroundImagePath)) == nullptr) {
        std::cout << "Failed to load backgroundImage image!" << GetError() << std::endl;
        return false;
    }

    if ((digits[0] = IMG_Load((digitImagePathPrefix + (std::string) "0.png").c_str())) == nullptr) {
        std::cout << "Failed to load digit0 image!" << GetError() << std::endl;
        return false;
    }

    if ((digits[1] = IMG_Load((digitImagePathPrefix + (std::string) "1.png").c_str())) == nullptr) {
        std::cout << "Failed to load digit1 image!" << GetError() << std::endl;
        return false;
    }

    if ((digits[2] = IMG_Load((digitImagePathPrefix + (std::string) "2.png").c_str())) == nullptr) {
        std::cout << "Failed to load digit2 image!" << GetError() << std::endl;
        return false;
    }

    if ((digits[3] = IMG_Load((digitImagePathPrefix + (std::string) "3.png").c_str())) == nullptr) {
        std::cout << "Failed to load digit3 image!" << GetError() << std::endl;
        return false;
    }

    if ((digits[4] = IMG_Load((digitImagePathPrefix + (std::string) "4.png").c_str())) == nullptr) {
        std::cout << "Failed to load digit4 image!" << GetError() << std::endl;
        return false;
    }

    if ((digits[5] = IMG_Load((digitImagePathPrefix + (std::string) "5.png").c_str())) == nullptr) {
        std::cout << "Failed to load digit5 image!" << GetError() << std::endl;
        return false;
    }

    if ((digits[6] = IMG_Load((digitImagePathPrefix + (std::string) "6.png").c_str())) == nullptr) {
        std::cout << "Failed to load digit6 image!" << GetError() << std::endl;
        return false;
    }

    if ((digits[7] = IMG_Load((digitImagePathPrefix + (std::string) "7.png").c_str())) == nullptr) {
        std::cout << "Failed to load digit7 image!" << GetError() << std::endl;
        return false;
    }

    if ((digits[8] = IMG_Load((digitImagePathPrefix + (std::string) "8.png").c_str())) == nullptr) {
        std::cout << "Failed to load digit8 image!" << GetError() << std::endl;
        return false;
    }

    if ((digits[9] = IMG_Load((digitImagePathPrefix + (std::string) "9.png").c_str())) == nullptr) {
        std::cout << "Failed to load digit9 image!" << GetError() << std::endl;
        return false;
    }

    if ((blackMino = IMG_Load(minoBlackPath)) == nullptr) {
        std::cout << "Failed to load black mino image!" << GetError() << std::endl;
        return false;
    }

    if ((tetrisDead = IMG_Load(tetrisDeadPath)) == nullptr) {
        std::cout << "Failed to load tetris dead image!" << GetError() << std::endl;
        return false;
    }

    if ((minos[0] = IMG_Load(mino0Path)) == nullptr) {
        std::cout << "Failed to load mino0 image!" << GetError() << std::endl;
        return false;
    }

    if ((minos[1] = IMG_Load(mino1Path)) == nullptr) {
        std::cout << "Failed to load mino1 image!" << GetError() << std::endl;
        return false;
    }
    if ((minos[2] = IMG_Load(mino2Path)) == nullptr) {
        std::cout << "Failed to load mino2 image!" << GetError() << std::endl;
        return false;
    }
    return true;
}

void media_sdl2::refreshScreen() {
    SDL_UpdateWindowSurface(gameWindow);
}

void media_sdl2::setLineScore(unsigned int score) {
    setDigitValue(linesX, linesY, linesWidth, linesHeight, linesWidth, score, 3);
}

void media_sdl2::setStatistics(int index, unsigned int value) {
    setDigitValue(statX, statY + (index * statGap), statWidth, statHeight, statWidth, value, 2);
}

void media_sdl2::setLevel(unsigned int level) {
    setDigitValue(levelX, levelY, levelWidth, levelHeight, levelWidth, level, 2);
}

void media_sdl2::setCurrentScore(unsigned int score) {
    setDigitValue(scoreX, currentScoreY, scoreWidth, scoreHeight, scoreWidth, score, 6);
}

void media_sdl2::setTopScore(unsigned int score) {
    setDigitValue(scoreX, topScoreY, scoreWidth, scoreHeight, scoreWidth, score, 6);
}

void media_sdl2::createMino(int x, int y, unsigned int type) {
    type %= minos.size();
    SDL_Rect rect = {gameBeginX + (y * minoLength), gameBeginY + (x * minoLength), minoLength, minoLength};
    assert(minos.size() > type && "mino type greater than expected");
    SDL_BlitScaled(minos[type], nullptr, gameSurface, &rect);
}

void media_sdl2::clearMino(int x, int y) {
    SDL_Rect rect = {gameBeginX + (y * minoLength), gameBeginY + (x * minoLength), minoLength, minoLength};
    SDL_BlitScaled(blackMino, nullptr, gameSurface, &rect);
}

void media_sdl2::setNextBlock(unsigned int type) {
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

void media_sdl2::gameOver() {
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

void media_sdl2::playMoveMusic() {
    playMusic(moveMusic);
}

void media_sdl2::playRotateMusic() {
    playMusic(rotateMusic);
}

void media_sdl2::playLandingMusic() {
    playMusic(landingMusic);
}

void media_sdl2::playTetrisMusic() {
    playMusic(tetrisMusic);
}

void media_sdl2::playClearingMusic() {
    playMusic(tetrisClearMusic);
}

void media_sdl2::playLevelUpMusic() {
    playMusic(tetrisLevelUpMusic);
}

void media_sdl2::playGameOverMusic() {
    playMusic(gameOverMusic);
}

void media_sdl2::playEntryMusic() {
    playMusic(entryMusic, -1);
}

void media_sdl2::stopMusic() {
    Mix_HaltChannel(-1);
}

void media_sdl2::setDigitValue(int x, int y, int width, int height, int widthGap, unsigned int value,
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

void media_sdl2::playMusic(Mix_Chunk *chunk, int loops) {
    Mix_PlayChannel(-1, chunk, loops);
}

