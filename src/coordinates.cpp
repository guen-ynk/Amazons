#include "coordniates.hpp"

    
    void Coordinates::add(Coordinates sec){
        x+=sec.x;
        y+=sec.y;
    }
    void Coordinates::sub(Coordinates sec){
        x-=sec.x;
        y-=sec.y;
    }