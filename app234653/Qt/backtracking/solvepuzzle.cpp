#include "solvepuzzle.h"
#include<cmath>
#include<set>
#include<stack>
#include<vector>
#include "showconstraint.h"
#include "generatepuzzle.h"
#include <QDebug>
using namespace std;
solvepuzzle::solvepuzzle()
{

}


//x is the grid, n is size
bool solvepuzzle::validity(int* x, int n)
{
    bool b = true;
    // assume it is valid
    if(b){ for(int i = 0; i<n; i++){
        b=checkrow(x,i,n);
    }
    }
    if(b){
        for(int j=0; j<n; j++){
            b=checkcol(x,j,n);
        }
    }
    //check blocks
    if(b){
        int a = sqrt(n);

            for(int m = 0 ;m < n; m+=a){

             for(int k = 0 ;k < n ; k+=a){
             b = checkblock(x,m,k,n);
        }
            }
    }
    //validity
    return b;
}

/*
 *  check if all the inserted number is different, if 9 number inserted,
    a duplicate will have only eight, so if size < count then false
 */

bool solvepuzzle::checkrow(int* x,int i,int n){

    bool b = true;
    std::set<int> s1;
    int count = 0;
    for(int k = 0; k<n ; k++){
        if(*(x+k+i*n) !=0){
            s1.insert(*(x+k+i*n));
            count++;
        }
    }

    if((int)s1.size()<count) b = false;
    return b;
}
bool solvepuzzle::checkcol(int* x,int j,int n){
    bool b = true;
    std::set<int> s1;
    int count = 0;
    for(int k = 0; k<n ; k++){
     if(*(x+j+k*n) !=0 ){
         s1.insert(*(x+j+k*n));
         count++;

     }
   }
     if((int)s1.size()<count) b = false;
    return b;
}

bool solvepuzzle::checkblock(int* x,int i, int j, int n){

    bool b = true;
    std::set<int> s1;
    int count = 0;
    int bs = sqrt(n);
    //calculate block number.
    i = std::ceil((i+1.0)/bs);
    j = std::ceil((j+1.0)/bs);
    int* start = (x+(j-1)*bs+(i-1)*bs*n);

    for(int a = 0; a<bs ; a++){
        for(int b = 0 ;b<bs ; b++){

           if( *(start+b+a*n)!=0){
               s1.insert(*(start+b+a*n));
               count ++;
           }
        }
    }
    if((int)s1.size()<count) b = false;
    return b;
}

bool solvepuzzle::validity_parti(int *x, int i,int j, int n)
{
    if(checkrow(x,i,n) && checkcol(x,j,n) &&checkblock(x,i,j,n))
        return true;
    else
        return false;
}


//void solvepuzzle::solve(int*x,int n)
//{
//    std::stack<int*> S1;
//    std::stack<int*> S2;
//    std::map<int*,std::vector<int>> cts;
//    std::map<int,std::vector<int*>> bucket;
//    bool solvable = true;

//    showconstraint sc;
//    //copy the grid
//    int grid[n][n];
//    for(int i=0;i<n; i++){
//       for(int j=0; j<n; j++){

//           grid[i][j] = *x++;
//       }
//     }
//    qDebug() << "n: " << n;
//    for(int i=0;i<n; i++){
//       for(int j=0; j<n; j++){
//           if(*(*grid+i*n+j)==0){
//           sc.findconstraintparti(*grid,i,j,n);
//           std::vector<int> tmp;
//           for(int i = 1; i<=n;i++){
//                //put constraints to cells

//               if(*(sc.getconstraint(n)+i)==3){
//                  tmp.push_back(i);
//               }
//           }
//           //if any cell do not have a valid candidate, then the puzzle is insolvable
//           if(tmp.size()==0){ solvable = false;
//                break;}

//           //add constraints to vector, correspondingly
//           if(solvable){
//             cts[*grid+i*n+j] = tmp;

//             //push unassigned
//             //bucket sort
//              bucket[tmp.size()].push_back(*grid+i*n+j);

//              // it is a unique identity,each cell joins three group
//             // int block = (i/sqrt(n))*sqrt(n) + j/sqrt(n);j
//              int sq = sqrt(n);
//              int block = (i/sq)*sq + j/sq;
//             // qDebug() << "i j k: " << i << " " << j << " "<< block;
//              rowFd[i].push_back(*grid+i*n+j);
//              colFd[j].push_back(*grid+i*n+j);
//              blkFd[block].push_back(*grid+i*n+j);
//           }
//       }
//     }
//    }
//    for(int j = n-1; j>0; j--){
//           for(auto i : bucket[j])
//             S1.push(i);

