//
// Created by alcicer on 6/7/2022.
//

#include <iostream>
#include "game.h"

movement_status board::moveDown() {

    if (!landed) {
        bool ret = checkNextPosition(1, 0);
        if (ret) {
            currentPosX++;
            return movement_status::MOVEMENT_SUCCESS;
        }
    }
    return movement_status::MOVEMENT_FAILED;

}

movement_status board::moveLeft() {
    if (!landed) {
        bool ret = checkNextPosition(0, -1);
        if (ret) {
            currentPosY--;
            return movement_status::MOVEMENT_SUCCESS;
        }
    }
    return movement_status::MOVEMENT_FAILED;
}


movement_status board::moveRight() {
    if (!landed) {
        bool ret = checkNextPosition(0, 1);
        if (ret) {
            currentPosY++;
            return movement_status::MOVEMENT_SUCCESS;
        }
    }
    return movement_status::MOVEMENT_FAILED;
}

movement_status board::rotateClockWise() const {
    if (!landed) {
        current->rotate(true);
        if (checkNextPosition(0, 0)) {
            return movement_status::ROTATE_SUCCESS;
        } else {
            current->rotate(false);
        }
    }
    return movement_status::ROTATE_FAILED;
}

movement_status board::rotateCounterClockWise() const {
    if (!landed) {
        current->rotate(false);
        if (checkNextPosition(0, 0)) {
            return movement_status::ROTATE_SUCCESS;
        } else {
            current->rotate(true);
        }
    }
    return movement_status::ROTATE_FAILED;
}

bool board::checkNextPosition(int moveX, int moveY) const {
    int testPosX;
    int testPosY;

    for (int i = 0; i < current->height; ++i) {
        for (int j = 0; j < current->width; ++j) {
            if (!current->getValue(i, j)) { /** if block tile false, OK */
                continue;
            } else {
                testPosX = i + currentPosX + moveX;
                testPosY = j + currentPosY + moveY;
                if (testPosX < 0 && testPosY >= 0 &&
                    testPosY <
                    columns) { /** if x pos less than zero it's mean tile above the board, column should be in range, OK */
                    continue;
                }
                if (testPosX >= rows || testPosY >= columns ||
                    testPosY < 0) { /** bottom overflow, right overflow, left overflow, FAIL */
                    return false;
                } else if (m[testPosX][testPosY] >= 0) { /** board tile already filled, FAIL */
                    return false;
                }
            }
        }
    }
    return true;
}

int board::doTick() {
    if (moveDown() == movement_status::MOVEMENT_FAILED && land() == merge_status::GAME_OVER) {
        return -1;
    }
    if (landed) {
        current = std::move(next);
        currentPosX = CURRENT_X_DEFAULT;
        currentPosY = CURRENT_Y_DEFAULT;
        next = blockQueue.generate_block();
        landed = false;
        return 0;
    }
    return 1;
}

merge_status board::land() {

    int testX;
    int testY;

    for (int i = 0; i < current->height; ++i) {
        for (int j = 0; j < current->width; ++j) {
            if (!current->getValue(i, j)) { /** if block tile false, do nothing */
                continue;
            } else {
                testX = i + currentPosX;
                testY = j + currentPosY;
                if (testX < 0) { /** if x pos less than zero it's mean tile above the board, game over */
                    return merge_status::GAME_OVER;
                }
                m[testX][testY] = static_cast<int>(current->type);
            }
        }
    }
    current = nullptr;
    landed = true;
    return merge_status::MERGED;
}

std::vector<int> board::clearLines() {

    /** find rows which all tiles filled */
    bool clear;
    std::vector<int> rowIndexes;
    for (int i = 0; i < rows; ++i) {
        clear = true;
        for (int j = 0; j < columns; ++j) {
            if (m[i][j] < 0) {
                clear = false;
                break;
            }
        }
        if (clear) {
            rowIndexes.push_back(i);
        }
    }

    /** drop rows after clearing */
    for (auto i: rowIndexes) {
        m.erase(m.begin() + i);
        m.insert(m.begin(), std::vector<int>(columns, -1));
    }

    return rowIndexes;
}

