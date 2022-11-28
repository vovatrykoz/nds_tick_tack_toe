#include <gridSupervisor.h>
#include <iostream>

std::vector<supervElement> GridSupervisor::getSupervArr() const {
    return supervArr;
}

unsigned int GridSupervisor::getSupervSize() const {
    return supervArr.size();
}

void GridSupervisor::processSubElementAt(unsigned int posX, unsigned int posY, unsigned int gridSize) {
    if(supervArr.size() == 0) {
        supervArr.push_back({posY, Winnable});
        supervArr.push_back({posX + gridSize, Winnable});

        if(posX == posY)
            supervArr.push_back({gridSize * 2, Winnable});

        if((posX + posY) == gridSize - 1)
            supervArr.push_back({(gridSize * 2) + 1, Winnable});
    }
   
    for(unsigned int i = 0; i < supervArr.size(); i++) {
        if(supervArr[i].compId == posY) {
            supervArr[i].compStat = Unwinnable;
            break;
        }

        if(i == supervArr.size() - 1)
            supervArr.push_back({posY, Winnable});
    }

    for(unsigned int i = 0; i < supervArr.size(); i++) {
        if(supervArr[i].compId == posX + gridSize) {
            supervArr[i].compStat = Unwinnable;
            break;
        }

        if(i == supervArr.size() - 1)
            supervArr.push_back({posX + gridSize, Winnable});
    }
}