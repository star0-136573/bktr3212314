#include "generatepuzzle.h"
#include <random>
#include <vector>
#include<QDebug>

generatepuzzle::generatepuzzle()
{

}

showconstraint sc;
solvepuzzle sp;
//n is size 9 or 16
/*
 *  the recent mode will generate 17 clues
 *
 *  @comment : it is not a successful function due the inefficiency of solver.
 *              an unbiased or insolvable Sudoku may be generated
 */
void generatepuzzle::generate(int *x, int n)
{

   // int clues = randnum(3)+17;
    int minimumgiven = 17;
    int clues = 20;
    if(n==16) clues = 5;

    int arr[n*n];
    //assign 0 - 80 or 0 to 255 to the cell
    for(int i=0; i<n*n ;i++){
        *(arr+i) = i;
    }
   shuffleArray(arr,n*n);


   int start = 0;
   int arrpos = 0;


   while(start < minimumgiven){
       //a random cell with position i,j
       int pos = *(arr+arrpos);

      // find constraints for a particular cell
       sc.findconstraintparti(x,pos/n,pos%n,n); // pos/n pos%n : i, j position

      std::vector<int> candidates = validcandidates(sc,n);
      int z = randnum(candidates.size())-1;

      if(candidates.size() > 0){
       *(x+pos)=  candidates.at(z);
       // sp.checksolvable(x,n);
     //   qDebug() << "tm : " << sp.solved;
      // if(!sp.solved) {*(x+pos) = 0;}
      //sp.solve(x,n);
    // if(sp.solved)
      start ++;
   //  else *(x+pos) = 0;
      }
      arrpos++;
   }
}


//get valid candidates of a cell
std::vector<int> generatepuzzle::validcandidates(showconstraint sc, int n){
    std::vector<int> v;
    for(int i=1;i<=n; i++){
        if(*(sc.getconstraint(n)+i)==3) v.push_back(i);
    }

    return v;
}




//fisher and yate's method, shuffle array to get a set of distinct values
void generatepuzzle::shuffleArray(int *x, int n){

   for(int i=n; i >0; i--){

     int pos = randnum(i)-1;
     //swap
     int temp = *(x+pos);
     *(x+pos) = *(x+i-1);
     *(x+i-1) = temp;
   }
}


// random number generator
int generatepuzzle::randnum(int n)
{
using namespace std;
  random_device dev;
  mt19937 rng(dev());
  uniform_int_distribution<mt19937::result_type> dist6(1,n);
 int num = dist6(rng);
 //cout << num << endl;

        return num;
}
