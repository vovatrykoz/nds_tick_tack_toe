#include <supervElement.h>
#include <vector>

class GridSupervisor {
    private:
        std::vector<supervElement> supervArr;

    public:
        std::vector<supervElement> getSupervArr() const;

        unsigned int getSupervSize() const;

        void processSubElementAt(unsigned int posX, unsigned int posY, unsigned int gridSize);
};