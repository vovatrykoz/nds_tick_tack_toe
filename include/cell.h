enum cellMark { Empty, Cross, Circle };

class Cell {
    private:
      cellMark mark;

    public:
      cellMark getMark() const;
  
      void setMark(cellMark mark);

      Cell();
};