#ifndef GRID_H
#define GRID_H
#include <iostream>

class grid {

//    int G[9][9] = {
//        {3,0,0,9,0,4,0,0,1},
//        {0,0,2,0,0,0,4,0,0},
//        {0,6,1,0,0,0,7,9,0},
//        {6,0,0,2,4,7,0,0,5},
//        {0,0,0,0,0,0,0,0,0},
//        {2,0,0,8,3,6,0,0,4},
//        {0,4,6,0,0,0,2,3,0},
//        {0,0,9,0,0,0,6,0,0},
//        {5,0,0,3,0,9,0,0,8}
//    };
    int G[9][9];
    int G16[16][16];
public:
       int n = 9;
    grid(int n);
    void printGrid();
    int *Grid(){
        if(n==9)
        return *G;
        else return *G16;
    }

};

#endif // GRID_H
