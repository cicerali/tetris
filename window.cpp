//
// Created by alcicer on 6/3/2022.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "window.h"
#include "SDL.h"

window &window::getInstance(media *m) {
    static window instance(m);
    return instance;
}

window::window(media *m) {
    md = std::unique_ptr<media>(m);
    level = gm.getLevel();
}

void window::reset() {
    started = false;
    paused = false;
    gg = false;
    gm = {ROWS, COLUMNS};
    level = gm.getLevel();
    gm.start();

    md->clearNextBlock();
    md->setLineScore(0);
    for (int i = 0; i < 7; ++i) {
        md->setStatistics(i, 0);
    }
    md->setLevel(0);
    md->setTopScore(0);
    md->setCurrentScore(0);

    md->playEntryMusic();
    drawBoard();
    sendStatus();
}

void window::start() {
    reset();
    rs.start();
    eventLoop();
}

void window::eventLoop() {

    auto begin = std::chrono::steady_clock::now();
    decltype(begin) end;
    auto epsilon = 0.0005;
    auto tick = gm.getSpeed();
    std::chrono::duration<double> diff{};
    SDL_Event e;
    int tickRes;
    bool send_gg = true;
    std::vector<int> lines;
    __begin__:
    while (true) {
        e = {};
        SDL_WaitEventTimeout(&e, 10);

        if (e.type == SDL_QUIT) {
            std::cout << "User typed quit" << std::endl;
            break;
        }

        if ((e.type == SDL_KEYDOWN || e.type == rs.ev.commandEvent) && e.key.keysym.scancode == SDL_SCANCODE_N) {
            std::cout << "User typed for new game" << std::endl;
            reset();
            send_gg = true;
            goto __begin__;
        }

        if ((e.type == SDL_KEYDOWN || e.type == rs.ev.commandEvent) && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
            paused = !paused;
            sendStatus();
            continue;
        }
        if (paused || gg) {
            if (gg && send_gg) {
                send_gg = false;
                sendStatus();
            }
            continue;
        }
        if (started) {
            end = std::chrono::steady_clock::now();
            diff = end - begin;
            if (diff.count() + epsilon >= tick) {
                tickRes = gm.doTick(lines);
                if (tickRes < 0) { /** block has minos above the sky, GAME OVER */
                    md->gameOver();
                    gg = true;
                } else if (tickRes == 0) { /** block landed to board, set next block */
                    processMerging(lines);
                } else { /** block moved down one square */
                    drawBoard();
                    sendStatus();
                }
                begin = end;
                tick = gm.getSpeed();
            }
        }
        if (e.type == SDL_KEYDOWN || e.type == rs.ev.commandEvent) {
            if (started && !gg) {
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_A: /** rotate the block counterclockwise */
                        if (gm.processCommand(command::ROTATE_COUNTER_CLOCKWISE) == movement_status::ROTATE_SUCCESS) {
                            md->playRotateMusic();
                        }
                        break;
                    case SDL_SCANCODE_S: /** rotate the block clockwise */
                    case SDL_SCANCODE_UP:
                        if (gm.processCommand(command::ROTATE_CLOCKWISE) == movement_status::ROTATE_SUCCESS) {
                            md->playRotateMusic();
                        }
                        break;
                    case SDL_SCANCODE_LEFT: /** move the block left 1 square */
                        if (gm.processCommand(command::MOVE_LEFT) == movement_status::MOVEMENT_SUCCESS) {
                            md->playMoveMusic();
                        }
                        break;
                    case SDL_SCANCODE_RIGHT: /** move the block right 1 square */
                        if (gm.processCommand(command::MOVE_RIGHT) == movement_status::MOVEMENT_SUCCESS) {
                            md->playMoveMusic();
                        }
                        break;
                    case SDL_SCANCODE_DOWN: /** increase the block speed */
                        gm.processCommand(command::MOVE_DOWN);
                        break;
                    default:
                        break;
                }
                drawBoard();
                sendStatus();
            } else if (e.key.keysym.scancode == SDL_SCANCODE_SPACE && !started) { /** begin the game */
                started = true;
                md->stopMusic();
                gm.start();
                md->setNextBlock(static_cast<unsigned>(gm.getBrd().getNext()->type));
                md->setStatistics(static_cast<int>(gm.getBrd().getCurrent()->type),
                                  gm.getStat(gm.getBrd().getCurrent()->type));
                drawBoard();
                sendStatus();
                md->refreshScreen();
            }
        }
    }

    exit(0);
}

