enum CellMark { Empty, X, O };

class Cell {
    private:
      CellMark mark;

    public:
      CellMark getMark() const;
  
      void setMark(CellMark mark);

      Cell();
};