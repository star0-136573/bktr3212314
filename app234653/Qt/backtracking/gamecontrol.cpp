#include "gamecontrol.h"
#include "grid.h"
#include "generatepuzzle.h"
#include "showconstraint.h"
#include "patternrecognition.h"
#include "unittest.h"



gamecontrol::gamecontrol()
{

}
/*
 * generate new Sudoku
 */
void gamecontrol::startpuzzle(int size)
{
    this->size = size;
      //have only one grid instance
      static grid g = grid(size);

    //handle of game restart, clear previous grid data
    g = grid(size);

    generatepuzzle gp;
    gp.generate(g.Grid(),size);


    //for debugging use
    //  ptr = &g;
   //  ptr->printGrid();
    //pointer to
    puzzle = g.Grid();
    printf("%s \n","generated grid");


}

bool gamecontrol::updategrid(int pos, int value)
{
    //update inserted value
    int temp = *(puzzle+pos-1);
    *(puzzle+pos-1) = value;

    bool valid = checkviolate(pos-1);

    //if invalid, reverse change
    if(!valid) *(puzzle+pos-1) = temp;
    return valid;
}
/*
 * check if an attempt is valid
 */
bool gamecontrol::checkviolate(int pos)
{
     solvepuzzle sp;
    int i = pos/size;
    int j = pos%size;
    return sp.validity_parti(puzzle,i,j,size);

}

/*
 * find constraint
 */
void gamecontrol::constraints(int pos, int* arr)
{
    //grid position of a cell
    pos = pos -1;
    int i = pos/size;
    int j = pos%size;
    showconstraint sc;
    // copy result to arr
    sc.findconstraintparti(puzzle,i,j,size);
    for(int i=0; i<size; i++){
        *(arr+i) = *(sc.getconstraint(size)+1+i);
    }

}
/*
 * find patterns X-wings, Y-wings and Rectangle
 */
std::map<std::string,std::set<std::vector<int>>> gamecontrol::pattern()
{
   patternrecognition pr;
   std::map<std::string,std::set<std::vector<int>>> pMap;
   pr.XYwing(puzzle,size);
   pr.Rect(puzzle,size);

    auto *X = pr.Xwing();
    auto *Y = pr.Ywing();
    auto *R = pr.Rect();
   // std::cout << "size of X " << X->size() << "\n";
    pMap["X"] = *X;
    pMap["Y"] = *Y;
    pMap["R"] = *R;

   return pMap;
}

/*
 * grid update handling for nishio
 */
void gamecontrol::nishioupdategrid(int cell,int value)
{
   if( *(puzzle+cell-1) == value)
   {
       *(puzzle+cell-1) = 0 ;
   }
   else
   {
       *(puzzle+cell-1) = value ;
   }
}
/*
 * generate random number
 */
int gamecontrol::randnum(int start, int end)
{
    generatepuzzle gp;

    return gp.randnum(end)+start;
}

/*
 *  solve puzzle
 */
void gamecontrol::solve()
{
    solvepuzzle sp;
    sp.solve(puzzle,size);

   // std::cout << " solved: \n";
    int n = size;
    for(int i=0;i<n; i++){
       for(int j=0; j<n; j++){
         *(puzzle+i*n+j) =*(sp.getResult(n)+j+i*n) ;
       }

    }
}

/*
 * for testing
 */
void gamecontrol::test(int x, int n)
{
    unittest uni;
   // uni.randomnum(x,n);
   // uni.generate(x);
    uni.correctness(x);


}