//       }

//    bucket.clear();


//  int step = 0;
//  solved = false;

//  std::stack<std::vector<std::map<int*,int>>> traceCts;

//  if(!S1.empty() && solvable)
//  {

//       bool backtrack = false;
//       std::set<int*> S2set;
//    do{

//      if(!backtrack && int(cts[S1.top()].size())>0 && cts[S1.top()].at(0)!=0){

//           *S1.top() = cts[S1.top()].at(0);
//          //delete constraints
//          int i = (S1.top()-*grid)/n;
//          int j = (S1.top()-*grid)%n;
//          int sq = sqrt(n);
//          int block = (i/sq)*sq + j/sq;

//          std::vector<std::vector<int*>> arr = {rowFd[i],colFd[j],blkFd[block]};
//            std::vector<std::map<int*,int>> tmpV;



//           for(auto v : arr){
//               //m - address of cell
//               //delete onstraint of cells in group and trace those cells
//               for(auto m : v){
//                      for(int k = 0;k< int(cts[m].size()); k++){
//                           if(cts[m].at(k) == *S1.top()){
//                               //track values deleted by a map
//                               std::map<int*,int> tmpM;
//                               tmpM[m] = *S1.top();
//                               cts[m].erase(cts[m].begin()+k--);
//                               tmpV.push_back(tmpM);
//                               if(int(cts[m].size())==0 && !S2set.count(m))
//                                   backtrack = true;
//                             //break
//                             k =n;
//                          }
//                       }
//                   }
//               }
//               traceCts.push(tmpV);
//               S2.push(S1.top());
//               S2set.insert(S1.top());
//               S1.pop();





//              }else{

//              //backtrack
//             if(cts[S1.top()].size()>0 && cts[S1.top()].at(0)==0) cts[S1.top()].erase(cts[S1.top()].begin());
//             if(!S2.empty()){

//                 if(!std::count(cts[S2.top()].begin(), cts[S2.top()].end(), 0))
//                     cts[S2.top()].push_back(0);
//                 for(auto i : traceCts.top()){
//                     for(const auto& p  : i ){
//                         cts[p.first].push_back(p.second);
//                     }
//                 }

//                 traceCts.pop();

//              S1.push(S2.top());
//              S2.pop();
//              if(int(cts[S1.top()].size())>0 && cts[S1.top()].at(0)!=0)
//                  backtrack = false;

//             }
//             else{
//               if(cts[S1.top()].at(0) ==0)solvable = false;
//             }

//         }

//       step ++ ;
//      // qDebug() << "s1: " <<  S1.size() ;
//      }while(!S1.empty() && solvable);
//     }

//      if(S1.empty()) solved = true;
//      totalstep = step;

//      qDebug() << "trial1: " << step << "solvable: " << solvable;
//      qDebug() << "valid1" << validity(*grid,n);
// //  bool e = validity(*grid,n);
//   for(int i=0;i<n; i++){
//      for(int j=0; j<n; j++){
//         if(n==9)
//             resultGrid[i][j] = grid[i][j] ;
//         else
//             resultGrid16[i][j] = grid[i][j];
//         //std::cout << grid[i][j] << " ";
//      }
//     // std::cout << "\n";
//   }
//}

/*
 * solver
 */
