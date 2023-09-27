#include "unittest.h"
#include "generatepuzzle.h"
#include <iostream>
#include <fstream>
#include <QDebug>
unittest::unittest()
{

}

void unittest::randomnum(int x,int n)
{
    generatepuzzle gp;
    std::ofstream myfile;
        myfile.open ("/Users/Isaac/Desktop/FinalProject/Sudoku/backtracking/backtracking/testrandom.csv");

        for(int i =0; i<n; i++){
            int r = gp.randnum(x);
            myfile << r;
            myfile << "\n";
        }

        myfile.close();
}

void unittest::generate(int n)
{
    generatepuzzle *gp;
    solvepuzzle *sp;

    std::ofstream myfile;
        myfile.open ("/Users/Isaac/Desktop/FinalProject/Sudoku/backtracking/backtracking/generate.csv");

    for(int i = 0; i<1; i++){
        int grid[n][n];
        for(int i=0; i< n*n; i++){
             *(*grid+i) = 0;
        }
//            int grid[9][9] = {
//                {3,0,0,9,0,4,0,0,1},
//                {0,0,2,0,0,0,4,0,0},
//                {0,6,1,0,0,0,7,9,0},
//                {6,0,0,2,4,7,0,0,5},
//                {0,0,0,0,0,0,0,0,0},
//                {2,0,0,8,3,6,0,0,4},
//                {0,4,6,0,0,0,2,3,0},
//                {0,0,9,0,0,0,6,0,0},
//                {5,0,0,3,0,9,0,0,8}
//            };
     gp = new generatepuzzle();
     sp = new solvepuzzle();
     gp->generate(*grid, n);
     sp->solve(*grid,n);
     bool valid = sp->validity(sp->getResult(n),n);
     int step = sp->totalstep;
      myfile  << valid << " " << step ;
      myfile << "\n";
      delete sp;
      delete gp;

   }

        myfile.close();
}

void unittest::correctness(int n)
{
  //store the puzzle and solution in vector
  std::vector<int*> puzzle;
  std::vector<int*> solution;
  for(int i = 0; i<5; i++){
      puzzle.push_back(*sudoku1);
      solution.push_back(*sudoku1Sol);
  }
  solvepuzzle *sp;
  //test start
  for(int i=0; i< 5 ; i++){
  sp = new solvepuzzle();
  sp->solve(puzzle.at(0),n);
  bool assert = true;
  // check difference
  for(int i=0;i<n; i++){
     for(int j=0; j<n; j++){
        std::cout << *(sp->getResult(n)+i*n+j) << " ";
        if(*(sp->getResult(n)+i*n+j) != *(solution.at(0)+i*n+j))
            assert = false;
     }
      std::cout << "\n";
    }
  //  for(int i=0;i<n; i++){
  //     for(int j=0; j<n; j++){
  //        std::cout << *(solution.at(0)+i*n+j)<< " ";
  //     }
  //      std::cout << "\n";
  //  }
   //print results
   std::string result = (assert==1)? "true":"false";
    std::cout << "correctness of puzzle " << i+1 << ": " << result;
    std::cout << "\n\n";
  }
   std::cout << "\n";
}