void window::sendStatus() {
    using nlohmann::json;
    auto data = json::object();
    auto rows = json::array();
    for (int i = 0; i < ROWS; ++i) {
        auto column = json::array();
        for (int j = 0; j < COLUMNS; ++j) {
            if (gm.getBrd().getValue(i, j) >= 0) {
                column[j] = 1;
            } else {
                column[j] = 0;
            }
        }
        rows[i] = column;
    }
    data["started"] = started;
    data["game-over"] = gg;
    data["paused"] = paused;
    data["level"] = gm.getLevel();
    data["score"] = gm.getScore();
    auto statistics = json::array();
    statistics[0] = gm.getStat(block_type::t);
    statistics[1] = gm.getStat(block_type::j);
    statistics[2] = gm.getStat(block_type::z);
    statistics[3] = gm.getStat(block_type::o);
    statistics[4] = gm.getStat(block_type::s);
    statistics[5] = gm.getStat(block_type::l);
    statistics[6] = gm.getStat(block_type::i);
    data["statistics"] = statistics;
    data["next"] = block_str[static_cast<int>(gm.getBrd().getNext()->type)];
    auto cur = json::object();;

    cur["type"] = block_str[static_cast<int>(gm.getBrd().getCurrent()->type)];

    auto cur_block = gm.getBrd().getCurrent();
    int currentX = gm.getBrd().getCurrentPosX();
    int currentY = gm.getBrd().getCurrentPosY();
    int xPos;
    int yPos;
    auto cur_rows = json::array();
    int k = 0;
    for (int i = 0; i < cur_block->height; ++i) {
        for (int j = 0; j < cur_block->width; ++j) {
            if (cur_block->getValue(i, j)) {
                auto column = json::array();
                xPos = currentX + i;
                yPos = currentY + j;
                column = {yPos, xPos};
                cur_rows[k++] = column;
            }
        }
    }

    cur["tiles"] = cur_rows;
    data["current"] = cur;
    data["board"] = rows;
    rs.ev.send_event(data.dump());
}

void window::drawBoard() const {
    const block *pBlock = gm.getBrd().getCurrent();
    int currentX = gm.getBrd().getCurrentPosX();
    int currentY = gm.getBrd().getCurrentPosY();

    /** draw board itself and fill the tiles */
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (gm.getBrd().getValue(i, j) >= 0) {
                md->createMino(i, j, gm.getBrd().getValue(i, j));
            } else {
                md->clearMino(i, j);
            }
        }
    }

    /** draw current block and fill the block tiles */
    int xPos;
    int yPos;
    for (int i = 0; i < pBlock->height; ++i) {
        for (int j = 0; j < pBlock->width; ++j) {
            if (pBlock->getValue(i, j)) {
                xPos = currentX + i;
                yPos = currentY + j;
                if (xPos >= 0 && yPos >= 0) {
                    md->createMino(xPos, yPos, static_cast<int>(pBlock->type));
                }
            }
        }
    }
    md->refreshScreen();
}

void window::processMerging(std::vector<int> &lines) {

    /** first check any clearLines or tetris */
    using namespace std::chrono_literals;

    if (!lines.empty()) { /** MERGE or TETRIS */
        auto middle = COLUMNS / 2;
        int k = middle - 1;
        int z = middle;
        if (lines.size() == 4) {
            md->playTetrisMusic();
        } else {
            md->playClearingMusic();
        }
        for (int j = 0; j < middle; j++) {// hata burda galiba
            for (auto i: lines) {
                md->clearMino(i, z);
                md->clearMino(i, k);
            }
            z++;
            k--;
            md->refreshScreen();
            std::this_thread::sleep_for(80ms);
        }
    } else { /** LANDING */
        md->playLandingMusic();
    }

    md->setStatistics(static_cast<int>(gm.getBrd().getCurrent()->type),
                      gm.getStat(gm.getBrd().getCurrent()->type));
    md->setNextBlock(static_cast<unsigned>(gm.getBrd().getNext()->type));
    md->setCurrentScore(gm.getScore());
    md->setLineScore(gm.getLines());
    if (level != gm.getLevel()) {
        md->playLevelUpMusic();
        level = gm.getLevel();
    }
    md->setLevel(gm.getLevel());
    md->refreshScreen();
}
