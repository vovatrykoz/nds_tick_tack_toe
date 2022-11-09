#include <cell.h>

Cell::Cell() : mark(Empty) {};

cellMark Cell::getMark() const {
    return mark;
}

void Cell::setMark(cellMark mark) {
    this->mark = mark;
}