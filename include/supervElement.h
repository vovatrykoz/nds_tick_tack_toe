#ifndef _SUPER_ELEMENT_
#define _SUPER_ELEMENT_
#include <cell.h>
enum CompStatuses { Winnable, Unwinnable };
struct supervElement {
    unsigned int compId;
    CompStatuses compStat;
    CellMark occupiedBy;
};
#endif