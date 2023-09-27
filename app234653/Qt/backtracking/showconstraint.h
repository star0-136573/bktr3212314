#ifndef SHOWCONSTRAINT_H
#define SHOWCONSTRAINT_H
#include "grid.h"
#include<map>
#include<vector>



class showconstraint
{
    int constraint[10];
    int constraint16[17];
    // - 1 if violate
    void setconstraint(int i,int n){
        if(n==9)
          //if there exist 5, for example, then the others can't have 5,
            //so the corresponding posistion constraint[5] - 1.
          *(constraint+i) = *(constraint+i)-1;
        else
          *(constraint16+i) = *(constraint16+i)-1;
    };


public:
    showconstraint();
    void findconstraintparti(int* x,int i, int j,int n);
    void updaterow(int* x,int i, int n);
    void updatecol(int* x,int j, int n);
    void updateblk(int* x,int i, int j,int n);

    // int {3,3,3,3....}
    void declareconstraint(int n){
        if(n == 9){
        for(int i=1; i<n+1; i++){
            constraint[i]=3;
        }
        }else{
            for(int i=1; i<n+1; i++){
                constraint16[i]=3;
            }
        }


    };
    int *getconstraint(int n){
        if(n==9)
            return constraint;
        else
            return constraint16;
    };

};

#endif // SHOWCONSTRAINT_H
