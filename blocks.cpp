//
// Created by alcicer on 5/31/2022.
//

#include <iostream>
#include "blocks.h"

block::~block() = default;

std::unique_ptr<block> block_queue::generate_block() {

    auto bt = queue.getNext();

    switch (bt) {
        case block_type::o:
            return std::make_unique<o_block>();
        case block_type::i:
            return std::make_unique<i_block>();
        case block_type::t:
            return std::make_unique<t_block>();
        case block_type::l:
            return std::make_unique<l_block>();
        case block_type::j:
            return std::make_unique<j_block>();
        case block_type::s:
            return std::make_unique<s_block>();
        case block_type::z:
            return std::make_unique<z_block>();
        default:
            throw std::range_error("not fount proper block in range");
    }
}

std::ostream &operator<<(std::ostream &os, const block_type &t) {
    os << static_cast<std::underlying_type<block_type>::type>(t);
    return os;
}

void block::rotate(bool clockwise) {
    if (clockwise) {
        ++rt;
    } else {
        --rt;
    }
}

void i_block::rotate(bool clockwise) {
    switch (rt) {
        case rotation::rotation_down:
        case rotation::rotation_up:
            m[2][0] = m[2][1] = m[2][3] = false;
            m[0][2] = m[1][2] = m[3][2] = true;
            break;
        case rotation::rotation_left:
        case rotation::rotation_right:
            m[2][0] = m[2][1] = m[2][3] = true;
            m[0][2] = m[1][2] = m[3][2] = false;
            break;
        default:
            break;
    }
    block::rotate(clockwise);
}

void t_block::rotate(bool clockwise) {
    switch (rt) {
        case rotation::rotation_down:
            if (clockwise) {
                m[1][2] = false;
            } else {
                m[1][0] = false;
            }
            m[0][1] = true;
            break;
        case rotation::rotation_left:
            if (clockwise) {
                m[2][1] = false;
            } else {
                m[0][1] = false;
            }
            m[1][2] = true;
            break;
        case rotation::rotation_right:
            if (clockwise) {
                m[0][1] = false;
            } else {
                m[2][1] = false;
            }
            m[1][0] = true;
            break;
        case rotation::rotation_up:
            if (clockwise) {
                m[1][0] = false;
            } else {
                m[1][2] = false;
            }
            m[2][1] = true;
            break;
        default:
            break;
    }
    block::rotate(clockwise);
}

void l_block::rotate(bool clockwise) {
    switch (rt) {
        case rotation::rotation_down:
            if (clockwise) {
                m[0][0] = true;
            } else {
                m[2][2] = true;
            }
            m[1][0] = m[2][0] = m[1][2] = false;
            m[0][1] = m[2][1] = true;
            break;
        case rotation::rotation_left:
            if (clockwise) {
                m[0][2] = true;
            } else {
                m[2][0] = true;
            }
            m[0][0] = m[0][1] = m[2][1] = false;
            m[1][0] = m[1][2] = true;
            break;
        case rotation::rotation_right:
            if (clockwise) {
                m[2][0] = true;
            } else {
                m[0][2] = true;
            }
            m[0][1] = m[2][1] = m[2][2] = false;
            m[1][0] = m[1][2] = true;
            break;
        case rotation::rotation_up:
            if (clockwise) {
                m[2][2] = true;
            } else {
                m[0][0] = true;
            }
            m[1][0] = m[0][2] = m[1][2] = false;
            m[0][1] = m[2][1] = true;
            break;
        default:
            break;
    }
    block::rotate(clockwise);
}

void j_block::rotate(bool clockwise) {
    switch (rt) {
        case rotation::rotation_down:
            if (clockwise) {
                m[2][0] = true;
            } else {
                m[0][2] = true;
            }
            m[1][0] = m[1][2] = m[2][2] = false;
            m[0][1] = m[2][1] = true;
            break;
        case rotation::rotation_left:
            if (clockwise) {
                m[0][0] = true;
            } else {
                m[2][2] = true;
            }
            m[2][0] = m[2][1] = m[0][1] = false;
            m[1][0] = m[1][2] = true;
            break;
        case rotation::rotation_right:
            if (clockwise) {
                m[2][2] = true;
            } else {
                m[0][0] = true;
            }
            m[0][1] = m[0][2] = m[2][1] = false;
            m[1][0] = m[1][2] = true;
            break;
        case rotation::rotation_up:
            if (clockwise) {
                m[0][2] = true;
            } else {
                m[2][0] = true;
            }
            m[0][0] = m[1][0] = m[1][2] = false;
            m[0][1] = m[2][1] = true;
            break;
        default:
            break;
    }
    block::rotate(clockwise);
}

void s_block::rotate(bool clockwise) {
    switch (rt) {
        case rotation::rotation_down:
        case rotation::rotation_up:
            m[1][2] = m[2][0] = false;
            m[0][0] = m[1][0] = true;
            break;
        case rotation::rotation_left:
        case rotation::rotation_right:
            m[0][0] = m[1][0] = false;
            m[1][2] = m[2][0] = true;
            break;
        default:
            break;
    }
    block::rotate(clockwise);
}

void z_block::rotate(bool clockwise) {
    switch (rt) {
        case rotation::rotation_down:
        case rotation::rotation_up:
            m[2][1] = m[2][2] = false;
            m[0][1] = m[2][0] = true;
            break;
        case rotation::rotation_left:
        case rotation::rotation_right:
            m[0][1] = m[2][0] = false;
            m[2][1] = m[2][2] = true;
            break;
        default:
            break;
    }
    block::rotate(clockwise);
}