void solvepuzzle::solve(int*x,int n)
{
    std::stack<int*> S1;
    std::stack<int*> S2;
    std::map<int*,std::vector<int>> cts;
    showconstraint sc;
    // for sorting
    std::map<int,std::vector<int*>> bucket;
    bool solvable = true;

    //copy the grid
    int grid[n][n];
    for(int i=0;i<n; i++){
       for(int j=0; j<n; j++){

           grid[i][j] = *x++;
       }
     }
    for(int i=0;i<n; i++){
       for(int j=0; j<n; j++){
           if(*(*grid+i*n+j)==0){
           sc.findconstraintparti(*grid,i,j,n);
           std::vector<int> tmp;
           for(int i = 1; i<=n;i++){
                //put constraints to cells
               if(*(sc.getconstraint(n)+i)==3){
                  tmp.push_back(i);
               }
           }
            if(tmp.size()==0){ solvable = false;
                break;}

           //add constraints to vector, correspondingly
           if(solvable){

             cts[*grid+i*n+j] = tmp;

           //push unassigned
             //bucket sort
              bucket[tmp.size()].push_back(*grid+i*n+j);

              // it is a unique identity,each cell joins three group
             // int block = (i/sqrt(n))*sqrt(n) + j/sqrt(n);j
              int sq = sqrt(n);
              int block = (i/sq)*sq + j/sq;
             // qDebug() << "i j k: " << i << " " << j << " "<< block;
              rowFd[i].push_back(*grid+i*n+j);
              colFd[j].push_back(*grid+i*n+j);
              blkFd[block].push_back(*grid+i*n+j);

           }
       }
     }

    }
    for(int j = n-1; j>0; j--){
           for(auto i : bucket[j])
             S1.push(i);

       }
    bucket.clear();
  //counting steps
  int step = 0;
  solved = false;
  std::stack<std::vector<std::map<int*,int>>> traceCts;
  if(!S1.empty() && solvable)
  {

    do{

      if(int(cts[S1.top()].size())>0 && cts[S1.top()].at(0)!=0){

           *S1.top() = cts[S1.top()].at(0);
          //delete constraints
          int i = (S1.top()-*grid)/n;
          int j = (S1.top()-*grid)%n;
          int sq = sqrt(n);
          int block = (i/sq)*sq + j/sq;

          std::vector<std::vector<int*>> arr = {rowFd[i],colFd[j],blkFd[block]};
          std::vector<std::map<int*,int>> tmpV;
           for(auto v : arr){
               //m - addr
               for(auto m : v){
                      for(int k = 0;k< int(cts[m].size()); k++){
                           if(cts[m].at(k) == *S1.top()){
                               //track values deleted by a map
                               std::map<int*,int> tmpM;

                               tmpM[m] = *S1.top();
                               cts[m].erase(cts[m].begin()+k--);
                               tmpV.push_back(tmpM);
                             //break
                             k =n;
                          }
                       }
                   }
               }
              //trace deletions and put assigned cell to S2
              traceCts.push(tmpV);
              S2.push(S1.top());
              S1.pop();

              }else{
              //backtrack
             //if there do not have a zero
             if(cts[S1.top()].size()>0 && cts[S1.top()].at(0)==0) cts[S1.top()].erase(cts[S1.top()].begin());
             if(!S2.empty()){
                 if(!std::count(cts[S2.top()].begin(), cts[S2.top()].end(), 0))
                     cts[S2.top()].push_back(0);
                 for(auto i : traceCts.top()){
                     for(const auto& p  : i ){
                         cts[p.first].push_back(p.second);
                     }
                 }
              //release traced cells and put back to S1
              traceCts.pop();
              S1.push(S2.top());
              S2.pop();
             }
             else{
               //possible candidates tried
               if(cts[S1.top()].at(0) ==0)solvable = false;
             }

         }

       step ++ ;
      }while(!S1.empty() && solvable);
     }

      if(S1.empty()) solved = true;
      totalstep = step;
   //put solution to resultGrid
   for(int i=0;i<n; i++){
      for(int j=0; j<n; j++){
         if(n==9)
             resultGrid[i][j] = grid[i][j] ;
         else
             resultGrid16[i][j] = grid[i][j];
      }
   }
}

//############### version 4 ############################

//void solvepuzzle::solve(int*x,int n)
//{
//    std::stack<int*> S1;
//    std::stack<int*> S2;
//    std::map<int*,std::vector<int>> cts;
//   // std::map<int*,int> ctsPos;
//    // for sorting
//    std::map<int,std::vector<int*>> bucket;
//    bool solvable = true;

//    showconstraint sc;
//    //copy the grid
//    int grid[n][n];
//    for(int i=0;i<n; i++){
//       for(int j=0; j<n; j++){

//           grid[i][j] = *x++;
//       }
//     }
//    qDebug() << "n: " << n;
//    for(int i=0;i<n; i++){
//       for(int j=0; j<n; j++){
//           if(*(*grid+i*n+j)==0){
//           sc.findconstraintparti(*grid,i,j,n);
//           std::vector<int> tmp;
//           for(int i = 1; i<=n;i++){
//                //put constraints to cells

