#include "grid.h"
#include "solvepuzzle.h"

//initial grid with all zeros
grid::grid(int n)
{

    this->n = n;
   for(int i=0; i< n*n; i++){
        *(Grid()+i) = 0;

   }

}

void grid::printGrid(){

    for(int i=0;i < n; i++){
        for(int j=0; j<n; j++){
       if(*(Grid()+i*n+j) ==0) std::cout << ".";
       else
       std::cout <<*(Grid()+i*n+j) << " ";
        }

        std::cout << std::endl;
    }
}
