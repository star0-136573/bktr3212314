#include "showconstraint.h"
#include <cmath>
using namespace std;
showconstraint::showconstraint()
{

}
/*
 *  find the constraint of a  particular cell
 */
void showconstraint::findconstraintparti(int* x,int i, int j, int n)
{
    declareconstraint(n);
    updaterow(x,i,n);
    updatecol(x,j,n);
    updateblk(x,i,j,n);

}

void showconstraint::updaterow(int* x,int i, int n)
{

  for(int k = 0; k<n ; k++){
    //  cout << *(x+i*n+k) << " ";

      setconstraint(*(x+i*n+k),n);
  }

}
void showconstraint::updatecol(int* x,int j, int n)
{

  for(int k = 0; k<n ; k++){

   setconstraint(*(x+j+k*n),n);
  }
}
void showconstraint::updateblk(int* x,int i, int j, int n)
{

   int bs = sqrt(n);
   i = std::ceil((i+1.0)/bs);
   j = std::ceil((j+1.0)/bs);
   int* start = (x+(j-1)*bs+(i-1)*bs*n);  //start point of a block

   for(int a = 0; a<bs ; a++){
       for(int b = 0 ;b<bs ; b++){
             // cout << *(start+b+a*n) << " ";

              setconstraint(*(start+b+a*n),n);

       }
   }


}