//               if(*(sc.getconstraint(n)+i)==3){
//                  tmp.push_back(i);
//               }
//           }
//            if(tmp.size()==0){ solvable = false;
//                break;}

//           //add constraints to vector, correspondingly
//           if(solvable){

//             cts[*grid+i*n+j] = tmp;

//           //push unassigned
//             //bucket sort
//              bucket[tmp.size()].push_back(*grid+i*n+j);

//              // it is a unique identity,each cell joins three group
//             // int block = (i/sqrt(n))*sqrt(n) + j/sqrt(n);j
//              int sq = sqrt(n);
//              int block = (i/sq)*sq + j/sq;
//             // qDebug() << "i j k: " << i << " " << j << " "<< block;
//              rowFd[i].push_back(*grid+i*n+j);
//              colFd[j].push_back(*grid+i*n+j);
//              blkFd[block].push_back(*grid+i*n+j);

//           }
//       }
//     }

//    }
//    for(int j = n-1; j>0; j--){
//           for(auto i : bucket[j])
//             S1.push(i);

//       }


////    while(!S1.empty()){
////        int i = (S1.top()-*grid)/n;
////        int j = (S1.top()-*grid)%n;
////        qDebug() << S1.size() << "cts size:" << cts[S1.top()]<<"pos: " << i << ": " << j;

////        S1.pop();
////    }

//    bucket.clear();


//  int start = 0;
//  solved = false;

//  std::stack<std::vector<std::map<int*,int>>> traceCts;

//  if(!S1.empty() && solvable)
//  {
//    do{


//      if(int(cts[S1.top()].size())>0 && cts[S1.top()].at(0)!=0){

//          *S1.top() = cts[S1.top()].at(0);


//          //delete constraints
//          int i = (S1.top()-*grid)/n;
//          int j = (S1.top()-*grid)%n;
//          int sq = sqrt(n);
//          int block = (i/sq)*sq + j/sq;

////          qDebug() << "s1: " << S1.size() << "s2: " << S2.size() << "pos: " << i+1 << ": " << j+1 ;
////         qDebug() << "constraint push : " << *S1.top();
////         for(auto i: cts[S1.top()]){

////                 qDebug() << i;

////         }
//          std::vector<std::vector<int*>> arr = {rowFd[i],colFd[j],blkFd[block]};
//            std::vector<std::map<int*,int>> tmpV;
//           for(auto v : arr){
//               //m - addr
//               for(auto m : v){
//                      for(int k = 0;k< int(cts[m].size()); k++){

//                           if(cts[m].at(k) == *S1.top()){
//                               //track values deleted by a map
//                               std::map<int*,int> tmpM;

//                               tmpM[m] = *S1.top();
//                               cts[m].erase(cts[m].begin()+k--);
//                               tmpV.push_back(tmpM);
//                             //break
//                             k =n;
//                          }
//                       }
//                   }
//               }
//              traceCts.push(tmpV);

//              S2.push(S1.top());
//              S1.pop();

//              }else{
//              //backtrack
//             if(cts[S1.top()].size()>0 && cts[S1.top()].at(0)==0) cts[S1.top()].erase(cts[S1.top()].begin());
//             if(!S2.empty()){
//                 //*S2.top() = 0;
//                 //push back constraint, add 0 in front of the tried candidates
////                 int i = (S2.top()-*grid)/n;
////                 int j = (S2.top()-*grid)%n;
////                 int sq = sqrt(n);
////                 int block = (i/sq)*sq + j/sq;
//               //  qDebug() << "s1: " << S1.size() << "s2: " << S2.size() << "pos: " << i+1 << ": " << j+1 ;
//                 if(!std::count(cts[S2.top()].begin(), cts[S2.top()].end(), 0))
//                     cts[S2.top()].push_back(0);
//                 for(auto i : traceCts.top()){
//                     for(const auto& p  : i ){
//                         cts[p.first].push_back(p.second);
//                     }
//                 }
////                 qDebug() << "constraint pop : " << *S2.top();
////                 for(auto i: cts[S2.top()]){

////                         qDebug() << i;

////                 }

//                 traceCts.pop();

//              S1.push(S2.top());
//              S2.pop();
//             }
//             else{
//               if(cts[S1.top()].at(0) ==0)solvable = false;
//             }

//         }

//       start ++ ;

//      // qDebug() << "s1: " <<  S1.size() ;
//      }while(!S1.empty() && solvable && start < 700000);
//     }



////  while(!traceCts.empty()){

