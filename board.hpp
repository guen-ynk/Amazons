// sample.h
#pragma once
#include <vector> // #include directive
#include <string>
#include "Eigen/Dense"
#include <iostream>


using namespace std;
using namespace Eigen;

class Coordinates{
    public:
        short x,y;
    Coordinates(short xx, short yy){
        x = xx;
        y = yy;
    }
};
class Board {
    public:
        bool whites_turn;
        short board_size;
        short amazons_count;
        vector<Coordinates> positions;
        Matrix<short,Dynamic,Dynamic> field;
        
        Board(){
            whites_turn = true;
            board_size = 10;
            amazons_count = 4;
            field =  Matrix <short , 10, 10>::Zero();

            field(0,3) = 1;
            field(0,6) = 1;
            field(3,0) = 1;
            field(3,9) = 1;

            field(9,3) = 2;
            field(9,6) = 2;
            field(6,0) = 2;
            field(6,9) = 2;
            
        }

        /*
            returns vector of coordinates ( amazons )
        **/
        vector<Coordinates> get_queen_positions(){
            short color = whites_turn ? 1 : 2;
            short counter = 0;
            vector<Coordinates> positions;
            for (size_t i = 0; i < board_size; i++)
            {
                for (size_t j = 0; j < board_size; j++)
                {
                    if(field(i,j)== color){
                        positions.push_back(Coordinates(i,j));
                        counter++;
                        if (counter == amazons_count)return positions;
                    }
                    
                }
                
            }
            
        }
         /*
            returns vector of coordinates ( reachable for amazon at position c )
        **/
        vector<Coordinates> get_amazon_moves(Coordinates c){
            short x = c.x;
            short y = c.y;                        
            vector<Coordinates> positions;
            
            // North
            int i = x-1;
            do{   
                if(field(i,y)==0){
                    positions.push_back(Coordinates(i,y));
                }else{
                    break;
                } 
            }while(i--);

            // South
            i = x+1;
            for (; i < board_size; i++)
            {
                if(field(i,y)==0){
                    positions.push_back(Coordinates(i,y));
                }else{
                    break;
                } 
            }
            
            // West
            i = y-1;
            do{   
                if(field(x,i)==0){
                    positions.push_back(Coordinates(x,i));
                }else{
                    break;
                } 
            }while(i--);

            // East
            i = y+1;
            for (; i < board_size; i++)
            {
                if(field(x,i)==0){
                    positions.push_back(Coordinates(x,i));
                }else{
                    break;
                } 
            }

            // SW
            x = c.x;
            y = c.y; 
            i = 0;
            for (; i < board_size; i++)
            {
                x -= 1;
                y -= 1;
                if( x>=0 && y>=0 && field(x,y)==0){
                    positions.push_back(Coordinates(x,y));
                }else{
                    break;
                }
            }

            // NE
            x = c.x;
            y = c.y; 
            i = 0;
            for (; i < board_size; i++)
            {
                x += 1;
                y += 1;
                if( x<board_size && y<board_size && field(x,y)==0){
                    positions.push_back(Coordinates(x,y));
                }else{
                    break;
                }
            }

            // SE
            x = c.x;
            y = c.y; 
            i = 0;
            for (; i < board_size; i++)
            {
                x -= 1;
                y += 1;
                if( x>=0 && y<board_size && field(x,y)==0){
                    positions.push_back(Coordinates(x,y));
                }else{
                    break;
                }
            }

            // NW
            x = c.x;
            y = c.y; 
            i = 0;
            for (; i < board_size; i++)
            {
                x += 1;
                y -= 1;
                if( x<board_size && y>=0 && field(x,y)==0){
                    positions.push_back(Coordinates(x,y));
                }else{
                    break;
                }
            }

            return positions;
        }

    };

 