//
// Created by Yuri Moiseyenko on 2024-10-16.
//

#ifndef PICO_LIGHTSHOW_BR_ITERATOR_H
#define PICO_LIGHTSHOW_BR_ITERATOR_H
#include "pico/stdio.h"
const uint8_t BR_MIN = 1;
const uint8_t BR_MAX = 255;

class br_iterator {
public:
    explicit br_iterator(bool up=true) : up(up) {
        this->val = up? BR_MIN : BR_MAX;
    }

    virtual ~br_iterator()=default;

    uint8_t inline next() {
        if(up) {
            return val < BR_MIN ? BR_MIN: val >= BR_MAX ? BR_MAX : val++;
        }
        else {
            return val <= BR_MAX ? val < BR_MIN ? BR_MIN : val-- : BR_MAX;
        }
    }

    [[nodiscard]] uint8_t inline begin() const {
        return up? BR_MIN : BR_MAX;
    }

    [[nodiscard]] uint8_t inline end() const {
        return up? BR_MAX : BR_MIN;
    }

private:
    bool up;
    uint8_t val;
};


#endif //PICO_LIGHTSHOW_BR_ITERATOR_H
