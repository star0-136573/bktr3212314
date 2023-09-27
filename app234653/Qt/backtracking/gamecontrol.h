#ifndef GAMECONTROL_H
#define GAMECONTROL_H
#include "grid.h"
#include "solvepuzzle.h"
#include<set>
#include<vector>
#include<map>
#include "generatepuzzle.h"


class gamecontrol
{
   int size;
    grid *ptr;



public:
    gamecontrol();

    void startpuzzle(int size);
    bool updategrid(int pos, int value);
    bool checkviolate(int pos);
    std::map<std::string,std::set<std::vector<int>>>pattern();
    void constraints(int pos, int* arr);
    void nishioupdategrid(int cell,int value);

    int* puzzle;
    int randnum(int start,int end);
     void solve();
     void test(int x,int n);


};

#endif // GAMECONTROL_H
