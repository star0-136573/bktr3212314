#ifndef GENERATEPUZZLE_H
#define GENERATEPUZZLE_H
#include "grid.h"
#include "solvepuzzle.h"
#include "showconstraint.h"



class generatepuzzle
{
public:
    generatepuzzle();
    void generate(int *x, int n);
    int randnum(int n);
    void shuffleArray(int *x,int n);


private:
    std::vector<int>  validcandidates(showconstraint sc,int n);

};

#endif // GENERATEPUZZLE_H
