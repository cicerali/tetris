//
// Created by alcicer on 6/15/2022.
//

#ifndef TETRIS_MEDIA_H
#define TETRIS_MEDIA_H

/**
 * responsible from screen drawing and playing sound
 */
class media {
public:

    virtual ~media() = default;

    virtual void refreshScreen() = 0;

    virtual void setLineScore(unsigned score) = 0;

    virtual void setStatistics(int index, unsigned value) = 0;

    virtual void setLevel(unsigned level) = 0;

    virtual void setCurrentScore(unsigned score) = 0;

    virtual void setTopScore(unsigned score) = 0;

    virtual void createMino(int x, int y, unsigned type) = 0;

    virtual void clearMino(int x, int y) = 0;

    virtual void setNextBlock(unsigned int type) = 0;

    virtual void clearNextBlock() = 0;

    virtual void gameOver() = 0;

    virtual void playMoveMusic() = 0;

    virtual void playRotateMusic() = 0;

    virtual void playLandingMusic() = 0;

    virtual void playTetrisMusic() = 0;

    virtual void playClearingMusic() = 0;

    virtual void playLevelUpMusic() = 0;

    virtual void playGameOverMusic() = 0;

    virtual void playEntryMusic() = 0;

    virtual void stopMusic() = 0;
};

#endif //TETRIS_MEDIA_H