////      for(auto i : traceCts.top()){
////          for(const auto& p  : i ){
////              qDebug() << "map: " << p.first << " " << p.second ;
////          }
////      }
////      traceCts.pop();

////  }



//      qDebug() << "trial: " << start << "solvable: " << solvable;
//      qDebug() << "valid" << validity(*grid,n);
// //  bool e = validity(*grid,n);
//   for(int i=0;i<n; i++){
//      for(int j=0; j<n; j++){
//         if(n==9)
//             resultGrid[i][j] = grid[i][j] ;
//         else
//             resultGrid16[i][j] = grid[i][j];
//         //std::cout << grid[i][j] << " ";
//      }
//     // std::cout << "\n";
//   }
//}

//########### version 3 ##################3

//void solvepuzzle::solve(int*x,int n)
//{
//    std::stack<int*> S1;
//    std::stack<int*> S2;
//    std::map<int*,std::vector<int>> cts;
//    std::map<int*,int> ctsPos;
//    // for sorting
//    std::map<int,std::vector<int*>> bucket;
//    bool solvable = true;

//    showconstraint sc;
//    //copy the grid
//    int grid[n][n];
//    for(int i=0;i<n; i++){
//       for(int j=0; j<n; j++){

//           grid[i][j] = *x++;
//       }
//     }

//    for(int i=0;i<n; i++){
//       for(int j=0; j<n; j++){

//           if(*(*grid+i*n+j)==0){

//           sc.findconstraintparti(*grid,i,j,n);
//           std::vector<int> tmp;
//           for(int i = 1; i<=n;i++){
//                //put constraints to cells

//               if(*(sc.getconstraint(n)+i)==3){
//                  tmp.push_back(i);
//               }
//           }
//            if(tmp.size()==0){ solvable = false;
//                qDebug() << i << " " << j;
//                break;}


//           //add constraints to vector, correspondingly



//           if(solvable){

//             cts[*grid+i*n+j] = tmp;

//           //push unassigned
//             //bucket sort
//              bucket[tmp.size()].push_back(*grid+i*n+j);

//              // it is a unique identity,each cell joins three group
//             // int block = (i/sqrt(n))*sqrt(n) + j/sqrt(n);j
//              int sq = sqrt(n);
//              int block = (i/sq)*sq + j/sq;
//             // qDebug() << "i j k: " << i << " " << j << " "<< block;
//              rowFd[i].push_back(*grid+i*n+j);
//              colFd[j].push_back(*grid+i*n+j);
//              blkFd[block].push_back(*grid+i*n+j);

//           }
//       }
//     }

//    }
//    for(int j = n-1; j>0; j--){
//           for(auto i : bucket[j])
//             S1.push(i);

//       }


////    while(!S1.empty()){
////        int i = (S1.top()-*grid)/n;
////        int j = (S1.top()-*grid)%n;
////        qDebug() << S1.size() << "pos: " << i << ": " << j;
////        for(auto i:cts[S1.top()])
////            qDebug() << "cts: " << i;
////        S1.pop();
////    }

//    bucket.clear();


//  int start = 0;
//  solved = false;

//  std::stack<std::vector<std::map<int*,int>>> traceCts;

//  if(!S1.empty() && solvable)
//  {
//    do{


//      if(int(cts[S1.top()].size())>0 && cts[S1.top()].at(0)!=0){

//          *S1.top() = cts[S1.top()].at(0);


//          //delete constraints
//          int i = (S1.top()-*grid)/n;
//          int j = (S1.top()-*grid)%n;
//          int sq = sqrt(n);
//          int block = (i/sq)*sq + j/sq;

////          qDebug() << "s1: " << S1.size() << "s2: " << S2.size() << "pos: " << i+1 << ": " << j+1 ;
////         qDebug() << "constraint push : " << *S1.top();
////         for(auto i: cts[S1.top()]){

////                 qDebug() << i;

////         }
//          std::vector<std::vector<int*>> arr = {rowFd[i],colFd[j],blkFd[block]};
//            std::vector<std::map<int*,int>> tmpV;
//           for(auto v : arr){
//               //m - addr
//               for(auto m : v){
//                      for(int k = 0;k< int(cts[m].size()); k++){

//                           if(cts[m].at(k) == *S1.top()){
//                               //track values deleted by a map
//                               std::map<int*,int> tmpM;

