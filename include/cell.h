enum cellMark { Empty, Cross, Circle };

class Cell {
    private:
      cellMark mark;

    public:
      void getMark();
  
      void setMark(cellMark mark);

      Cell();
};