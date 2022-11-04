enum cellMark { Empty, Cross, Circle };

class Cell {
    private:
      cellMark mark;

    public:
      Cell();

      void setMark(cellMark mark);
};