//                               tmpM[m] = *S1.top();
//                               cts[m].erase(cts[m].begin()+k--);
//                               tmpV.push_back(tmpM);
//                             //break
//                             k =n;
//                          }
//                       }
//                   }
//               }
//              traceCts.push(tmpV);

//              S2.push(S1.top());
//              S1.pop();

//              }else{
//              //backtrack
//             if(cts[S1.top()].size()>0 && cts[S1.top()].at(0)==0) cts[S1.top()].erase(cts[S1.top()].begin());
//             if(!S2.empty()){
//                 //*S2.top() = 0;
//                 //push back constraint, add 0 in front of the tried candidates
////                 int i = (S2.top()-*grid)/n;
////                 int j = (S2.top()-*grid)%n;
////                 int sq = sqrt(n);
////                 int block = (i/sq)*sq + j/sq;
//               //  qDebug() << "s1: " << S1.size() << "s2: " << S2.size() << "pos: " << i+1 << ": " << j+1 ;
//                 if(!std::count(cts[S2.top()].begin(), cts[S2.top()].end(), 0))
//                     cts[S2.top()].push_back(0);
//                 for(auto i : traceCts.top()){
//                     for(const auto& p  : i ){
//                         cts[p.first].push_back(p.second);
//                     }
//                 }
////                 qDebug() << "constraint pop : " << *S2.top();
////                 for(auto i: cts[S2.top()]){

////                         qDebug() << i;

////                 }

//                 traceCts.pop();

//              S1.push(S2.top());
//              S2.pop();
//             }
//             else{
//               if(cts[S1.top()].at(0) ==0)solvable = false;
//             }

//         }

//       start ++ ;

//      // qDebug() << "s1: " <<  S1.size() ;
//      }while(!S1.empty() && solvable);
//     }



////  while(!traceCts.empty()){

////      for(auto i : traceCts.top()){
////          for(const auto& p  : i ){
////              qDebug() << "map: " << p.first << " " << p.second ;
////          }
////      }
////      traceCts.pop();

////  }



//      qDebug() << "trial: " << start << "solvable: " << solvable;
//   if(S1.empty()) solved = true;
// //  bool e = validity(*grid,n);
//   for(int i=0;i<n; i++){
//      for(int j=0; j<n; j++){
//         if(n==9)
//             resultGrid[i][j] = grid[i][j] ;
//         else
//             resultGrid16[i][j] = grid[i][j];
//         //std::cout << grid[i][j] << " ";
//      }
//     // std::cout << "\n";
//   }
//}


//*********** version 2 *******************


//void solvepuzzle::solve(int*x,int n)
//{
//    std::stack<int*> S1;
//    std::stack<int*> S2;
//    std::map<int*,std::vector<int>> cts;
//    std::map<int*,int> ctsPos;
//    // O(n) sort
//    std::map<int,std::vector<int*>> bucket;

//    showconstraint sc;
//    //copy the grid
//    int grid[n][n];
//    for(int i=0;i<n; i++){
//       for(int j=0; j<n; j++){

//           grid[i][j] = *x++;
//       }
//     }


//    for(int i=0;i<n; i++){
//       for(int j=0; j<n; j++){

//           if(*(*grid+i*n+j)==0){

//           sc.findconstraintparti(*grid,i,j,n);
//           std::vector<int> tmp;
//           for(int i = 1; i<=n;i++){
//                //put constraints to cells

//               if(*(sc.getconstraint(n)+i)==3){
//                  tmp.push_back(i);
//               }
//           }
//           //add constraints to vector, correspondingly
//             cts[*grid+i*n+j] = tmp;
//            ctsPos[*grid+i*n+j] = 0;
//           //push unassigned
//             //bucket sort
//              bucket[tmp.size()].push_back(*grid+i*n+j);
//           }
//       }
//     }
//    for(int j = n; j>0; j--){

//              for(auto i : bucket[j])
//                S1.push(i);
//          }


//  int start = 0;
//  solved = false;
//  bool solvable = true;
//  if(!S1.empty())
//  {
//    do{
//     //if stack 1, point to S1, else S2

//     //get the pos of the cell

//     //value will be assigned from 1 to n, if the value is 5, the next trial is 6


//     //int trial = *p->top()+1;
//     int trial = int(ctsPos[S1.top()]);
//    // int trial = 0;
//     int end = int(cts[S1.top()].size());

