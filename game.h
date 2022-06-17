//
// Created by alcicer on 5/30/2022.
//

#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <map>
#include <algorithm>
#include <stdexcept>
#include "blocks.h"

enum class movement_status : unsigned {
    MOVEMENT_SUCCESS,
    MOVEMENT_FAILED,
    ROTATE_SUCCESS,
    ROTATE_FAILED
};

enum class merge_status : unsigned {
    MERGED,
    GAME_OVER
};

enum class command : unsigned {
    ROTATE_CLOCKWISE,
    ROTATE_COUNTER_CLOCKWISE,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_DOWN
};

class board {

public:
    /**
     *
     * @param r number of rows
     * @param c number of columns
     */
    board(unsigned r, unsigned c) : rows(r), columns(c), m(r, std::vector<int>(c, -1)) {
        next = blockQueue.generate_block();
    };

    movement_status moveDown();

    movement_status moveLeft();

    movement_status moveRight();

    [[nodiscard]] movement_status rotateClockWise() const;

    [[nodiscard]] movement_status rotateCounterClockWise() const;

    /**
     * The board will go one step further, to do this
     * it will try to move the current block down one square.
     * @return -1 if game over, 0 if block landed, 1 if the block has moved down one square
     */
    int doTick();

    /**
     * initialize the board, sets the blocks
     */
    void init();

    /**
     * clears the rows which all squares filled with minions
     * @return cleared row indexes
     */
    [[nodiscard]] std::vector<int> clearLines();

    [[nodiscard]] const block *getCurrent() const {
        return current.get();
    }

    [[nodiscard]] const block *getNext() const {
        return next.get();
    }

    /**
     *
     * @param x row index
     * @param y column index
     * @return -1 if not filled, else filled value which determines also minion type
     */
    [[nodiscard]] int getValue(unsigned x, unsigned y) const {
        return m[x][y];
    }

    /**
     *
     * @return current block`s top x position
     */
    [[nodiscard]] int getCurrentPosX() const {
        return currentPosX;
    };

    /**
     *
     * @return current block`s top y position
     */
    [[nodiscard]] int getCurrentPosY() const {
        return currentPosY;
    };

private:
    /**
     *
     * @param moveX move on X axis
     * @param moveY move on Y axis
     * @return true if position suitable
     */
    [[nodiscard]] bool checkNextPosition(int moveX, int moveY) const;

    /**
     * try to merge current block with board
     * @return MERGED if success, GAME_OVER if not possible
     */
    merge_status land();

    block_queue blockQueue;
    std::unique_ptr<block> current;
    bool landed = false;
    std::unique_ptr<block> next;
    static const int CURRENT_X_DEFAULT = -4;
    static const int CURRENT_Y_DEFAULT = 3;
    int currentPosX{CURRENT_X_DEFAULT};
    int currentPosY{CURRENT_Y_DEFAULT};
    const unsigned rows;
    const unsigned columns;
    /** board matrix rows X columns */
    std::vector<std::vector<int>> m;
};

class game {
public:
    /**
     * create game with default 20X10 and level 0
     */
    game() : game(20, 10) {
    }

    /**
     * create game with default 20X10 and starting level
     * @param level starting level
     */
    explicit game(unsigned level) : game(20, 10, level) {

    }

    /**
     *
     * @param r number of rows
     * @param c number of columns
     */
    game(unsigned r, unsigned c, unsigned level = 0);

    /**
     *
     * @param lvl level
     * @return original tetris frame value
     */
    [[nodiscard]] unsigned getFrame(unsigned lvl) const;

    /**
     *
     * @param lvl level
     * @return number of lines needed for increase the level
     */
    [[nodiscard]] unsigned getLvlIncrease(unsigned lvl) const;

    /**
     * increase +1 stat for block type
     * @param bt block type
     */
    void increaseStat(block_type bt);

    [[nodiscard]] unsigned getStat(block_type bt) const;

    [[nodiscard]] unsigned int getScore() const {
        return score;
    }

    [[nodiscard]] unsigned int getLines() const {
        return lines;
    }

    [[nodiscard]] unsigned int getLevel() const {
        return level;
    }

    [[nodiscard]] double getSpeed() const {
        return speed;
    }

    /**
    * The game will go one step further, to do this
    * it will call doTick for board and calculate level, speed, statistics, etc...
    * @return -1 if game over, 0 if block landed, 1 if the block has moved down one square
    */
    int doTick(std::vector<int> &lineIndexes);

    /**
     *
     * @param cmd user input
     * @return movement status
     */
    movement_status processCommand(command cmd);

    /**
     * start the game
     */
    void start();

    [[nodiscard]] const board &getBrd() const;

    // TODO
    // select start level
    // maybe wrappers for SDL functions, and native c++ game mechanism
private:
    bool started = false;
    std::map<unsigned, unsigned> lvl_frames;
    unsigned score{0};
    std::map<unsigned, unsigned> lvl_increase;
    unsigned lines{0};
    std::map<block_type, unsigned> statistics;
    unsigned level{0};
    double gravity = 60.0988;
    double speed;
    board brd;
};

#endif //TETRIS_GAME_H
