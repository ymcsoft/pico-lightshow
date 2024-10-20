//
// Implementation of the range class
// example range(4) produces iterable values from 0..4
// for(int i : range(4)) iterates over the values from 0..4
// Created by Yuri Moiseyenko on 2024-10-19.
//

#ifndef PICO_LIGHTSHOW_RANGE_H
#define PICO_LIGHTSHOW_RANGE_H
class range
{
private:
    int last;
    int iter;

public:
    range(int start, int end):last(end),iter(start){}
    explicit range(int end):last(end),iter(0){}
    // Iterable functions
    [[nodiscard]] const range& begin() const { return *this; }
    [[nodiscard]] const range& end() const { return *this; }

    // Iterator functions
    bool operator!=(const range&) const { return iter < last; }
    void operator++() { ++iter; }
    int operator*() const { return iter; }
};

#endif //PICO_LIGHTSHOW_RANGE_H