//      bool b = false;
//     // std::cout << " begin trial: " <<  trial <<" " << stk << " : " << p->size()<< " " <<  i <<" ivsj " << j <<" "  << std::endl;

//      //trial until a valid candidate found
//      while(trial< end){
//          //assign trial to the cell

//          *S1.top() = int(cts[S1.top()].at(trial));
//          //check if the new trial is a valid candidate

//          int i = (S1.top()-*grid)/n;
//          int j = (S1.top()-*grid)%n;
//          b =validity_parti(*grid,i,j,n);

//          ctsPos[S1.top()]++;

//          if(b){         //s1
//              //if find a clue to a cell put it to S2
//              S2.push(S1.top());
//              S1.pop();
//              trial = end; //break
//             }

//            trial++;
//        }

//      if(!b){

//          ctsPos[S1.top()] = 0;
//          *S1.top() = 0;
//          //stack 1, change to 2
//             if(!S2.empty()){
//              S1.push(S2.top());
//              S2.pop();
//             }else{
//                 solvable = false;
//             }

//          }

//       start ++ ;

//      }while(!S1.empty() && solvable);
//     }
//       qDebug() << "trial: " << start << "solvable: " << solvable;
//   if(S1.empty()) solved = true;
// //  bool e = validity(*grid,n);
//   for(int i=0;i<n; i++){
//      for(int j=0; j<n; j++){
//         if(n==9)
//             resultGrid[i][j] = grid[i][j] ;
//         else
//             resultGrid16[i][j] = grid[i][j];
//         //std::cout << grid[i][j] << " ";
//      }
//     // std::cout << "\n";
//   }
//}









//************ version 1 ***************

///*
// * Naive version
// */

//void solvepuzzle::solve(int*x,int n)
//{
//    std::stack<int*> S1;
//    std::stack<int*> S2;
//    std::vector<std::vector<int>> cts;
//    solved = false;
//    showconstraint sc;
//    //copy the grid
//    int grid[n][n];
//    for(int i=0;i<n; i++){
//       for(int j=0; j<n; j++){

//           grid[i][j] = *x++;
//       }
//     }
//    for(int i=0;i<n; i++){
//       for(int j=0; j<n; j++){

//           if(*(*grid+i*n+j)==0){
//           //push unassigned
//           S1.push(*grid+i*n+j);
//           sc.findconstraintparti(*grid,i,j,n);
//           std::vector<int> tmp;
//           for(int i = 1; i<=n;i++){
//                //put constraints to cells

//               if(*(sc.getconstraint(n)+i)==3){
//                  tmp.push_back(i);
//               }
//           }
//           //add constraints to vector, correspondingly
//           cts.push_back(tmp);
//           }
//       }
//     }
//   bool stk = 1;
//   std::stack<int*> *p;

//  int step = 0;
//  if(!S1.empty())
//  {
//    do{
//     //if stack 1, point to S1, else S2
//     if(stk) p = &S1;
//     else p = &S2;
//     //get the pos of the cell
//     int i = (p->top()-*grid)/n;
//     int j = (p->top()-*grid)%n;
//     //value will be assigned from 1 to n, if the value is 5, the next trial is 6
//     int trial = *p->top()+1;
//      bool b = false;
//      //trial until a valid candidate found
//      while(trial<=n){
//          //assign trial to the cell
//          *p->top() = trial;
//          //check if the new trial is a valid candidate
//          b =validity_parti(*grid,i,j,n);

//          if(b && stk){         //s1
//              //if find a clue to a cell put it to S2
//              S2.push(S1.top());
//              S1.pop();
//              trial = n; //break
//             }

//          if(b && !stk){      //s2

//              stk = 1;    //backtrack finished
//              trial = n; //break
//           }
//          trial++;
//        }
//      //no clues for the cell , b remain false
//      if(!b){
//          *p->top()=0;
//          //stack 1, change to 2
//           if(stk){
//              stk =0;
//           }else{
//              //put back to stack 1
//              S1.push(p->top());
//              p->pop();
//           }
//          }
//      step ++;
//      }while(!S1.empty() && !S2.empty());
//     }
//   //put solution to resultGrid
//   for(int i=0;i<n; i++){
//      for(int j=0; j<n; j++){
//         if(n==9)
//             resultGrid[i][j] = grid[i][j] ;
//         else
//             resultGrid16[i][j] = grid[i][j];
//      }
//   }

//}












