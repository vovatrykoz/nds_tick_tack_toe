#include <gridSupervisor.h>
#include <iostream>

std::vector<supervElement> GridSupervisor::getSupervArr() const {
    return supervArr;
}

unsigned int GridSupervisor::getSupervSize() const {
    return supervArr.size();
}

void GridSupervisor::processSubComponent(unsigned int posX, unsigned int posY, unsigned int gridSize, CellMark mark) {
    //when array is empty
    if(supervArr.size() == 0) {
        supervArr.push_back({posY, Winnable, mark});
        supervArr.push_back({posX + gridSize, Winnable, mark});

        if(posX == posY)
            supervArr.push_back({gridSize * 2, Winnable, mark});

        if((posX + posY) == gridSize - 1)
            supervArr.push_back({(gridSize * 2) + 1, Winnable, mark});

        return;
    }
    //push rows
    for(unsigned int i = 0; i < supervArr.size(); i++) {
        if(supervArr[i].compId == posY) {
            if(mark != supervArr[i].occupiedBy)
                supervArr[i].compStat = Unwinnable;
            
            break;
        }

        if(i == supervArr.size() - 1)
            supervArr.push_back({posY, Winnable, mark});
    }
    //push cols
    for(unsigned int i = 0; i < supervArr.size(); i++) {
        if(supervArr[i].compId == posX + gridSize) {
            if(mark != supervArr[i].occupiedBy)
                supervArr[i].compStat = Unwinnable;
            
            break;
        }

        if(i == supervArr.size() - 1)
            supervArr.push_back({posX + gridSize, Winnable, mark});
    }
    //push SE diag
    for(unsigned int i = 0; i < supervArr.size(); i++) {
        if(supervArr[i].compId == gridSize * 2) {
            if(mark != supervArr[i].occupiedBy)
                supervArr[i].compStat = Unwinnable;
            
            break;
        }

        if(i == supervArr.size() - 1)
            supervArr.push_back({gridSize * 2, Winnable, mark});
    }
    //push SW diag
    for(unsigned int i = 0; i < supervArr.size(); i++) {
        if(supervArr[i].compId == (gridSize * 2) + 1) {
            if(mark != supervArr[i].occupiedBy)
                supervArr[i].compStat = Unwinnable;
            
            break;
        }

        if(i == supervArr.size() - 1)
            supervArr.push_back({(gridSize * 2) + 1, Winnable, mark});
    }
}