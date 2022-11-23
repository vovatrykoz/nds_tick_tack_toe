#include <gridSupervisor.h>

void GridSupervisor::processSubElementAt(unsigned int posX, unsigned int posY, unsigned int gridSize) {
    unsigned int componentId = posX + posY * gridSize;
    for(unsigned int i = 0; i < supervArr.size(); i++) {
        if(supervArr[i].compId == componentId) {
            supervArr[i].compStat = Unwinnable;
        }
    }
}