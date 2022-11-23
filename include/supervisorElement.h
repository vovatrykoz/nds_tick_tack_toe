enum CompStatuses { Winnable, NonWinnable }

/*A single element of the grid component supervisor which is 
  responsible for tracking a single grid component. A component
  can be a row, a column or a diagonal

  compId - trackable components id
  compStat - status of the current component (can be Winnable or NotWinnable) */
struct supervisorElement {
    int compId;
    CompStatuses compStat;
}