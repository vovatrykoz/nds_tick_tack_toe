#include <cell.h>

Cell::Cell() : mark(Empty) {};

CellMark Cell::getMark() const {
    return mark;
}

void Cell::setMark(CellMark mark) {
    this->mark = mark;
}