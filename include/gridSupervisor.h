#include <supervElement.h>
#include <vector>

class GridSupervisor {
    private:
        std::vector<supervElement> supervArr;

    public:
        void processSubElementAt(unsigned int posX, unsigned int posY, unsigned int gridSize);
};