#pragma once
#include "coordinates.cpp"

class Move{
    public:
        Coordinates s;
        Coordinates d;
        Coordinates a;
    Move() = delete;
    Move(Coordinates s_in, Coordinates d_in, Coordinates a_in);
   

};