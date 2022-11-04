#include <cell.h>

Cell::Cell() : mark(Empty) {};

void Cell::getMark() {
    return mark;
}

void Cell::setMark(cellMark mark) {
    this->mark = mark;
}