#include <cell.h>
#include <iostream> //DEBUG ONLY, REMOVE LATER

Cell::Cell() : mark(Empty) {};

CellMark Cell::getMark() const {
    return mark;
}

void Cell::setMark(CellMark mark) {
    this->mark = mark;
}