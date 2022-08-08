//
// Created by alcicer on 6/3/2022.
//

#ifndef TETRIS_WINDOW_H
#define TETRIS_WINDOW_H

#include <array>
#include "SDL_surface.h"
#include "SDL_video.h"
#include "blocks.h"
#include "game.h"
#include "media.h"
#include "rest_service.h"

class window {
public:
    static window &getInstance(media *m);

    void start();

    void drawBoard() const;

    void sendStatus();

    void reset();

private:
    explicit window(media *m);

    void processMerging(std::vector<int> &lines);

    void eventLoop();

    std::unique_ptr<media> md;
    static const int ROWS = 20;
    static const int COLUMNS = 10;
    game gm{ROWS, COLUMNS};
    bool started = false;
    bool paused = false;
    bool gg = false;
    unsigned level;

    rest_service rs;
};

#endif //TETRIS_WINDOW_H
