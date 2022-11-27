#ifndef _SUPER_ELEMENT_
#define _SUPER_ELEMENT_
enum CompStatuses { Winnable, Unwinnable };
struct supervElement {
    unsigned int compId;
    CompStatuses compStat;
};
#endif