void board::init() {
    current = std::move(next);
    next = blockQueue.generate_block();
}

const board &game::getBrd() const {
    return brd;
}

int game::doTick(std::vector<int> &lineIndexes) {

    lineIndexes.clear();
    auto tick = brd.doTick();
    if (tick < 0) {
        return -1;
    } else if (tick == 0) {
        auto clear = brd.clearLines();
        unsigned size = clear.size();
        unsigned earned = 0;
        if (size == 1) {
            earned = 40 * (level + 1);
        } else if (size == 2) {
            earned = 100 * (level + 1);
        } else if (size == 3) {
            earned = 300 * (level + 1);
        } else if (size == 4) {
            earned = 1200 * (level + 1);
        }

        lines += size;
        score += earned;
        if (size > 0) {
            unsigned inc = std::min((level * 10) + 10, std::max(100u, (level * 10) - 50));
            if (lines >= inc) {
                ++level;
                speed = getFrame(level) / gravity;
            }
        }
        increaseStat(brd.getCurrent()->type);
        lineIndexes = clear;
        return 0;
    } else {
        return 1;
    }
}

game::game(unsigned r, unsigned c, unsigned level) : brd(r, c), level(level) {
    lvl_frames = {{0,  48},
                  {1,  43},
                  {2,  38},
                  {3,  33},
                  {4,  28},
                  {5,  23},
                  {6,  18},
                  {7,  13},
                  {8,  8},
                  {9,  6},
                  {12, 5},
                  {15, 4},
                  {18, 3},
                  {28, 2},
                  {50, 1}};
    speed = getFrame(level) / gravity;
    lvl_increase = {{0,  10},
                    {1,  20},
                    {2,  30},
                    {3,  40},
                    {4,  50},
                    {5,  60},
                    {6,  70},
                    {7,  80},
                    {8,  90},
                    {15, 100},
                    {16, 110},
                    {17, 120},
                    {18, 130},
                    {19, 140},
                    {20, 150},
                    {21, 160},
                    {22, 170},
                    {23, 180},
                    {24, 190},
                    {50, 200}};
    statistics = {{block_type::t, 0},
                  {block_type::j, 0},
                  {block_type::z, 0},
                  {block_type::o, 0},
                  {block_type::s, 0},
                  {block_type::l, 0},
                  {block_type::i, 0},
    };
}

[[nodiscard]] unsigned game::getFrame(unsigned lvl) const {
    auto up = lvl_frames.lower_bound(lvl);
    if (up == lvl_frames.end()) {
        throw std::range_error("not found proper frame");
    }
    return up->second;
}

[[nodiscard]] unsigned game::getLvlIncrease(unsigned lvl) const {
    auto up = lvl_increase.lower_bound(lvl);
    if (up == lvl_increase.end()) {
        throw std::range_error("not found proper increase");
    }
    return up->second;
}

void game::increaseStat(block_type bt) {
    auto it = statistics.find(bt);
    if (it != statistics.end()) {
        ++(it->second);
    }
}

unsigned game::getStat(block_type bt) const {
    auto it = statistics.find(bt);
    if (it != statistics.end()) {
        return it->second;
    }
    return 0;
}

void game::start() {
    if (!started) {
        brd.init();
        increaseStat(brd.getCurrent()->type);
        started = true;
    }
}

movement_status game::processCommand(command cmd) {
    switch (cmd) {
        case command::ROTATE_CLOCKWISE:
            return brd.rotateClockWise();
        case command::ROTATE_COUNTER_CLOCKWISE:
            return brd.rotateCounterClockWise();
        case command::MOVE_LEFT:
            return brd.moveLeft();
        case command::MOVE_RIGHT:
            return brd.moveRight();
        case command::MOVE_DOWN:
            return brd.moveDown();
    }
    return movement_status::MOVEMENT_SUCCESS;
}
