#ifndef SOLVEPUZZLE_H
#define SOLVEPUZZLE_H
#include "grid.h"
#include <set>
#include<map>

class solvepuzzle
{

   std::set<int*> track;
   int resultGrid[9][9];
   int resultGrid16[16][16];

   std::map<int,std::vector<int*>> rowFd;
   std::map<int,std::vector<int*>> colFd;
   std::map<int,std::vector<int*>> blkFd;


public:

    solvepuzzle();
    bool validity(int*x, int n);
    bool validity_parti(int*x, int i,int j, int n);
    bool checkrow(int *x,int i, int n);
    bool checkcol(int *x, int j, int n);
    bool checkblock(int *x,int i, int j,int n);
    void solve(int *x,int n);
    bool anothersol(int*x,std::set<int>* s);
    int *getResult(int n){
        if(n==9) return *resultGrid;
        else return *resultGrid16;
    }
    bool solved = false;
   // void solve2(int *x,int n);

    int totalstep;


};

#endif // SOLVEPUZZLE_H
