#include "patternrecognition.h"
#include "showconstraint.h"
#include <map>
#include <vector>
#include <set>


patternrecognition::patternrecognition()
{
;
}
void patternrecognition::Rect(int *grid, int size)
{
   std::map<int,std::vector<int>> numpositionRect = mapconstraints(grid,size,"Rect");
   matchpoints(false,size,numpositionRect);
}

void patternrecognition::XYwing(int *grid, int size)
{


     std::map<int,std::vector<int>> numpositionXY = mapconstraints(grid,size,"XY");
    matchpoints(true,size,numpositionXY);


}
void patternrecognition::matchpoints(bool XYmode,int size,std::map<int,std::vector<int>> numposition)
{
    //since the vector array are already in ordered position , to find an x
  // can find by four point of top right top left, bottom left and bottom right;
   for(int i=1; i<=size; i++){
       //if there're more or equal than four cells
       if(numposition[i].size()>=4){
           auto &q = numposition[i];
           //minus the last 3 pts of possible nodes
           for(int j = 0; j< (int)q.size()-3; j++){
             int next = 1;

             while(next < (int)q.size()-2){

                 bool topRight = false;
                 bool bottomLeft = false;
                 bool bottomRight = false;
                 int k;
             //find top right corner
             for(  k = next ; k<(int)q.size()-2; k++){
                 if(q[k]/size == q[j]/size && q[k]!=q[j]){ topRight = true; break;}
             }
             //bottom left
             int m;
             if(topRight){
                 for( m = k+1; m<(int)q.size()-1; m++){
                     if(q[m]%size == q[j]%size && q[m] !=q[j]){ bottomLeft = true; break;}
                 }
             }
             //bottom right
             int n;
             if(bottomLeft){
                 for(n=m+1; n<(int)q.size(); n++){
                     if(q[n]/size == q[m]/size && q[n]%size == q[k]%size
                             &&q[n]!=q[m]){ bottomRight = true; break;}
                 }
             }

             //if there exit an X, add those four position
             if( topRight && bottomLeft && bottomRight){

                 //insert four corner position;
                 std::vector<int> tmpX = {q[j],q[k],q[m],q[n]};
                 //X is a set, so do not have duplicate sets

                 if(XYmode) X.insert(tmpX);
                 else R.insert(tmpX);

             };

             //Y wings
             if(XYmode && topRight && bottomLeft && !bottomRight){

                 //insert three corner position;
               std::vector<int> tmpY = {q[j],q[k],q[m]};
                 //X is a set, so do not have duplicate sets
                 Y.insert(tmpY);

             };

              //next round search should start after the right corner of first set
              next = k+1;

             }
           }

       }
     }
}

std::map<int,std::vector<int>> patternrecognition::mapconstraints(int *grid, int size, std::string mode)
{
   showconstraint sc;
   std::map<int,std::vector<int>> numposition;

   for(int i = 0 ; i<size; i++){
        for(int j=0; j<size; j++){
           //only involve the cells not filled
           if(*(grid+i*size+j)==0) {
             sc.findconstraintparti(grid,i,j,size);
              int count = 0;
             //map number 1 to n with corresponding cells
             for(int k = 1;k<=size; k++){
                    //put the valid candidates to a set
                   if(*(sc.getconstraint(size)+k)==3){
                       //insert cell pos
                         count++;
                       if(mode == "XY")  numposition[k].push_back(i*size+j);
                      }
                  }
               //add to
               if(mode == "Rect" && count == 2){
                   for(int k = 1;k<=size; k++){
                          //put the valid candidates to a set
                         if(*(sc.getconstraint(size)+k)==3){
                             //insert cell pos
                              numposition[k].push_back(i*size+j);
                            }
                        }
                   }
             }

          }
      }

    return numposition;
}
