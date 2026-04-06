#pragma once
#include <constants.h>

namespace mcv
{
template <typename T>
class Point
{
public:
    Point<T>(){}
    Point<T>(T x, T y)
    {
        this->x = x;
        this->y = y;
    }

public:
    T x = 0;
    T y = 0;
};

template <typename T>
class Rect
{
public:
    Rect<T>(){}
    Rect<T>(Point<T> tl, Point<T> br)
    {
        this->tl = tl;
        this->br = br;
        width = br.x - tl.x;
        height = br.y - tl.y;
    }

public:
    Point<T> tl;
    Point<T> br;
    T width;
    T height;
};

}