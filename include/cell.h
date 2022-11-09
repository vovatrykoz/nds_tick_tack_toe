enum cellMark { Empty, X, O };

class Cell {
    private:
      cellMark mark;

    public:
      cellMark getMark() const;
  
      void setMark(cellMark mark);

      Cell();
};