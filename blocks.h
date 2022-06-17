//
// Created by alcicer on 5/30/2022.
//

#ifndef TETRIS_BLOCKS_H
#define TETRIS_BLOCKS_H

#include <array>
#include <random>
#include <memory>
#include <ctime>

enum class block_type : unsigned {
    t,
    j,
    z,
    o,
    s,
    l,
    i
};

enum class rotation : unsigned {
    rotation_down,
    rotation_left,
    rotation_up,
    rotation_right
};

static rotation &operator++(rotation &rt) {
    auto urt = static_cast<unsigned>(rt);
    urt = ++urt % 4;
    rt = static_cast<rotation>(urt);
    return rt;
}

static rotation &operator--(rotation &rt) {
    auto urt = static_cast<unsigned>(rt);
    urt = --urt % 4;
    rt = static_cast<rotation>(urt);
    return rt;
}

/** block matrix
 * . . . .
 * . . . .
 * . . . .
 * . . . .
 */
class block {
public:

    /**
     *
     * @param type block type(t, j, z, o, s, l, i)
     * @param height number of rows
     * @param width number of columns
     */
    block(block_type type, int height, int width) : type(type), height(height), width(width),
                                                    m(height, std::vector<bool>(width,
                                                                                false)) {
    }

    block(block &) = delete;

    block(block &&) = delete;

    block &operator=(const block &rhs) = delete;

    block &operator=(const block &&rhs) = delete;

    const block_type type;

    virtual ~block() = 0;

    /**
     *
     * @param clockwise if true, will rotate the block clockwise, else counterclockwise
     */
    virtual void rotate(bool clockwise);

    /**
     *
     * @param x row index
     * @param y column index
     * @return true if it has value
     */
    [[nodiscard]] bool getValue(unsigned x, unsigned y) const {
        return m[x][y];
    }

    const unsigned height;
    const unsigned width;

protected:
    std::vector<std::vector<bool>> m;
    rotation rt{rotation::rotation_down};
};

/**
 * . . . .
 * . # # .
 * . # # .
 * . . . .
 */
class o_block : public block {
public:
    o_block() : block(block_type::o, 4, 4) {
        m[1][1] = m[1][2] = m[2][1] = m[2][2] = true;
    }
};

/**
 * . . . .
 * . . . .
 * # # # #
 * . . . .
 */
class i_block : public block {
public:
    i_block() : block(block_type::i, 4, 4) {
        m[2][0] = m[2][1] = m[2][2] = m[2][3] = true;
    }

    void rotate(bool clockwise) override;
};

/**
 * . . .
 * # # #
 * . # .
 */
class t_block : public block {
public:
    t_block() : block(block_type::t, 3, 3) {
        m[1][0] = m[1][1] = m[1][2] = m[2][1] = true;
    }

    void rotate(bool clockwise) override;
};

/**
 * . . .
 * # # #
 * # . .
 */
class l_block : public block {
public:
    l_block() : block(block_type::l, 3, 3) {
        m[1][0] = m[1][1] = m[1][2] = m[2][0] = true;
    }

    void rotate(bool clockwise) override;
};

/**
 * . . .
 * # # #
 * . . #
 */
class j_block : public block {
public:
    j_block() : block(block_type::j, 3, 3) {
        m[1][0] = m[1][1] = m[1][2] = m[2][2] = true;
    }

    void rotate(bool clockwise) override;
};

/**
 * . . .
 * . # #
 * # # .
 */
class s_block : public block {
public:
    s_block() : block(block_type::s, 3, 3) {
        m[1][1] = m[1][2] = m[2][0] = m[2][1] = true;
    }

    void rotate(bool clockwise) override;
};

/**
 * . . .
 * # # .
 * . # #
 */
class z_block : public block {
public:
    z_block() : block(block_type::z, 3, 3) {
        m[1][0] = m[1][1] = m[2][1] = m[2][2] = true;
    }

    void rotate(bool clockwise) override;
};

template<typename T, int min, int max>
class next_queue {
public:
    next_queue() = default;

    T getNext() {
        return roll(true);
    };
private:
    T roll(bool re_roll) {
        std::uniform_int_distribution<> distribution(min, max + re_roll);
        int r = distribution(generator);
        time(nullptr);
        if ((re_roll && r == max + re_roll) || r == static_cast<int>(previous)) {
            return roll(false);
        } else {
            previous = static_cast<T>(r);
            return static_cast<T>(r);
        }
    }

    T previous;
    std::default_random_engine generator = std::default_random_engine(std::random_device{}());
};

class block_queue {
public:

    [[nodiscard]] std::unique_ptr<block> generate_block();

private:
    next_queue<block_type, 0, 6> queue;
};

std::ostream &operator<<(std::ostream &os, const block_type &t);

#endif //TETRIS_BLOCKS_H
