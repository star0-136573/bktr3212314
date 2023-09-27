#ifndef PATTERNRECOGNITION_H
#define PATTERNRECOGNITION_H
#include <map>
#include<set>
#include<vector>

class patternrecognition
{
   std::set<std::vector<int>> X;
   std::set<std::vector<int>> Y;
   std::set<std::vector<int>> R;
public:

    patternrecognition();
    void matchpoints(bool XYmode,int size,std::map<int,std::vector<int>> numposition);
    std::map<int,std::vector<int>> mapconstraints(int *grid, int size, std::string mode);
    void XYwing(int* grid,int size);
    void Rect(int* grid,int size);
    auto* Xwing(){
        return &X;
    }
    auto* Ywing(){
        return &Y;
    }
    auto* Rect(){
        return &R;
    }
};

#endif // PATTERNRECOGNITION_H
