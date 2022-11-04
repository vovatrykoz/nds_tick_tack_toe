enum cellFill { Empty, Cross, Circle };

class Cell {
    private:
      cellFill fill;

    public:
      Cell();

      bool setFill(cellFill fill);
};