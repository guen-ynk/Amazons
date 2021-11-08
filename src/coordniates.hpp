#pragma once


class Coordinates{
    public:
        short x,y = {0};    

    Coordinates (short xx, short yy)
        :x(xx),y(yy)
       {}
    void add(Coordinates sec);
    void sub(Coordinates sec);
};